// SPDX-FileCopyrightText: 2024 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once 

#include "scpi/scpi.h"
#include "main.h"

#define SCPI_INPUT_BUFFER_LENGTH 256
#define SCPI_ERROR_QUEUE_SIZE 32
#define SCPI_IDN1 "jan28"
#define SCPI_IDN2 "DCL8010"
#define SCPI_IDN3 NULL
#define SCPI_VERSION "1999.0"

using namespace dcl;

namespace dcl::scpi {

extern int32_t scpi_busy; // For OPC functionallity
extern int32_t scpi_busy_inc();
extern int32_t scpi_busy_dec();

// SCPI data structures
extern const scpi_command_t scpi_commands[];
extern scpi_interface_t scpi_interface;
extern char scpi_input_buffer[];
extern scpi_error_t scpi_error_queue_data[];
extern scpi_t scpi_context;

// SCPI helper commands
size_t SCPI_Write(scpi_t * context, const char * data, size_t len);
int SCPI_Error(scpi_t * context, int_fast16_t err);
scpi_result_t SCPI_Control(scpi_t * context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val);
scpi_result_t SCPI_Reset(scpi_t * context);
scpi_result_t SCPI_Flush(scpi_t * context);

//scpi_result_t SCPI_SystemCommTcpipControlQ(scpi_t * context);

extern scpi_result_t scpi_opc(scpi_t *context);
extern scpi_result_t scpi_opcQ(scpi_t *context);
extern scpi_result_t scpi_rst(scpi_t *context);

// EL-Load
extern scpi_result_t scpi_cmd_cal(scpi_t *context);
extern scpi_result_t scpi_cmd_calQ(scpi_t *context);
extern scpi_result_t scpi_cmd_cal_init_eeprom(scpi_t *context);
extern scpi_result_t scpi_cmd_cal_init_eepromQ(scpi_t *context);
extern scpi_result_t scpi_cmd_cal_type(scpi_t *context);
extern scpi_result_t scpi_cmd_cal_typeQ(scpi_t *context);
extern scpi_result_t scpi_cmd_cal_point(scpi_t *context);
extern scpi_result_t scpi_cmd_cal_pointQ(scpi_t *context);
extern scpi_result_t scpi_cmd_cal_point_maxQ(scpi_t *context);
extern scpi_result_t scpi_cmd_cal_set(scpi_t *context);
extern scpi_result_t scpi_cmd_cal_setQ(scpi_t *context);
extern scpi_result_t scpi_cmd_cal_adcQ(scpi_t *context);
extern scpi_result_t scpi_cmd_cal_measQ(scpi_t *context);

extern scpi_result_t scpi_cmd_cal_meas(scpi_t *context);
extern scpi_result_t scpi_cmd_cal_meas_runQ(scpi_t *context); 
extern scpi_result_t scpi_cmd_cal_type_save(scpi_t *context);
extern scpi_result_t scpi_cmd_cal_type_reset(scpi_t *context);

extern scpi_result_t scpi_cmd_deb_eeprom_clear(scpi_t *context);
extern scpi_result_t scpi_cmd_deb_flow_queueQ(scpi_t *context);
extern scpi_result_t scpi_cmd_deb_mem_heapQ(scpi_t *context);
extern scpi_result_t scpi_cmd_deb_mem_lvmonQ(scpi_t *context);
extern scpi_result_t scpi_cmd_deb_mem_queues_minQ(scpi_t *context);
extern scpi_result_t scpi_cmd_deb_mem_queues_overflowsQ(scpi_t *context);
extern scpi_result_t scpi_cmd_deb_reboot(scpi_t *context);
extern scpi_result_t scpi_cmd_deb_iolinesQ(scpi_t *context);
extern scpi_result_t scpi_cmd_deb_state_countQ(scpi_t *context);
extern scpi_result_t scpi_cmd_deb_tasks_prioQ(scpi_t *context);
extern scpi_result_t scpi_cmd_deb_tasks_runtimeQ(scpi_t *context);
extern scpi_result_t scpi_cmd_deb_tasks_stackhwQ(scpi_t *context);
extern scpi_result_t scpi_cmd_deb_wdog_thres_maxQ(scpi_t *context);

extern scpi_result_t scpi_cmd_fetch_current(scpi_t *context);
extern scpi_result_t scpi_cmd_fetch_curr_statQ(scpi_t *context);
extern scpi_result_t scpi_cmd_fetch_voltage(scpi_t *context);
extern scpi_result_t scpi_cmd_fetch_volt_statQ(scpi_t *context);
extern scpi_result_t scpi_cmd_fetch_volt_revQ(scpi_t *context);
extern scpi_result_t scpi_cmd_fetch_power(scpi_t *context);
extern scpi_result_t scpi_cmd_fetch_pow_statQ(scpi_t *context);
extern scpi_result_t scpi_cmd_fetch_cap(scpi_t *context);

extern scpi_result_t scpi_cmd_meas_currQ(scpi_t *context);
extern scpi_result_t scpi_cmd_meas_voltQ(scpi_t *context);
extern scpi_result_t scpi_cmd_meas_powQ(scpi_t *context);

extern scpi_result_t scpi_cmd_sense_curr_stat(scpi_t *context);
extern scpi_result_t scpi_cmd_sense_curr_statQ(scpi_t *context);
extern scpi_result_t scpi_cmd_sense_curr_stat_clear(scpi_t *context);
extern scpi_result_t scpi_cmd_sense_nplc(scpi_t *context);
extern scpi_result_t scpi_cmd_sense_nplcQ(scpi_t *context);
extern scpi_result_t scpi_cmd_sense_plfreq(scpi_t *context);
extern scpi_result_t scpi_cmd_sense_plfreqQ(scpi_t *context);
extern scpi_result_t scpi_cmd_sense_pow_stat(scpi_t *context);
extern scpi_result_t scpi_cmd_sense_pow_statQ(scpi_t *context);
extern scpi_result_t scpi_cmd_sense_pow_stat_clear(scpi_t *context);
extern scpi_result_t scpi_cmd_sense_volt_stat(scpi_t *context);
extern scpi_result_t scpi_cmd_sense_volt_statQ(scpi_t *context);
extern scpi_result_t scpi_cmd_sense_volt_stat_clear(scpi_t *context);

extern scpi_result_t scpi_cmd_sense_volt_remote(scpi_t *context);
extern scpi_result_t scpi_cmd_sense_volt_remoteQ(scpi_t *context);
extern scpi_result_t scpi_cmd_sense_volt_remote_errorQ(scpi_t *context);

extern scpi_result_t scpi_cmd_source_input_state(scpi_t *context);
extern scpi_result_t scpi_cmd_source_input_stateQ(scpi_t *context);

extern scpi_result_t scpi_cmd_source_mode(scpi_t *context);
extern scpi_result_t scpi_cmd_source_modeQ(scpi_t *context);

extern scpi_result_t scpi_cmd_source_input_prot_clear(scpi_t *context);
extern scpi_result_t scpi_cmd_source_input_prot_tripQ(scpi_t *context);
extern scpi_result_t scpi_cmd_source_input_prot_trip_revQ(scpi_t *context);

extern scpi_result_t scpi_cmd_source_input_prot_wdog(scpi_t *context);
extern scpi_result_t scpi_cmd_source_input_prot_wdogQ(scpi_t *context);
extern scpi_result_t scpi_cmd_source_input_prot_wdog_clear(scpi_t *context);
extern scpi_result_t scpi_cmd_source_input_prot_wdog_del(scpi_t *context);
extern scpi_result_t scpi_cmd_source_input_prot_wdog_delQ(scpi_t *context);
extern scpi_result_t scpi_cmd_source_input_prot_wdog_pet(scpi_t *context);
extern scpi_result_t scpi_cmd_source_input_prot_wdog_type(scpi_t *context);
extern scpi_result_t scpi_cmd_source_input_prot_wdog_typeQ(scpi_t *context);
extern scpi_result_t scpi_cmd_source_input_prot_wdog_tripQ(scpi_t *context);

extern scpi_result_t scpi_cmd_source_cap(scpi_t *context);
extern scpi_result_t scpi_cmd_source_capQ(scpi_t *context);
extern scpi_result_t scpi_cmd_source_cap_zero(scpi_t *context);
extern scpi_result_t scpi_cmd_source_cap_limit(scpi_t *context);
extern scpi_result_t scpi_cmd_source_cap_limitQ(scpi_t *context);
extern scpi_result_t scpi_cmd_source_cap_limit_clear(scpi_t *context);
extern scpi_result_t scpi_cmd_source_cap_limit_tripQ(scpi_t *context);
extern scpi_result_t scpi_cmd_source_cap_ahstop(scpi_t *context);
extern scpi_result_t scpi_cmd_source_cap_ahstopQ(scpi_t *context);
extern scpi_result_t scpi_cmd_source_cap_whstop(scpi_t *context);
extern scpi_result_t scpi_cmd_source_cap_whstopQ(scpi_t *context);
extern scpi_result_t scpi_cmd_source_cap_timestop(scpi_t *context);
extern scpi_result_t scpi_cmd_source_cap_timestopQ(scpi_t *context);
extern scpi_result_t scpi_cmd_source_cap_voltstop(scpi_t *context);
extern scpi_result_t scpi_cmd_source_cap_voltstopQ(scpi_t *context);

extern scpi_result_t scpi_cmd_source_current(scpi_t *context);
extern scpi_result_t scpi_cmd_source_currentQ(scpi_t *context);
extern scpi_result_t scpi_cmd_source_current_prot_level(scpi_t *context);
extern scpi_result_t scpi_cmd_source_current_prot_levelQ(scpi_t *context);
extern scpi_result_t scpi_cmd_source_current_range(scpi_t *context);
extern scpi_result_t scpi_cmd_source_current_rangeQ(scpi_t *context);

extern scpi_result_t scpi_cmd_source_voltage(scpi_t *context);
extern scpi_result_t scpi_cmd_source_voltageQ(scpi_t *context);

extern scpi_result_t scpi_cmd_source_voltage_on(scpi_t *context);
extern scpi_result_t scpi_cmd_source_voltage_onQ(scpi_t *context);
extern scpi_result_t scpi_cmd_source_voltage_on_latch(scpi_t *context);
extern scpi_result_t scpi_cmd_source_voltage_on_latchQ(scpi_t *context);

extern scpi_result_t scpi_cmd_source_voltage_prot_level(scpi_t *context);
extern scpi_result_t scpi_cmd_source_voltage_prot_levelQ(scpi_t *context);
extern scpi_result_t scpi_cmd_source_voltage_range(scpi_t *context);
extern scpi_result_t scpi_cmd_source_voltage_rangeQ(scpi_t *context);

extern scpi_result_t scpi_cmd_source_res(scpi_t *context);
extern scpi_result_t scpi_cmd_source_resQ(scpi_t *context);

extern scpi_result_t scpi_cmd_source_pow(scpi_t *context);
extern scpi_result_t scpi_cmd_source_powQ(scpi_t *context);
extern scpi_result_t scpi_cmd_source_pow_prot_level(scpi_t *context);
extern scpi_result_t scpi_cmd_source_pow_prot_levelQ(scpi_t *context);
extern scpi_result_t scpi_cmd_source_pow_prot_delay(scpi_t *context);
extern scpi_result_t scpi_cmd_source_pow_prot_delayQ(scpi_t *context);

extern scpi_result_t scpi_cmd_syst_beep(scpi_t *context);
extern scpi_result_t scpi_cmd_syst_beep_dur(scpi_t *context);
extern scpi_result_t scpi_cmd_syst_beep_durQ(scpi_t *context);
extern scpi_result_t scpi_cmd_syst_beep_on_prot(scpi_t *context);
extern scpi_result_t scpi_cmd_syst_beep_on_protQ(scpi_t *context);
extern scpi_result_t scpi_cmd_syst_beep_on_cap(scpi_t *context);
extern scpi_result_t scpi_cmd_syst_beep_on_capQ(scpi_t *context);
extern scpi_result_t scpi_cmd_syst_beep_on_pol(scpi_t *context);
extern scpi_result_t scpi_cmd_syst_beep_on_polQ(scpi_t *context);
extern scpi_result_t scpi_cmd_syst_beep_on_sense(scpi_t *context);
extern scpi_result_t scpi_cmd_syst_beep_on_senseQ(scpi_t *context);
extern scpi_result_t scpi_cmd_syst_beep_on_enc(scpi_t *context);
extern scpi_result_t scpi_cmd_syst_beep_on_encQ(scpi_t *context);

extern scpi_result_t scpi_cmd_syst_eventQ(scpi_t *context);
extern scpi_result_t scpi_cmd_syst_event_countQ(scpi_t *context);
extern scpi_result_t scpi_cmd_syst_event_first(scpi_t *context);

extern scpi_result_t scpi_cmd_syst_fan_mode(scpi_t *context);
extern scpi_result_t scpi_cmd_syst_fan_modeQ(scpi_t *context);
extern scpi_result_t scpi_cmd_syst_fan_speed(scpi_t *context);
extern scpi_result_t scpi_cmd_syst_fan_speedQ(scpi_t *context);
extern scpi_result_t scpi_cmd_syst_fan_rpmQ(scpi_t *context);
extern scpi_result_t scpi_cmd_syst_tempQ(scpi_t *context);
extern scpi_result_t scpi_cmd_syst_temp_prot(scpi_t *context);
extern scpi_result_t scpi_cmd_syst_temp_protQ(scpi_t *context);
extern scpi_result_t scpi_cmd_syst_temp_prot_del(scpi_t *context);
extern scpi_result_t scpi_cmd_syst_temp_prot_delQ(scpi_t *context);
}


