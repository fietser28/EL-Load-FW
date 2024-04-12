// SPDX-FileCopyrightText: 2024 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scpi/scpi.h"

#include "main.h"
#include "../ui/vars.h"     // TODO: Remove this dependancy  
#include "../ui/actions.h"  // TODO: Remove this dependancy
#include "scpi-def.h"

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


char scpi_input_buffer[SCPI_INPUT_BUFFER_LENGTH];
scpi_error_t scpi_error_queue_data[SCPI_ERROR_QUEUE_SIZE];

scpi_t scpi_context;

size_t SCPI_Write(scpi_t * context, const char * data, size_t len) {
    SERIALDEBUG.write(data, len);
    return len;
};

int SCPI_Error(scpi_t * context, int_fast16_t err) {   
    if (err == 0) {
        SERIALDEBUG.printf("%d, \"%s\"\n", err, SCPI_ErrorTranslate(err));
    } else {
        SERIALDEBUG.printf("**ERROR: %d, \"%s\"\n", err, SCPI_ErrorTranslate(err));
    }
    return 0;
};

scpi_result_t SCPI_Control(scpi_t * context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val) {
    if (SCPI_CTRL_SRQ == ctrl) {
        SERIALDEBUG.printf("**SRQ: 0x%X (%d)\n", val, val); 
    } else {
        SERIALDEBUG.printf("**CTRL %02x: 0x%X (%d)\n", ctrl, val, val);
    }
    return SCPI_RES_OK;
};

scpi_result_t SCPI_Reset(scpi_t * context) {
    state.setDefaults();
    SERIALDEBUG.printf("**Reset\n");
    return SCPI_RES_OK;
};

scpi_result_t SCPI_Flush(scpi_t * context) {
    SERIALDEBUG.flush();
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

scpi_result_t scpi_cmd_cal_type(scpi_t *context) {
    int32_t param;

    if (!SCPI_ParamChoice(context, cal_type_list, &param, TRUE)) {
         return SCPI_RES_ERR;
    }

    if (!state.getCalibrationMode()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
        return SCPI_RES_ERR;
    }

    set_var_cal_cal_type((calType_e)param);
    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_cal_typeQ(scpi_t *context)
{
    if (!state.getCalibrationMode()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
        return SCPI_RES_ERR;
    }

    SCPI_ResultUInt32(context, get_var_cal_cal_type());
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

            if (value >= 0 && value <= get_var_cal_numpoints()) { //TODO: replace numpoints with proper function from cal.c
                set_var_cal_curpoint(value);
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

    SCPI_ResultUInt32(context, get_var_cal_curpoint() + 1);
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_cal_point_maxQ(scpi_t *context) {
    if (!state.getCalibrationMode()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
        return SCPI_RES_ERR;
    }
    SCPI_ResultInt32(context, get_var_cal_numpoints());    
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

            
            if (value >= ranges[caldefaults[cal_calType].keyBoard].minValue && 
                value <= ranges[caldefaults[cal_calType].keyBoard].maxValue ) { 
                set_var_cal_set(value);
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
    SCPI_ResultFloat(context, get_var_cal_set());    
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_cal_measQ(scpi_t *context) {
    if (!state.getCalibrationMode()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
        return SCPI_RES_ERR;
    }
    SCPI_ResultFloat(context, get_var_cal_measured());    
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
        SCPI_ResultInt32(context, caldefaults[cal_calType].adcMin);
    } else {
        SCPI_ResultInt32(context, caldefaults[cal_calType].adcMax);     
    }
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_cal_meas(scpi_t *context) {
    if (!state.getCalibrationMode()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
        return SCPI_RES_ERR;
    }
    if (get_var_cal_trigger_measure()) {
        return SCPI_RES_ERR;
    }

    // TODO replace with more advanced flow action call
    //scpi_busy_inc(); //Done in flow for now

    if (caldefaults[cal_calType].type == calCalType_e_DAC) {
        action_cal_set_dac((lv_event_t *)NULL);
        vTaskDelay(1000);
    }

    set_var_cal_trigger_measure(true);

    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_cal_type_save(scpi_t *context) {
    if (!state.getCalibrationMode()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
        return SCPI_RES_ERR;
    }
    if (!cal_valuesChanged) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
        return SCPI_RES_ERR;
    }
    action_cal_store_values(NULL);
    set_var_cal_values_changed(false);
    return SCPI_RES_OK;
}

scpi_result_t scpi_cmd_cal_type_reset(scpi_t *context) {
    if (!state.getCalibrationMode()) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
        return SCPI_RES_ERR;
    }
    if (!cal_valuesChanged) {
        SCPI_ErrorPush(context, SCPI_ERROR_CALIBRATION_FAILED);
        return SCPI_RES_ERR;
    }
    action_cal_reset_values(NULL);
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

scpi_result_t scpi_cmd_fetch_voltage(scpi_t *context) {
    char buffer[64] = { 0 };
    measuredStateStruct localMeasuredState; 
    state.getMeasuredStateCopy(&localMeasuredState, 1000);

    SCPI_FloatToStr(localMeasuredState.Umon,buffer,sizeof(buffer));
    SCPI_ResultCharacters(context, buffer, strlen(buffer));
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_fetch_power(scpi_t *context) {
    char buffer[64] = { 0 };
    measuredStateStruct localMeasuredState; 
    state.getMeasuredStateCopy(&localMeasuredState, 1000);

    SCPI_FloatToStr(localMeasuredState.Imon * localMeasuredState.Umon,buffer,sizeof(buffer));
    SCPI_ResultCharacters(context, buffer, strlen(buffer));
    return SCPI_RES_OK;
};

scpi_result_t scpi_cmd_fetch_cap(scpi_t *context) {
    measuredStateStruct localMeasuredState; 
    state.getMeasuredStateCopy(&localMeasuredState, 1000);
    const float cap_array[] = { (float)localMeasuredState.As / 3600.0f, (float)localMeasuredState.Ws / 3600.0f, (float)localMeasuredState.Ptime};
    SCPI_ResultArrayFloat(context, cap_array, 3, SCPI_FORMAT_ASCII );
    return SCPI_RES_OK;
};

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

    bool res = localSetState.protection || localMeasureState.OCPstate || localMeasureState.OVPstate || localMeasureState.OPPstate || localMeasureState.OTPstate;
    SCPI_ResultBool(context, res);
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
