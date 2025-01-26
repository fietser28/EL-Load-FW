// SPDX-FileCopyrightText: 2024 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <FreeRTOS.h>
#include "task.h"
#include "message_buffer.h"
#include "scpi/scpi.h"
#include "eez-framework.h"
#include <eez/flow/queue.h>
#include <eez/flow/flow.h>

#include "main.h"
#include "eeprom.h"
#include "scpi-def.h"

#include "keys.h"
#include "display.h"

using namespace dcl;
namespace dcl::scpi {

//// SCPI I/O and ERROR helper functions
scpi_interface_t scpi_interface = {
    /*.error = */ SCPI_Error,
    /*.write = */ SCPI_Write,
    /*.control = */ SCPI_Control,
    /*.flush = */ SCPI_Flush,
    /*.reset = */ SCPI_Reset,
};

scpi_t scpi_context;
scpi_error_t scpi_error_queue_data[SCPI_ERROR_QUEUE_SIZE];

int32_t scpi_busy = 0;

int32_t scpi_busy_inc() {
  return ++scpi_busy;
}

int32_t scpi_busy_dec() {
  if (scpi_busy == 0) {
    return 0; //TODO add assert we hit a bug.
  }
  return --scpi_busy;
}

// Buffering to UART message buffer.
////////////////////////////////////
char scpi_input_buffer[SCPI_INPUT_BUFFER_LENGTH];
char scpi_output_buffer[SCPI_INPUT_BUFFER_LENGTH];
size_t scpi_output_buffer_pos = 0;

size_t flushUART(TickType_t timeout = 10)
{
    size_t bytesSend = xMessageBufferSend(SCPIreturns, (void *)scpi_output_buffer, scpi_output_buffer_pos, timeout);
    xTaskNotifyGiveIndexed(taskUART, 0);

    debugMemorySCPIReturnsMinSpace = min(debugMemorySCPIReturnsMinSpace, xMessageBufferSpaceAvailable(SCPIreturns));
    if (bytesSend == 0)
    {
        // TODO: Generate an error on console/events or will scpi library handle this?
        debugMemorySCPIReturnsOverflows++;
    }
    else
    {
        // Clear buffer. FreeRTOS sends full buffer or not at all.
        scpi_output_buffer_pos = 0;
    }
    return bytesSend;
}

size_t sendUART(const char * data, size_t len)
{
    if (len == 0) { return 0; }
    size_t stored = 0;

    // If data won't fit, try to flush first.
    if ((scpi_output_buffer_pos + len) >= SCPI_INPUT_BUFFER_LENGTH) {
        // First flush if it doesn't fit in buffer
        size_t flushed = flushUART(100);
    }

    // If wew data fits in buffer then append it.
    if ((scpi_output_buffer_pos + len) < SCPI_INPUT_BUFFER_LENGTH) {
        memcpy(scpi_output_buffer + scpi_output_buffer_pos, data, len);
        scpi_output_buffer_pos = scpi_output_buffer_pos + len;
        stored = len;
    } 

    return stored;
}


// SCPI glue to UART functions above.
/////////////////////////////////////
size_t SCPI_Write(scpi_t * context, const char * data, size_t len) {
    return sendUART(data, len);
};

const size_t scpierrbufsize = 128;
char scpierrbuf[scpierrbufsize];
int SCPI_Error(scpi_t * context, int_fast16_t err) {   
    size_t len = 0;
    if (err == 0) {
        len = snprintf(scpierrbuf, scpierrbufsize, "%d, \"%s\"\n", err, SCPI_ErrorTranslate(err));
    } else {
        len = snprintf(scpierrbuf, scpierrbufsize, "**ERROR: %d, \"%s\"\n", err, SCPI_ErrorTranslate(err));
    }
    sendUART(scpierrbuf, len);
    return 0;
};

// TODO: Implement this.
scpi_result_t SCPI_Control(scpi_t * context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val) {
    if (SCPI_CTRL_SRQ == ctrl) {
        //SERIALDEBUG.printf("**SRQ: 0x%X (%d)\n", val, val); 
    } else {
        //SERIALDEBUG.printf("**CTRL %02x: 0x%X (%d)\n", ctrl, val, val);
    }
    return SCPI_RES_OK;
};

scpi_result_t SCPI_Reset(scpi_t * context) {
    state.setDefaults();
    // TODO: Remove, it's a SCPI command so no feedback.
    const char *msg = "**Reset\n";
    sendUART(msg, sizeof(msg));
    return SCPI_RES_OK;
};

scpi_result_t SCPI_Flush(scpi_t * context) {
    flushUART();
    return SCPI_RES_OK;
};
/////

// Helper list for MODE parsing
///////////////////////////////
 scpi_choice_def_t source_mode_list[] = {
     {"CC", mode_e_CC},
     {"CV", mode_e_CV},
     {"CR", mode_e_CR},
     {"CP", mode_e_CP},
     {"SHORT", mode_e_SHORT},
     {"DVM", mode_e_DVM},
     SCPI_CHOICE_LIST_END /* termination of option list */
};

// Helper lists & functions for NUMBER parsing including MIN,MAX,DEFault
////////////////////////////////////////////////////////////////////////
 scpi_choice_def_t number_specials[] = {
     {"MINimum", SCPI_NUM_MIN},
     {"MAXimum", SCPI_NUM_MAX},
     {"DEFault", SCPI_NUM_DEF},
     SCPI_CHOICE_LIST_END /* termination of option list */
};

// Min, Max, Default or float value within range with optional Unit suffix
bool get_value_from_param(scpi_t *context, const scpi_number_t &param, ranges_e range, float &value) 
{

    if (param.special) {
        if (param.content.tag == SCPI_NUM_MAX) {
            value = ranges[range].maxValue;
        } else if (param.content.tag == SCPI_NUM_MIN) {
            value = ranges[range].minValue;
        } else if (param.content.tag == SCPI_NUM_DEF) {
            value = ranges[range].defValue;
      //  } else if (param.content.tag == SCPI_NUM_UP && cv) {
      //      value = channel_dispatcher::getUSet(slotIndex, subchannelIndex) + cv->step;
      //      if (value > channel_dispatcher::getUMax(slotIndex, subchannelIndex))
      //          value = channel_dispatcher::getUMax(slotIndex, subchannelIndex);
      //  } else if (param.content.tag == SCPI_NUM_DOWN && cv) {
      //      value = channel_dispatcher::getUSet(slotIndex, subchannelIndex) - cv->step;
      //      if (value < channel_dispatcher::getUMin(slotIndex, subchannelIndex))
      //          value = channel_dispatcher::getUMin(slotIndex, subchannelIndex);
        } else {
            SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
            return false;
        }
    } else {
        if (param.unit != SCPI_UNIT_NONE && param.unit != ranges[range].scpi_unit) {
            SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
            return false;
        }

        value = (float)param.content.value;

        if (value < ranges[range].minValue || value > ranges[range].maxValue) {
            SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
            return false;
        }
    }
    return true;
};

// Helper lists & functions for RANGE parsing
/////////////////////////////////////////////
enum special_lowhigh {
    SCPI_LOWHIGH_LOW,
    SCPI_LOWHIGH_HIGH,
    SCPI_LOWHIGH_DEFAULT
};

scpi_choice_def_t range_specials[] = {
     {"Low", special_lowhigh::SCPI_LOWHIGH_LOW},
     {"High", special_lowhigh::SCPI_LOWHIGH_HIGH},
     {"DEFault", special_lowhigh::SCPI_LOWHIGH_DEFAULT},
     SCPI_CHOICE_LIST_END /* termination of option list */
};

// Low, High, Default or float value within one of the ranges with optional Unit suffix. Lower range has priority.
bool get_range_from_param(scpi_t *context, const scpi_number_t &param, ranges_e rangeLow, ranges_e rangeHigh, bool &rangeIsLow) 
{
    float value;

    if (param.special) {
        if (param.content.tag == SCPI_LOWHIGH_HIGH) {
            rangeIsLow = false;
        } else if (param.content.tag == SCPI_LOWHIGH_LOW) {
            rangeIsLow = true;
        } else if (param.content.tag == SCPI_NUM_DEF) {
            rangeIsLow = false;
        } else {
            SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
            return false;
        }
    } else {
        if (param.unit != SCPI_UNIT_NONE && param.unit != ranges[rangeLow].scpi_unit) {  // Unit of rangeLow == rangeHigh
            SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
            return false;
        }

        value = (float)param.content.value;

        if (value >= ranges[rangeLow].minValue && value <= ranges[rangeLow].maxValue) {
            // Value fits within lower range
            rangeIsLow = true;
        } else if (value >= ranges[rangeHigh].minValue && value <= ranges[rangeHigh].maxValue)
        {
            // Value fits within higher range
            rangeIsLow = false;
        } else {
            SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
            return false;
        }
    }
    return true;
};

// Helper list for SCPI watchdog type.
scpi_choice_def_t scpi_wdog_list[] = {
    {"ACTivity", dcl::WDogType::ACTIVITY},
    {"PET", dcl::WDogType::PET}
};

// Helper list for power line frequency parsing.
scpi_choice_def_t sense_plfreq_list[] = {
     {"50", 50},
     {"60", 60},
     SCPI_CHOICE_LIST_END /* termination of option list */
};

// Helper list for Von Latch types
scpi_choice_def_t von_latch_mode_list[] = {
     {"OFF", VonType_e::VonType_e_Unlatched},
     {"ON", VonType_e::VonType_e_Latched},
     {"INhibit", VonType_e::VonType_e_Inhibit},
     SCPI_CHOICE_LIST_END /* termination of option list */
};

scpi_choice_def_t cal_type_list[] = {
    {"IMONHigh", calType_e_Imon_High},
    {"IMONLow", calType_e_Imon_Low},
    {"UMONHigh", calType_e_Umon_High},
    {"UMONLow", calType_e_Umon_Low},
    {"ISETHigh", calType_e_Iset_High},
    {"ISETLow", calType_e_Iset_Low},
    {"USETHigh", calType_e_Uset_High},
    {"USETLow", calType_e_Uset_Low},
    {"VONHigh", calType_e_Von_High},
    {"VONLow", calType_e_Von_Low},
    {"OCPHigh", calType_e_OCPset_High},
    {"OCPLow", calType_e_OCPset_Low},
    {"OVPHigh", calType_e_OVPset_High},
    {"OVPLow", calType_e_OVPset_Low}
};

// Helper list for adc min/max request.
scpi_choice_def_t cal_adc_minmax[] = {
     {"MIN", 0},
     {"MAX", 1},
     SCPI_CHOICE_LIST_END /* termination of option list */
};

// Helper list for fan mode parsing.
scpi_choice_def_t fan_mode_list[] = {
     {"AUTO", true},
     {"MANual", false},
     SCPI_CHOICE_LIST_END /* termination of option list */
};

// Helper list for statistics queries parsing
scpi_choice_def_t stat_type_list[] = {
    {"ALL", 0},  // empty = default
    {"MIN", 1},
    {"MAX", 2},
    {"AVG", 3},
    {"COUNT", 4},
    SCPI_CHOICE_LIST_END
};

// Helper list for eeprom init
scpi_choice_def_t cal_init_list[] = {
    {"CURRent", 0},
    {"DEFault", 1},
    SCPI_CHOICE_LIST_END
};

//// SCPI COMMANDS
//////////////////


/**
 * *OPC
 * @param context
 * @return 
 */
scpi_result_t scpi_opc(scpi_t * context) {
    SCPI_RegSetBits(context, SCPI_REG_ESR, ESR_OPC);
    return SCPI_RES_OK;
}

/**
 * *OPC?
 * @param context
 * @return 
 */
scpi_result_t scpi_opcQ(scpi_t * context) {
    SCPI_ResultInt32(context, scpi_busy == 0);
    return SCPI_RES_OK;
}

scpi_result_t scpi_rst(scpi_t *context) {
    state.resetAllStates(); 
    changeScreen_s msg;
    msg.newScreen = SCREEN_ID_MAIN;
    msg.pop = false;
    xQueueSend(changeScreen, &msg, 100);
    return SCPI_RES_OK;
}

// Fetch current available data
///////////////////////////////

// CALIBRATION COMMANDS
scpi_result_t scpi_cmd_cal(scpi_t *context) {
    scpi_bool_t param1;

    if (!SCPI_ParamBool(context, &param1, TRUE)) {
         return SCPI_RES_ERR;
    }
   
    if (state.CalibrationMode(param1)) {
        return SCPI_RES_OK;
    } else {
        return SCPI_RES_ERR;
    };
};

scpi_result_t scpi_cmd_calQ(scpi_t *context)
{
    SCPI_ResultBool(context, state.getCalibrationMode());
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_cal_init_eeprom(scpi_t *context)
{
    if (!state.getCalibrationMode()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
    return SCPI_RES_ERR;
    }

    int32_t param;
    if (!SCPI_ParamChoice(context, cal_init_list, &param, TRUE)) {
        return SCPI_RES_ERR;
    }

    if (!myeeprom.magicWrite()) {
        return SCPI_RES_ERR;
    }

    bool res;
    scpi_busy_inc();

    if (param == 0) {
        res = calActions.storeAllValues();
    } else {
        res = calActions.storeDefaults();
    }
    scpi_busy_dec();
    if (res) { return SCPI_RES_OK; } 

    return SCPI_RES_ERR;
}

scpi_result_t scpi_cmd_cal_init_eepromQ(scpi_t *context)
{
    SCPI_ResultBool(context, myeeprom.magicFound());
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_cal_type(scpi_t *context) {
    int32_t param;

    if (!SCPI_ParamChoice(context, cal_type_list, &param, TRUE)) {
         return SCPI_RES_ERR;
    }

    if (!state.getCalibrationMode()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
        return SCPI_RES_ERR;
    }

    calActions.setCalType((calType_e)param);
    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_cal_typeQ(scpi_t *context)
{
    if (!state.getCalibrationMode()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
        return SCPI_RES_ERR;
    }

    SCPI_ResultUInt32(context, calActions.getCalType());
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_cal_point(scpi_t *context) {
    scpi_bool_t res;
    scpi_parameter_t param1;
    int32_t value = 0;

    if (!state.getCalibrationMode()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
        return SCPI_RES_ERR;
    }

    res = SCPI_Parameter(context, &param1, FALSE);

    if (res) {
        // Is parameter a number without suffix?
        if (SCPI_ParamIsNumber(&param1, FALSE)) {
            // Convert parameter to unsigned int. Result is in value.
            SCPI_ParamToInt32(context, &param1, &value);

            value = value - 1; // In UI and SCPI 1 based, in code 0 based.

            if (value >= 0 && value <= calActions.getNumPoints()) { 
                calActions.setCurPoint(value);
                return SCPI_RES_OK;
            } else {
                //SCPI_ErrorPushEx(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE, " valid range: 1-100", 0);
                SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
                return SCPI_RES_ERR;
            }; 

        } else {
            SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
            return SCPI_RES_ERR;
        }
    } else {
        SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
        return SCPI_RES_ERR;
    }
    SCPI_ErrorPush(context, SCPI_ERROR_PARAMETER_ERROR);
    return SCPI_RES_ERR;
};

scpi_result_t scpi_cmd_cal_pointQ(scpi_t *context) {
    if (!state.getCalibrationMode()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
        return SCPI_RES_ERR;
    }

    SCPI_ResultUInt32(context, calActions.getCurPoint() + 1);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_cal_point_maxQ(scpi_t *context) {
    if (!state.getCalibrationMode()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
        return SCPI_RES_ERR;
    }
    SCPI_ResultInt32(context, calActions.getNumPoints() );    
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_cal_set(scpi_t *context) {
    scpi_bool_t res;
    scpi_parameter_t param1;
    float value = 0;

    if (!state.getCalibrationMode()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
        return SCPI_RES_ERR;
    }

    res = SCPI_Parameter(context, &param1, FALSE);

    if (res) {
        // Is parameter a number without suffix?
        if (SCPI_ParamIsNumber(&param1, FALSE)) {
            // Convert parameter to unsigned int. Result is in value.
            SCPI_ParamToFloat(context, &param1, &value);

            
            if (value >= ranges[caldefaults[calActions.getCalType()].keyBoard].minValue && 
                value <= ranges[caldefaults[calActions.getCalType()].keyBoard].maxValue ) { 
                calActions.setSet(value);
                return SCPI_RES_OK;
            } else {
                //SCPI_ErrorPushEx(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE, " valid range: 1-100", 0);
                SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
                return SCPI_RES_ERR;
            }; 

        } else {
            SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
            return SCPI_RES_ERR;
        }
    } else {
        SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
        return SCPI_RES_ERR;
    }
    SCPI_ErrorPush(context, SCPI_ERROR_PARAMETER_ERROR);
    return SCPI_RES_ERR;
};

scpi_result_t scpi_cmd_cal_setQ(scpi_t *context) {
    if (!state.getCalibrationMode()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
        return SCPI_RES_ERR;
    }
    SCPI_ResultFloat(context, calActions.getSet());    
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_cal_measQ(scpi_t *context) {
    if (!state.getCalibrationMode()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
        return SCPI_RES_ERR;
    }
    SCPI_ResultFloat(context, calActions.getMeasured());    
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_cal_adcQ(scpi_t *context) {
    int32_t param;
    if (!state.getCalibrationMode()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
        return SCPI_RES_ERR;
    }

    if (!SCPI_ParamChoice(context, cal_adc_minmax, &param, TRUE)) {
         return SCPI_RES_ERR;
    }

    if (param == 0) {
        SCPI_ResultInt32(context, caldefaults[calActions.getCalType()].adcMin);
    } else {
        SCPI_ResultInt32(context, caldefaults[calActions.getCalType()].adcMax);     
    }
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_cal_meas(scpi_t *context) {
    // In calibration mode?
    if (!state.getCalibrationMode()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
        return SCPI_RES_ERR;
    }

    // Not already/still running?
    if (calActions.getTriggeredCalibration()) {
        return SCPI_RES_ERR;
    }

    // TODO replace with more advanced flow action call
    //scpi_busy_inc(); //Done in flow for now

    // Set DAC if DAC type.
    if (caldefaults[calActions.getCalType()].type == calCalType_e_DAC) {
        calActions.setDAC();
        vTaskDelay(1000);
    }

    calActions.setTriggeredCalibration(true);

    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_cal_meas_runQ(scpi_t *context) {
    SCPI_ResultBool(context, calActions.getTriggeredCalibration());
    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_cal_type_save(scpi_t *context) {
    if (!state.getCalibrationMode()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
        return SCPI_RES_ERR;
    }
/*    if (!calActions.getValuesChanged()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
        return SCPI_RES_ERR;
    }*/ //TODO: Remove? (removing allows for rewrite including CRC)
    calActions.storeValues();
    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_cal_type_reset(scpi_t *context) {
    if (!state.getCalibrationMode()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
        return SCPI_RES_ERR;
    }
    if (!calActions.getValuesChanged()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
        return SCPI_RES_ERR;
    }
    calActions.resetValues();
    return SCPI_RES_OK;
}

extern scpi_result_t scpi_cmd_deb_eeprom_clear(scpi_t *context) {
    scpi_busy_inc();
    if (myeeprom.fullWrite(0xff)) {
        scpi_busy_dec();
        return SCPI_RES_OK;
    } else {
        scpi_busy_dec();
        return SCPI_RES_ERR;
    }
};

extern scpi_result_t scpi_cmd_deb_flow_queueQ(scpi_t *context) {
    uint32_t q[] = { 0, 0};
    q[0] = eez::flow::getQueueSize();
    q[1] = eez::flow::getMaxQueueSize();
    q[2] = eez::flow::getTickMaxDurationCounter();
    SCPI_ResultArrayUInt32(context, q, 3, SCPI_FORMAT_ASCII);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_deb_mem_heapQ(scpi_t *context)
{
    uint32_t mem[] = { 0, 0, 0, 0};
    mem[0] = rp2040.getTotalHeap();
    mem[1] = rp2040.getUsedHeap();
    mem[2] = rp2040.getFreeHeap();
    SCPI_ResultArrayUInt32(context, mem, 3, SCPI_FORMAT_ASCII);
    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_deb_mem_lvmonQ(scpi_t *context)
{
    lv_mem_monitor_t lvmon;
    lv_mem_monitor(&lvmon);
    uint32_t mem[] = { 
        lvmon.total_size,
        lvmon.free_cnt,
        lvmon.free_size,
        lvmon.free_biggest_size,
        lvmon.used_cnt,
        lvmon.max_used,
        lvmon.used_pct,
        lvmon.frag_pct
    };
    SCPI_ResultArrayUInt32(context, mem, 8, SCPI_FORMAT_ASCII);
    return SCPI_RES_OK;
};


scpi_result_t scpi_cmd_deb_mem_queues_minQ(scpi_t *context)
{
    uint32_t q[] = { 0,1,2,3,4,5,6,7};
    q[0] = debugMemoryNewMeasurementsBuffMinSpace / (sizeof(newMeasurementMsg) + sizeof (size_t));
    q[1] = debugMemoryChangeMeasureTaskSettingsQMinSpace;
    q[2] = debugMemoryChangeAverageSettingsQMinSpace;
    q[3] = debugMemoryChangeHWIOSettingsQMinSpace;
    q[4] = debugMemoryChangeScreenQMinSpace;
    q[5] = debugMemoryBeeperQMinSpace;
    q[6] = debugMemorySCPIMessagesMinSpace;
    q[7] = debugMemorySCPIReturnsMinSpace;
    SCPI_ResultArrayUInt32(context, q, 8, SCPI_FORMAT_ASCII);
    return SCPI_RES_OK;
 }

scpi_result_t scpi_cmd_deb_mem_queues_overflowsQ(scpi_t *context)
{
    uint32_t q[] = { 0,1,2,3,4,5,6,7};
    q[0] = debugMemoryNewMeasurementsBuffOverflows;
    q[1] = debugMemoryChangeMeasureTaskSettingsQOverflows;
    q[2] = debugMemoryChangeAverageSettingsQOverflows;
    q[3] = debugMemoryChangeHWIOSettingsQOverflows;
    q[4] = debugMemoryChangeScreenQOverflows;
    q[5] = debugMemoryBeeperQOverflows;
    q[6] = debugMemorySCPIMessagesOverflows;
    q[7] = debugMemorySCPIMessagesOverflows;
    SCPI_ResultArrayUInt32(context, q, 8, SCPI_FORMAT_ASCII);
    return SCPI_RES_OK;
 }

scpi_result_t scpi_cmd_deb_reboot(scpi_t *context) {
    state.setOff();
    rp2040.restart();
    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_deb_iolinesQ(scpi_t *context) 
 {
    SCPI_ResultInt32(context, gpiopinstate);
    return SCPI_RES_OK;
 }

scpi_result_t scpi_cmd_deb_state_countQ(scpi_t *context)
{
    measuredStateStruct mstate; 
    setStateStruct sstate;

    state.getMeasuredStateCopy(&mstate, 100);
    state.getSetStateCopy(&sstate, 100);

    const uint64_t count_array[] = { sstate.sCount, mstate.sCount, mstate.sCountFromAverage, mstate.sCountFromHWIO};
    SCPI_ResultArrayUInt64(context, count_array, 4, SCPI_FORMAT_ASCII);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_deb_tasks_prioQ(scpi_t *context)
{
    uint32_t q[] = { 0,0,0,0,0,0,0,0,0,0,0,0};
    q[0] = uxTaskPriorityGet(taskWatchdog);
    q[1] = uxTaskPriorityGet(taskMeasureAndOutput);
    q[2] = uxTaskPriorityGet(taskAveraging);
    q[3] = uxTaskPriorityGet(taskProtHW);
    q[4] = uxTaskPriorityGet(encTaskHandle);
    q[5] = uxTaskPriorityGet(xTimerGetTimerDaemonTaskHandle());
    q[6] = uxTaskPriorityGet(guiTaskHandle);
    q[7] = uxTaskPriorityGet(taskLoop);
    q[8] = uxTaskPriorityGet(taskUART);
    q[9] = uxTaskPriorityGet(taskBeep);
    q[10] = uxTaskPriorityGet(xTaskGetIdleTaskHandleForCore(0));
    q[11] = uxTaskPriorityGet(xTaskGetIdleTaskHandleForCore(1));

    SCPI_ResultArrayUInt32(context, q, 12, SCPI_FORMAT_ASCII);
    return SCPI_RES_OK;
 }

scpi_result_t scpi_cmd_deb_tasks_runtimeQ(scpi_t *context)
{
    uint32_t q[] = { 0,0,0,0,0,0,0,0,0,0,0};
    q[0] = ulTaskGetRunTimeCounter(taskWatchdog);
    q[1] = ulTaskGetRunTimeCounter(taskMeasureAndOutput);
    q[2] = ulTaskGetRunTimeCounter(taskAveraging);
    q[3] = ulTaskGetRunTimeCounter(taskProtHW);
    q[4] = ulTaskGetRunTimeCounter(encTaskHandle);
    q[5] = ulTaskGetRunTimeCounter(xTimerGetTimerDaemonTaskHandle());
    q[6] = ulTaskGetRunTimeCounter(guiTaskHandle);
    q[7] = ulTaskGetRunTimeCounter(taskLoop);
    q[8] = ulTaskGetRunTimeCounter(taskUART);
    q[9] = ulTaskGetRunTimeCounter(taskBeep);
    q[10] = ulTaskGetRunTimeCounter(xTaskGetIdleTaskHandleForCore(0));
    q[11] = ulTaskGetRunTimeCounter(xTaskGetIdleTaskHandleForCore(1));

    SCPI_ResultArrayUInt32(context, q, 12, SCPI_FORMAT_ASCII);
    return SCPI_RES_OK;
 }

scpi_result_t scpi_cmd_deb_tasks_stackhwQ(scpi_t *context)
{
    uint32_t q[] = { 0,0,0,0,0,0,0,0,0,0,0};
    q[0] = uxTaskGetStackHighWaterMark(taskWatchdog);
    q[1] = uxTaskGetStackHighWaterMark(taskMeasureAndOutput);
    q[2] = uxTaskGetStackHighWaterMark(taskAveraging);
    q[3] = uxTaskGetStackHighWaterMark(taskProtHW);
    q[4] = uxTaskGetStackHighWaterMark(encTaskHandle);
    q[5] = uxTaskGetStackHighWaterMark(xTimerGetTimerDaemonTaskHandle());
    q[6] = uxTaskGetStackHighWaterMark(guiTaskHandle);
    q[7] = uxTaskGetStackHighWaterMark(taskLoop);
    q[8] = uxTaskGetStackHighWaterMark(taskUART);
    q[9] = uxTaskGetStackHighWaterMark(taskBeep);
    q[10] = uxTaskGetStackHighWaterMark(xTaskGetIdleTaskHandleForCore(0));
    q[11] = uxTaskGetStackHighWaterMark(xTaskGetIdleTaskHandleForCore(1));

    SCPI_ResultArrayUInt32(context, q, 12, SCPI_FORMAT_ASCII);
    return SCPI_RES_OK;
 }

 


scpi_result_t scpi_cmd_deb_wdog_thres_maxQ(scpi_t *context) {
    const uint32_t thres_array[] = { 0, watchdogMeasureAndOutputMax, watchdogAveragingMax, watchdogProtHWMax, watchdogEncTaskMax, 
                                    watchdogGuiTimerFunctionMax, watchdogGuiTaskMax, 
                                     watchdogLoopMax, watchdogUARTMax, 0, 0, 0};
    SCPI_ResultArrayUInt32(context, thres_array, 12, SCPI_FORMAT_ASCII );
    return SCPI_RES_OK;
}

// FETCH commands
scpi_result_t scpi_cmd_fetch_current(scpi_t *context) {
    char buffer[64] = { 0 };
    measuredStateStruct localMeasuredState; 
    state.getMeasuredStateCopy(&localMeasuredState, 1000);

    SCPI_FloatToStr(localMeasuredState.Imon,buffer,sizeof(buffer));
    SCPI_ResultCharacters(context, buffer, strlen(buffer));
    return SCPI_RES_OK;
};

scpi_result_t stat_param(scpi_t *context, uint32_t param, measureStat stats)
{
    const float stat_array[] = { (float)stats.min, (float)stats.avg, 
                                 (float)stats.max, (float)stats.count};

    switch(param)
    {
        case 0:
            SCPI_ResultArrayFloat(context, stat_array, 4, SCPI_FORMAT_ASCII);            
            break;
        case 1:
            SCPI_ResultFloat(context, stats.min);
            break;
        case 2:
            SCPI_ResultFloat(context, stats.max);
            break;
        case 3:
            SCPI_ResultFloat(context, stats.avg);
            break;
        case 4:
            SCPI_ResultUInt32(context, stats.count);
            break;
        default:
            return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_fetch_curr_statQ(scpi_t *context) {
    scpi_parameter_t scpi_param;
    int32_t param;
    float value;
    measuredStateStruct mstate; 

    state.getMeasuredStateCopy(&mstate, 1000);

    if (!SCPI_ParamChoice(context, stat_type_list, &param, false)) {
        if (SCPI_ParamErrorOccurred(context) ) {
            return SCPI_RES_ERR;
        } else {
            // No error, no parameter, so default (ALL)
            param = 0;
        }
    }
    return stat_param(context, param, mstate.ImonStats);
}


scpi_result_t scpi_cmd_fetch_voltage(scpi_t *context) {
    char buffer[64] = { 0 };
    measuredStateStruct localMeasuredState; 
    state.getMeasuredStateCopy(&localMeasuredState, 1000);

    SCPI_FloatToStr(localMeasuredState.Umon,buffer,sizeof(buffer));
    SCPI_ResultCharacters(context, buffer, strlen(buffer));
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_fetch_volt_statQ(scpi_t *context) {
    int32_t param;
    float value;

    measuredStateStruct mstate; 
    state.getMeasuredStateCopy(&mstate, 1000);

    if (!SCPI_ParamChoice(context, stat_type_list, &param, false)) {
        if (SCPI_ParamErrorOccurred(context) ) {
            return SCPI_RES_ERR;
        } else {
            // No error, no parameter, so default (ALL)
            param = 0;
        }
    }

    return stat_param(context, param, mstate.UmonStats);
}

scpi_result_t scpi_cmd_fetch_volt_revQ(scpi_t *context)
{
    SCPI_ResultBool(context,state.getReversePolarityNow());
    return SCPI_RES_OK;
}


scpi_result_t scpi_cmd_fetch_power(scpi_t *context) {
    char buffer[64] = { 0 };
    measuredStateStruct localMeasuredState; 
    state.getMeasuredStateCopy(&localMeasuredState, 1000);

    SCPI_FloatToStr(localMeasuredState.Imon * localMeasuredState.Umon,buffer,sizeof(buffer));
    SCPI_ResultCharacters(context, buffer, strlen(buffer));
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_fetch_pow_statQ(scpi_t *context) {
    int32_t param;
    float value;
    measuredStateStruct mstate; 

    state.getMeasuredStateCopy(&mstate, 1000);

    if (!SCPI_ParamChoice(context, stat_type_list, &param, false)) {
        if (SCPI_ParamErrorOccurred(context) ) {
            return SCPI_RES_ERR;
        } else {
            // No error, no parameter, so default (ALL)
            param = 0;
        }
    }

    return stat_param(context, param, mstate.PmonStats);
}

scpi_result_t scpi_cmd_fetch_cap(scpi_t *context) {
    measuredStateStruct localMeasuredState; 
    state.getMeasuredStateCopy(&localMeasuredState, 1000);
    const float cap_array[] = { (float)localMeasuredState.As / 3600.0f, (float)localMeasuredState.Ws / 3600.0f, (float)localMeasuredState.Ptime};
    SCPI_ResultArrayFloat(context, cap_array, 3, SCPI_FORMAT_ASCII );
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_sense_curr_stat(scpi_t *context)
{
    scpi_bool_t param1;

    if (!SCPI_ParamBool(context, &param1, TRUE)) {
         return SCPI_RES_ERR;
    }
   
    if (state.setImonStat(param1)) {
        return SCPI_RES_OK;
    } else {
        return SCPI_RES_ERR;
    };
};

// MEASure commands
scpi_result_t measurement(scpi_t *context, scpi_result_t (fetch)(scpi_t *)) 
{
    uint64_t s = state.startMeasurement();
    uint32_t u = 0;

    if ( s == 0) {
        // TODO: Add specific error message (can't initiate measurment)
        return SCPI_RES_ERR;
    }
    
    while(true) 
    {
        if (state.getMeasuredSCount() == s)
        {
            // Just fetch command
            return fetch(context);
        }
        vTaskDelay(5);
        u++;
        if (u > 1000) 
        {
            // TODO add specific eror messages (timeout on measurement)
            return SCPI_RES_ERR;
        }
    }
};

scpi_result_t scpi_cmd_meas_currQ(scpi_t *context)
{
    return measurement(context, scpi_cmd_fetch_current);
}; 

scpi_result_t scpi_cmd_meas_voltQ(scpi_t *context)
{
    return measurement(context, scpi_cmd_fetch_voltage);
};

scpi_result_t scpi_cmd_meas_powQ(scpi_t *context)
{
    return measurement(context, scpi_cmd_fetch_power);
};

scpi_result_t scpi_cmd_sense_curr_statQ(scpi_t *context)
{
    SCPI_ResultBool(context, state.getImonStat());
    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sense_curr_stat_clear(scpi_t *context) 
{
    if (state.clearImonStat()) {
        return SCPI_RES_OK;
    }

    SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
    return SCPI_RES_ERR;
}

scpi_result_t scpi_cmd_sense_nplc(scpi_t *context)
{
    scpi_bool_t res;
    scpi_parameter_t param1;
    uint32_t value = 0;

    res = SCPI_Parameter(context, &param1, FALSE);

    if (res) {
        // Is parameter a number without suffix?
        if (SCPI_ParamIsNumber(&param1, FALSE)) {
            // Convert parameter to unsigned int. Result is in value.
            SCPI_ParamToUInt32(context, &param1, &value);

            if (value >= 1 && value <= 100) {
                state.setNPLC(value);
                return SCPI_RES_OK;
            } else {
                //SCPI_ErrorPushEx(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE, " valid range: 1-100", 0);
                SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
                return SCPI_RES_ERR;
            }; 

        } else {
            SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
            return SCPI_RES_ERR;
        }
    } else {
        SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
        return SCPI_RES_ERR;
    }
    SCPI_ErrorPush(context, SCPI_ERROR_PARAMETER_ERROR);
    return SCPI_RES_ERR;
};

scpi_result_t scpi_cmd_sense_nplcQ(scpi_t *context)
{
    SCPI_ResultUInt32(context,state.getNPLC());
    return SCPI_RES_OK;
};


extern scpi_result_t scpi_cmd_sense_plfreq(scpi_t *context) 
{
    scpi_bool_t res;
    scpi_parameter_t param1;
    uint32_t value = 0;

    res = SCPI_Parameter(context, &param1, FALSE);
    if (!res) {
        SCPI_ErrorPush(context, SCPI_ERROR_PARAMETER_ERROR);
        return SCPI_RES_ERR;
    };

    if (SCPI_ParamIsNumber(&param1, FALSE)) {
        // Convert parameter to unsigned int. Result is in value.
        SCPI_ParamToUInt32(context, &param1, &value);

        if (value == 50 || value == 60) {
                if (state.setPLFreq(value)) {
                    return SCPI_RES_OK;
                } else {
                    SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
                    return SCPI_RES_ERR;
                };
        } 
    }
    SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
    return SCPI_RES_ERR;
};

scpi_result_t scpi_cmd_sense_plfreqQ(scpi_t *context)
{
    SCPI_ResultUInt32(context, state.getPLFreq());
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_sense_volt_stat(scpi_t *context)
{
    scpi_bool_t param1;

    if (!SCPI_ParamBool(context, &param1, TRUE)) {
         return SCPI_RES_ERR;
    }
   
    if (state.setUmonStat(param1)) {
        return SCPI_RES_OK;
    } else {
        return SCPI_RES_ERR;
    };
};

scpi_result_t scpi_cmd_sense_volt_statQ(scpi_t *context)
{
    SCPI_ResultBool(context, state.getUmonStat());
    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sense_volt_stat_clear(scpi_t *context) 
{
    if (state.clearUmonStat()) {
        return SCPI_RES_OK;
    }

    SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
    return SCPI_RES_ERR;
}

scpi_result_t scpi_cmd_sense_pow_stat(scpi_t *context)
{
    scpi_bool_t param1;

    if (!SCPI_ParamBool(context, &param1, TRUE)) {
         return SCPI_RES_ERR;
    }
   
    if (state.setPmonStat(param1)) {
        return SCPI_RES_OK;
    } else {
        return SCPI_RES_ERR;
    };
};

scpi_result_t scpi_cmd_sense_pow_statQ(scpi_t *context)
{
    SCPI_ResultBool(context, state.getPmonStat());
    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sense_pow_stat_clear(scpi_t *context) 
{
    if (state.clearPmonStat()) {
        return SCPI_RES_OK;
    }

    SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
    return SCPI_RES_ERR;
}

scpi_result_t scpi_cmd_sense_volt_remote(scpi_t *context)
{
    scpi_bool_t param1;

    if (!SCPI_ParamBool(context, &param1, TRUE)) {
         return SCPI_RES_ERR;
    }
   
    if (state.setVoltSense(param1)) {
        return SCPI_RES_OK;
    } else {
        return SCPI_RES_ERR;
    };
}

scpi_result_t scpi_cmd_sense_volt_remoteQ(scpi_t *context)
{
    SCPI_ResultBool(context, state.getVoltSense());
    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_sense_volt_remote_errorQ(scpi_t *context)
{
    measuredStateStruct localMeasuredState; 
    state.getMeasuredStateCopy(&localMeasuredState, 1000);

    SCPI_ResultBool(context, localMeasuredState.SenseError);
    return SCPI_RES_OK;
}

 // SOURCE commands

scpi_result_t scpi_cmd_source_input_state(scpi_t *context){
    scpi_bool_t param1;

    if (!SCPI_ParamBool(context, &param1, TRUE)) {
         return SCPI_RES_ERR;
    }

    bool result = false;
    if (param1 == true) 
    {
        result = state.setOn();
    } else {
        result = state.setOff();
    }
    if (result)
        return SCPI_RES_OK;
    else 
        return SCPI_RES_ERR;
};

scpi_result_t scpi_cmd_source_input_stateQ(scpi_t *context)
{
    setStateStruct localSetState; 
    state.getSetStateCopy(&localSetState, 1000);
    SCPI_ResultBool(context, localSetState.on);
    return SCPI_RES_OK;
};


scpi_result_t scpi_cmd_source_mode(scpi_t *context)
{
     int32_t param;

     if (!SCPI_ParamChoice(context, source_mode_list, &param, TRUE)) {
         return SCPI_RES_ERR;
     }

     if (!state.setMode((mode_e)param)) {
        SCPI_ErrorPush(context, SCPI_ERROR_POWER_ON);
        return SCPI_RES_ERR;
     };

    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_source_modeQ(scpi_t *context)
{
     const char * name;
     mode_e mode;

    setStateStruct localSetState; 
    state.getSetStateCopy(&localSetState, 1000);

    // this maps the state modes to the UI modes which are also the SCPI modes...
    switch (localSetState.mode)
    {
        case ELmode::CC:
            mode = mode_e_CC;
            break;
        case ELmode::CV:
            mode = mode_e_CV;
            break;
        case ELmode::CR:
            mode = mode_e_CR;
            break;
        case ELmode::CP:
            mode = mode_e_CP;
            break;
        case ELmode::SHORT:
            mode = mode_e_SHORT;
            break;
        case ELmode::DVM:
            mode = mode_e_DVM;
            break;
        default:
            mode = mode_e_CC;
            break;
    }

     SCPI_ChoiceToName(source_mode_list, mode, &name);
     SCPI_ResultCharacters(context, name, strlen(name));

    return SCPI_RES_OK;   
}

scpi_result_t scpi_cmd_source_input_prot_clear(scpi_t *context) 
{
    if (state.clearProtection()) {
        return SCPI_RES_OK;
    }

    SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
    return SCPI_RES_ERR;
}

scpi_result_t scpi_cmd_source_input_prot_tripQ(scpi_t *context)
{
    setStateStruct localSetState;
    measuredStateStruct localMeasureState;

    state.getSetStateCopy(&localSetState, 1000);
    state.getMeasuredStateCopy(&localMeasureState, 1000);

    bool res = localMeasureState.protection || localMeasureState.OCPstate || localMeasureState.OVPstate || 
               localMeasureState.OPPstate || localMeasureState.OTPstate || localMeasureState.PolarityError;
    SCPI_ResultBool(context, res);
    return SCPI_RES_OK;    
};

scpi_result_t scpi_cmd_source_input_prot_trip_revQ(scpi_t *context)
{
    SCPI_ResultBool(context,state.getReversePolarityTriggered());
    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_source_input_prot_wdog(scpi_t *context) {
    scpi_bool_t param1;
    if (!SCPI_ParamBool(context, &param1, TRUE)) {
         return SCPI_RES_ERR;
    }
    if (!state.setSCPIWdog(param1)) {
        SCPI_ErrorPush(context, SCPI_ERROR_EXECUTION_ERROR);
        return SCPI_RES_ERR;
    };
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_input_prot_wdogQ(scpi_t *context) {
    SCPI_ResultBool(context, state.getSCPIWdog());
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_input_prot_wdog_clear(scpi_t *context) {
    if (!state.SCPIWdogClear()) {
        return SCPI_RES_ERR;
    };
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_input_prot_wdog_del(scpi_t *context) {
    scpi_parameter_t param;
    scpi_number_t    scpi_number;
    scpi_special_number_t scpi_special;
    float value;
    ranges_e range;

    // Parse command to number type
    if (!SCPI_ParamNumber(context, number_specials, &scpi_number, TRUE)) {
        return SCPI_RES_ERR;
    }

    // translate number type to real value depending on range definition
    if (!get_value_from_param(context, scpi_number, ranges_e_WatchdogDelay, value)) {
        return SCPI_RES_ERR;
    };

    state.setSCPIWdogDelay((int32_t)value);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_input_prot_wdog_delQ(scpi_t *context) {
    SCPI_ResultUInt32(context, state.getSCPIWdogDelay());
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_input_prot_wdog_pet(scpi_t *context) {
    if (!state.SCPIWdogPet()) {
        SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
        return SCPI_RES_ERR;
    };
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_input_prot_wdog_type(scpi_t *context) {
    int32_t param;
    if (!SCPI_ParamChoice(context, scpi_wdog_list, &param, TRUE)) {
        return SCPI_RES_ERR;
    }
    if (!state.setSCPIWdogType((WDogType)param)) {
        SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
        return SCPI_RES_ERR;
    };
    return SCPI_RES_OK;
};
scpi_result_t scpi_cmd_source_input_prot_wdog_typeQ(scpi_t *context) {
    SCPI_ResultUInt8(context, state.getSCPIWdogType());
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_input_prot_wdog_tripQ(scpi_t *context) {
    SCPI_ResultBool(context, state.getSCPIWdogTripped());
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_cap(scpi_t *context) {
    scpi_bool_t param1;
    if (!SCPI_ParamBool(context, &param1, TRUE)) {
         return SCPI_RES_ERR;
    }
    if (!state.record(param1)) {
        SCPI_ErrorPush(context, SCPI_ERROR_EXECUTION_ERROR);
        return SCPI_RES_ERR;
    };
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_capQ(scpi_t *context) {
    setStateStruct localSetState; 
    state.getSetStateCopy(&localSetState, 1000);
    SCPI_ResultBool(context, localSetState.record);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_cap_zero(scpi_t *context) {
    if (!state.clearPower()) {
        SCPI_ErrorPush(context, SCPI_ERROR_EXECUTION_ERROR);
        return SCPI_RES_ERR;
    };
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_cap_limit_clear(scpi_t *context) {
    if (!state.clearCapacityLimit()) {
        SCPI_ErrorPush(context, SCPI_ERROR_EXECUTION_ERROR);
        return SCPI_RES_ERR;
    };
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_cap_limit_tripQ(scpi_t *context) {
    setStateStruct localSetState; 
    state.getSetStateCopy(&localSetState, 1000);
    SCPI_ResultBool(context, localSetState.capacityLimit);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_cap_limit(scpi_t *context) {
    scpi_bool_t param1;
    if (!SCPI_ParamBool(context, &param1, TRUE)) {
         return SCPI_RES_ERR;
    }
    if (!state.record(param1)) {
        SCPI_ErrorPush(context, SCPI_ERROR_EXECUTION_ERROR);
        return SCPI_RES_ERR;
    };
    state.setCapacityLimitEnabled((bool)param1);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_cap_limitQ(scpi_t *context) {
    setStateStruct localSetState; 
    state.getSetStateCopy(&localSetState, 1000);
    SCPI_ResultBool(context, localSetState.capacityLimitEnabled);
    return SCPI_RES_OK;
};


char error_not_implemented[] = { "Command not implemented" };

scpi_result_t scpi_cmd_source_cap_ahstop(scpi_t *context) {
    scpi_parameter_t param;
    scpi_number_t    scpi_number;
    scpi_special_number_t scpi_special;
    float value;
    ranges_e range = ranges_e::ranges_e_AHStop;

    // Parse command to number type
    if (!SCPI_ParamNumber(context, number_specials, &scpi_number, TRUE)) {
        return SCPI_RES_ERR;
    }

    // translate number type to real value depending on range definition
    if (!get_value_from_param(context, scpi_number, range, value)) {
        return SCPI_RES_ERR;
    };

    if (!state.setCapAhStop(value)) {
        SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
        return SCPI_RES_ERR;
    };

    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_cap_ahstopQ(scpi_t *context) {
    char buffer[64] = { 0 };
    setStateStruct localSetState; 
    state.getSetStateCopy(&localSetState, 1000);

    SCPI_FloatToStr(localSetState.CapAhStop,buffer,sizeof(buffer));
    SCPI_ResultCharacters(context, buffer, strlen(buffer));
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_cap_whstop(scpi_t *context) {
    scpi_parameter_t param;
    scpi_number_t    scpi_number;
    scpi_special_number_t scpi_special;
    float value;
    ranges_e range = ranges_e::ranges_e_WHStop;

    // Parse command to number type
    if (!SCPI_ParamNumber(context, number_specials, &scpi_number, TRUE)) {
        return SCPI_RES_ERR;
    }

    // translate number type to real value depending on range definition
    if (!get_value_from_param(context, scpi_number, range, value)) {
        return SCPI_RES_ERR;
    };

    if (!state.setCapWhStop(value)) {
        SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
        return SCPI_RES_ERR;
    };

    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_cap_whstopQ(scpi_t *context) {
    char buffer[64] = { 0 };
    setStateStruct localSetState; 
    state.getSetStateCopy(&localSetState, 1000);

    SCPI_FloatToStr(localSetState.CapWhStop,buffer,sizeof(buffer));
    SCPI_ResultCharacters(context, buffer, strlen(buffer));
    return SCPI_RES_OK;
};


scpi_result_t scpi_cmd_source_cap_timestop(scpi_t *context) {
    scpi_parameter_t param;
    scpi_number_t    scpi_number;
    scpi_special_number_t scpi_special;
    float value;
    ranges_e range = ranges_e::ranges_e_TimeStop;

    // Parse command to number type
    if (!SCPI_ParamNumber(context, number_specials, &scpi_number, TRUE)) {
        return SCPI_RES_ERR;
    }

    // translate number type to real value depending on range definition
    if (!get_value_from_param(context, scpi_number, range, value)) {
        return SCPI_RES_ERR;
    };

    if (!state.setCapTimeStop(value)) {
        SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
        return SCPI_RES_ERR;
    };

    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_cap_timestopQ(scpi_t *context) {
    setStateStruct localSetState; 
    state.getSetStateCopy(&localSetState, 1000);
    SCPI_ResultFloat(context, localSetState.CapTimeStop);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_cap_voltstop(scpi_t *context) {
    scpi_parameter_t param;
    scpi_number_t    scpi_number;
    scpi_special_number_t scpi_special;
    float value;
    ranges_e range = ranges_e::ranges_e_VoltStop;

    // Parse command to number type
    if (!SCPI_ParamNumber(context, number_specials, &scpi_number, TRUE)) {
        return SCPI_RES_ERR;
    }

    // translate number type to real value depending on range definition
    if (!get_value_from_param(context, scpi_number, range, value)) {
        return SCPI_RES_ERR;
    };

    if (!state.setCapVoltStop(value)) {
        SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
        return SCPI_RES_ERR;
    };

    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_cap_voltstopQ(scpi_t *context) {
    setStateStruct localSetState; 
    state.getSetStateCopy(&localSetState, 1000);
    SCPI_ResultFloat(context, localSetState.CapVoltStop);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_current(scpi_t *context)
{
    scpi_parameter_t param;
    scpi_number_t    scpi_number;
    scpi_special_number_t scpi_special;
    float value;
    ranges_e range;

    if (state.getRangeCurrentLow()) 
    {
        range = ranges_e::ranges_e_Curr_Low;
    } else {
        range = ranges_e::ranges_e_Curr_High;
    };

    // Parse command to number type
    if (!SCPI_ParamNumber(context, number_specials, &scpi_number, TRUE)) {
        return SCPI_RES_ERR;
    }

    // translate number type to real value depending on range definition
    if (!get_value_from_param(context, scpi_number, range, value)) {
        return SCPI_RES_ERR;
    };

    if (!state.setIset(value)) {
        SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
        return SCPI_RES_ERR;
    };

    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_currentQ(scpi_t *context)
{
    setStateStruct localSetState;
    state.getSetStateCopy(&localSetState, 1000);
    
    SCPI_ResultFloat(context, localSetState.Iset);
    return SCPI_RES_OK;
};


scpi_result_t scpi_cmd_source_current_prot_level(scpi_t *context)
{
    scpi_parameter_t param;
    scpi_number_t    scpi_number;
    scpi_special_number_t scpi_special;
    float value;
    ranges_e range;

    if (state.getRangeCurrentLow()) 
    {
        range = ranges_e::ranges_e_OCP_Low;
    } else {
        range = ranges_e::ranges_e_OCP_High;
    };

    // Parse command to number type
    if (!SCPI_ParamNumber(context, number_specials, &scpi_number, TRUE)) {
        return SCPI_RES_ERR;
    }

    // translate number type to real value depending on range definition
    if (!get_value_from_param(context, scpi_number, range, value)) {
        return SCPI_RES_ERR;
    };

    if (!state.setOCP(value)) {
        SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
        return SCPI_RES_ERR;
    };

    return SCPI_RES_OK;

};

scpi_result_t scpi_cmd_source_current_prot_levelQ(scpi_t *context)
{
    setStateStruct localSetState;
    state.getSetStateCopy(&localSetState, 1000);
    
    SCPI_ResultFloat(context, localSetState.OCPset);
    return SCPI_RES_OK;
};


scpi_result_t scpi_cmd_source_current_range(scpi_t *context) {
    scpi_parameter_t param;
    scpi_number_t    scpi_number;
    bool rangeIsLow;
    ranges_e rangeLow = ranges_e::ranges_e_Curr_Low;
    ranges_e rangeHigh = ranges_e::ranges_e_Curr_High;

    // Parse command to number type
    if (!SCPI_ParamNumber(context, range_specials, &scpi_number, TRUE)) {
        return SCPI_RES_ERR;
    }

    // translate number type to real value depending on range definition
    if (!get_range_from_param(context, scpi_number, rangeLow, rangeHigh, rangeIsLow)) {
        return SCPI_RES_ERR;
    };

    if (!state.setRangeCurrent(rangeIsLow)) {
        SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
        return SCPI_RES_ERR;
    };

    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_current_rangeQ(scpi_t *context) {
    SCPI_ResultCharacters(context, state.getRangeCurrentLow() ? "L" : "H", 1);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_voltage(scpi_t *context)
{
    scpi_parameter_t param;
    scpi_number_t    scpi_number;
    scpi_special_number_t scpi_special;
    float value;
    ranges_e range;

    if (state.getRangeVoltageLow()) 
    {
        range = ranges_e::ranges_e_Volt_Low;
    } else {
        range = ranges_e::ranges_e_Volt_High;
    };
    // Parse command to number type
    if (!SCPI_ParamNumber(context, number_specials, &scpi_number, TRUE)) {
        return SCPI_RES_ERR;
    }
    // translate number type to real value depending on range definition
    if (!get_value_from_param(context, scpi_number, range, value)) {
        return SCPI_RES_ERR;
    };
    if (!state.setUset(value)) {
        SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
        return SCPI_RES_ERR;
    };
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_voltageQ(scpi_t *context)
{
    setStateStruct localSetState;
    state.getSetStateCopy(&localSetState, 1000);
    
    SCPI_ResultFloat(context, localSetState.Uset);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_voltage_on(scpi_t *context) {
    scpi_parameter_t param;
    scpi_number_t    scpi_number;
    scpi_special_number_t scpi_special;
    float value;
    ranges_e range;

    if (state.getRangeVoltageLow()) 
    {
        range = ranges_e::ranges_e_Von_Low;
    } else {
        range = ranges_e::ranges_e_Von_High;
    };
    // Parse command to number type
    if (!SCPI_ParamNumber(context, number_specials, &scpi_number, TRUE)) {
        return SCPI_RES_ERR;
    }
    // translate number type to real value depending on range definition
    if (!get_value_from_param(context, scpi_number, range, value)) {
        return SCPI_RES_ERR;
    };
    if (!state.setVonset(value)) {
        SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
        return SCPI_RES_ERR;
    };
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_voltage_onQ(scpi_t *context) {
    setStateStruct localSetState;
    state.getSetStateCopy(&localSetState, 1000);
    
    SCPI_ResultFloat(context, localSetState.VonSet);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_voltage_on_latch(scpi_t *context) {
    int32_t param;
    if (!SCPI_ParamChoice(context, von_latch_mode_list, &param, TRUE)) {
        return SCPI_RES_ERR;
    }
    if (!state.setVonLatched((VonType_e)param)) {
        SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
        return SCPI_RES_ERR;
    };
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_voltage_on_latchQ(scpi_t *context) {
    setStateStruct localSetState;
    state.getSetStateCopy(&localSetState, 1000);
    
    SCPI_ResultInt8(context, localSetState.VonLatched);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_voltage_prot_level(scpi_t *context)
{
    scpi_parameter_t param;
    scpi_number_t    scpi_number;
    scpi_special_number_t scpi_special;
    float value;
    ranges_e range;

    if (state.getRangeVoltageLow()) 
    {
        range = ranges_e::ranges_e_OVP_Low;
    } else {
        range = ranges_e::ranges_e_OVP_High;
    };
    // Parse command to number type
    if (!SCPI_ParamNumber(context, number_specials, &scpi_number, TRUE)) {
        return SCPI_RES_ERR;
    }
    // translate number type to real value depending on range definition
    if (!get_value_from_param(context, scpi_number, range, value)) {
        return SCPI_RES_ERR;
    };
    if (!state.setOVP(value)) {
        SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
        return SCPI_RES_ERR;
    };
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_voltage_prot_levelQ(scpi_t *context)
{
    setStateStruct localSetState;
    state.getSetStateCopy(&localSetState, 1000);
    
    SCPI_ResultFloat(context, localSetState.OVPset);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_voltage_range(scpi_t *context) {
    scpi_parameter_t param;
    scpi_number_t    scpi_number; 
    bool rangeIsLow;
    ranges_e rangeLow = ranges_e_Volt_Low;
    ranges_e rangeHigh = ranges_e_Volt_High;

    // Parse command to number type
    if (!SCPI_ParamNumber(context, range_specials, &scpi_number, TRUE)) {
        return SCPI_RES_ERR;
    }
    // translate number type to real value depending on range definition
    if (!get_range_from_param(context, scpi_number, rangeLow, rangeHigh, rangeIsLow)) {
        return SCPI_RES_ERR;
    };
    if (!state.setRangeVoltage(rangeIsLow)) {
        SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
        return SCPI_RES_ERR;
    };
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_voltage_rangeQ(scpi_t *context) {
    SCPI_ResultCharacters(context, state.getRangeVoltageLow() ? "L" : "H", 1);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_res(scpi_t *context)
{
    scpi_parameter_t param;
    scpi_number_t    scpi_number;
    scpi_special_number_t scpi_special;
    float value;
    ranges_e range = ranges_e::ranges_e_Res;

    // Parse command to number type
    if (!SCPI_ParamNumber(context, number_specials, &scpi_number, TRUE)) {
        return SCPI_RES_ERR;
    }
    // translate number type to real value depending on range definition
    if (!get_value_from_param(context, scpi_number, range, value)) {
        return SCPI_RES_ERR;
    };
    if (!state.setRset(value)) {
        SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
        return SCPI_RES_ERR;
    };
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_resQ(scpi_t *context)
{
    setStateStruct localSetState;
    state.getSetStateCopy(&localSetState, 1000);
    
    SCPI_ResultFloat(context, localSetState.Rset);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_pow(scpi_t *context)
{
    scpi_parameter_t param;
    scpi_number_t    scpi_number;
    scpi_special_number_t scpi_special;
    float value;
    ranges_e range = ranges_e::ranges_e_Power;

    // Parse command to number type
    if (!SCPI_ParamNumber(context, number_specials, &scpi_number, TRUE)) {
        return SCPI_RES_ERR;
    }
    // translate number type to real value depending on range definition
    if (!get_value_from_param(context, scpi_number, range, value)) {
        return SCPI_RES_ERR;
    };
    if (!state.setPset(value)) {
        SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
        return SCPI_RES_ERR;
    };
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_powQ(scpi_t *context)
{
    setStateStruct localSetState;
    state.getSetStateCopy(&localSetState, 1000);
    
    SCPI_ResultFloat(context, localSetState.Pset);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_pow_prot_level(scpi_t *context)
{
    scpi_parameter_t param;
    scpi_number_t    scpi_number;
    scpi_special_number_t scpi_special;
    float value;
    ranges_e range = ranges_e::ranges_e_OPP_Power;

    // Parse command to number type
    if (!SCPI_ParamNumber(context, number_specials, &scpi_number, TRUE)) {
        return SCPI_RES_ERR;
    }
    // translate number type to real value depending on range definition
    if (!get_value_from_param(context, scpi_number, range, value)) {
        return SCPI_RES_ERR;
    };
    if (!state.setOPPset(value)) {
        SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
        return SCPI_RES_ERR;
    };
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_pow_prot_levelQ(scpi_t *context)
{
    setStateStruct localSetState;
    state.getSetStateCopy(&localSetState, 1000);
    
    SCPI_ResultFloat(context, localSetState.OPPset);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_pow_prot_delay(scpi_t *context)
{
    scpi_parameter_t param;
    scpi_number_t    scpi_number;
    scpi_special_number_t scpi_special;
    float value;
    ranges_e range = ranges_e::ranges_e_OPP_Delay;

    // Parse command to number type
    if (!SCPI_ParamNumber(context, number_specials, &scpi_number, TRUE)) {
        return SCPI_RES_ERR;
    }
    // translate number type to real value depending on range definition
    if (!get_value_from_param(context, scpi_number, range, value)) {
        return SCPI_RES_ERR;
    };
    if (!state.setOPPdelay(value)) {
        SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
        return SCPI_RES_ERR;
    };
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_source_pow_prot_delayQ(scpi_t *context)
{
    setStateStruct localSetState;
    state.getSetStateCopy(&localSetState, 1000);
    
    SCPI_ResultFloat(context, localSetState.OPPdelay);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_syst_beep(scpi_t *context)
{
    scpi_parameter_t param;
    scpi_number_t    scpi_number;
    scpi_special_number_t scpi_special;
    float value=0;
    ranges_e range = ranges_e::ranges_e_beepDuration;

    
    // Parse command to number type
    if (!SCPI_ParamNumber(context, number_specials, &scpi_number, FALSE)) {
        // No parameter given or not a number.
        value = state.getBeepDefaultDuration();
        // TODO: Give error if parameter is not a number.
    } else {
        // translate number type to real value depending on range definition
        if (!get_value_from_param(context, scpi_number, range, value)) {
            return SCPI_RES_ERR;
        };
    } 
    if (!beep(value)) {
        SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
        return SCPI_RES_ERR;
    };
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_syst_beep_dur(scpi_t *context)
{
    scpi_parameter_t param;
    scpi_number_t    scpi_number;
    scpi_special_number_t scpi_special;
    float value;
    ranges_e range = ranges_e::ranges_e_beepDuration;

    // Parse command to number type
    if (!SCPI_ParamNumber(context, number_specials, &scpi_number, TRUE)) {
        return SCPI_RES_ERR;
    }
    // translate number type to real value depending on range definition
    if (!get_value_from_param(context, scpi_number, range, value)) {
        return SCPI_RES_ERR;
    };
    state.setBeepDefaultDuration(value);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_syst_beep_durQ(scpi_t *context)
{
    SCPI_ResultFloat(context, state.getBeepDefaultDuration());
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_syst_beep_on_prot(scpi_t *context) {
    scpi_bool_t param1;
    if (!SCPI_ParamBool(context, &param1, TRUE)) {
         return SCPI_RES_ERR;
    }
    state.setBeepProt(param1);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_syst_beep_on_protQ(scpi_t *context) {
    SCPI_ResultBool(context, state.getBeepProt());
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_syst_beep_on_cap(scpi_t *context) {
    scpi_bool_t param1;
    if (!SCPI_ParamBool(context, &param1, TRUE)) {
         return SCPI_RES_ERR;
    }
    state.setBeepCap(param1);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_syst_beep_on_capQ(scpi_t *context) {
    SCPI_ResultBool(context, state.getBeepCap());
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_syst_beep_on_pol(scpi_t *context) {
    scpi_bool_t param1;
    if (!SCPI_ParamBool(context, &param1, TRUE)) {
         return SCPI_RES_ERR;
    }
    state.setBeepReverse(param1);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_syst_beep_on_polQ(scpi_t *context) {
    SCPI_ResultBool(context, state.getBeepReverse());
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_syst_beep_on_sense(scpi_t *context) {
    scpi_bool_t param1;
    if (!SCPI_ParamBool(context, &param1, TRUE)) {
         return SCPI_RES_ERR;
    }
    state.setBeepSense(param1);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_syst_beep_on_senseQ(scpi_t *context) {
    SCPI_ResultBool(context, state.getBeepSense());
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_syst_beep_on_enc(scpi_t *context) {
    scpi_bool_t param1;
    if (!SCPI_ParamBool(context, &param1, TRUE)) {
         return SCPI_RES_ERR;
    }
    state.setBeepEncoder(param1);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_syst_beep_on_encQ(scpi_t *context) {
    SCPI_ResultBool(context, state.getBeepEncoder());
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_syst_fan_mode(scpi_t *context) {
    int32_t param;
    if (!SCPI_ParamChoice(context, fan_mode_list, &param, TRUE)) {
        return SCPI_RES_ERR;
    }
    if (!state.setFanAuto((bool)param)) {
        SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
        return SCPI_RES_ERR;
    };
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_syst_fan_modeQ(scpi_t *context) {
    setStateStruct localSetState;
    state.getSetStateCopy(&localSetState, 1000);
    
    if (localSetState.FanAuto) {
        SCPI_ResultText(context, "AUTO");
    } else {
        SCPI_ResultText(context, "MANUAL");
    }
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_syst_fan_speed(scpi_t *context) {
    scpi_parameter_t param;
    scpi_number_t    scpi_number;
    scpi_special_number_t scpi_special;
    float value;
    ranges_e range;

    // Parse command to number type
    if (!SCPI_ParamNumber(context, number_specials, &scpi_number, TRUE)) {
        return SCPI_RES_ERR;
    }

    // translate number type to real value depending on range definition
    if (!get_value_from_param(context, scpi_number, ranges_e_FanSpeed, value)) {
        return SCPI_RES_ERR;
    };

    set_var_fan_set_speed((int32_t)value);
    return SCPI_RES_OK;

};
scpi_result_t scpi_cmd_syst_fan_speedQ(scpi_t *context) {
    setStateStruct localSetState;
    state.getSetStateCopy(&localSetState, 1000);

    SCPI_ResultInt32(context, (int32_t)max(localSetState.FanManualSpeed/(2.55 - 0.50)-50,0));
    return SCPI_RES_OK; 
};

scpi_result_t scpi_cmd_syst_fan_rpmQ(scpi_t *context) {
    measuredStateStruct localMeasureState;
    state.getMeasuredStateCopy(&localMeasureState, 1000);
    
    SCPI_ResultFloat(context, localMeasureState.FanRPM);
    return SCPI_RES_OK;
};
scpi_result_t scpi_cmd_syst_tempQ(scpi_t *context) {
    measuredStateStruct localMeasureState;
    state.getMeasuredStateCopy(&localMeasureState, 1000);
    
    SCPI_ResultFloat(context, localMeasureState.Temp1);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_syst_temp_prot(scpi_t *context) {
    scpi_parameter_t param;
    scpi_number_t    scpi_number;
    scpi_special_number_t scpi_special;
    float value;
    ranges_e range = ranges_e::ranges_e_OTP_Temp;

    // Parse command to number type
    if (!SCPI_ParamNumber(context, number_specials, &scpi_number, TRUE)) {
        return SCPI_RES_ERR;
    }
    // translate number type to real value depending on range definition
    if (!get_value_from_param(context, scpi_number, range, value)) {
        return SCPI_RES_ERR;
    };
    if (!state.setOTPset(value)) {
        SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
        return SCPI_RES_ERR;
    };
    return SCPI_RES_OK;
};
scpi_result_t scpi_cmd_syst_temp_protQ(scpi_t *context) {
    setStateStruct localSetState;
    state.getSetStateCopy(&localSetState, 1000);
    
    SCPI_ResultFloat(context, localSetState.OTPset);
    return SCPI_RES_OK;
};
scpi_result_t scpi_cmd_syst_temp_prot_del(scpi_t *context) {
    scpi_parameter_t param;
    scpi_number_t    scpi_number;
    scpi_special_number_t scpi_special;
    float value;
    ranges_e range = ranges_e::ranges_e_OTP_Delay;

    // Parse command to number type
    if (!SCPI_ParamNumber(context, number_specials, &scpi_number, TRUE)) {
        return SCPI_RES_ERR;
    }
    // translate number type to real value depending on range definition
    if (!get_value_from_param(context, scpi_number, range, value)) {
        return SCPI_RES_ERR;
    };
    if (!state.setOTPdelay(value)) {
        SCPI_ErrorPush(context, SCPI_ERROR_DEVICE_ERROR);
        return SCPI_RES_ERR;
    };
    return SCPI_RES_OK;
};
scpi_result_t scpi_cmd_syst_temp_prot_delQ(scpi_t *context) {
    setStateStruct localSetState;
    state.getSetStateCopy(&localSetState, 1000);
    
    SCPI_ResultFloat(context, localSetState.OTPdelay);
    return SCPI_RES_OK;
};

} //namespace dcl::scpi
