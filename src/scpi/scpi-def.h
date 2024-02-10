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
#define SCPI_IDN4 "01-02"

using namespace dcl;

namespace dcl::scpi {

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

// EL-Load
extern scpi_result_t scpi_cmd_fetch_current(scpi_t *context);
extern scpi_result_t scpi_cmd_fetch_voltage(scpi_t *context);
extern scpi_result_t scpi_cmd_fetch_power(scpi_t *context);

extern scpi_result_t scpi_cmd_sense_nplc(scpi_t *context);
extern scpi_result_t scpi_cmd_sense_nplcQ(scpi_t *context);
extern scpi_result_t scpi_cmd_sense_plfreq(scpi_t *context);
extern scpi_result_t scpi_cmd_sense_plfreqQ(scpi_t *context);

extern scpi_result_t scpi_cmd_sense_volt_remote(scpi_t *context);
extern scpi_result_t scpi_cmd_sense_volt_remoteQ(scpi_t *context);

extern scpi_result_t scpi_cmd_source_input_state(scpi_t *context);
extern scpi_result_t scpi_cmd_source_input_stateQ(scpi_t *context);

extern scpi_result_t scpi_cmd_source_mode(scpi_t *context);
extern scpi_result_t scpi_cmd_source_modeQ(scpi_t *context);

extern scpi_result_t scpi_cmd_source_input_prot_clear(scpi_t *context);
extern scpi_result_t scpi_cmd_source_input_prot_tripQ(scpi_t *context);

extern scpi_result_t scpi_cmd_source_current(scpi_t *context);
extern scpi_result_t scpi_cmd_source_currentQ(scpi_t *context);
extern scpi_result_t scpi_cmd_source_current_prot_level(scpi_t *context);
extern scpi_result_t scpi_cmd_source_current_prot_levelQ(scpi_t *context);
extern scpi_result_t scpi_cmd_source_current_range(scpi_t *context);
extern scpi_result_t scpi_cmd_source_current_rangeQ(scpi_t *context);

extern scpi_result_t scpi_cmd_source_voltage(scpi_t *context);
extern scpi_result_t scpi_cmd_source_voltageQ(scpi_t *context);
extern scpi_result_t scpi_cmd_source_voltage_prot_level(scpi_t *context);
extern scpi_result_t scpi_cmd_source_voltage_prot_levelQ(scpi_t *context);
extern scpi_result_t scpi_cmd_source_voltage_range(scpi_t *context);
extern scpi_result_t scpi_cmd_source_voltage_rangeQ(scpi_t *context);
}


