// SPDX-FileCopyrightText: 2024 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "scpi/scpi.h"

#include "main.h"
#include "scpi-def.h"

using namespace dcl;

namespace dcl::scpi {

const scpi_command_t scpi_commands[] = {
    /* IEEE Mandatory Commands (SCPI std V1999.0 4.1.1) */
    /* ================================================*/
    // TODO: Not all these are properly done yet.
    {"*CLS", SCPI_CoreCls, 0},
    {"*ESE", SCPI_CoreEse, 0},
    {"*ESE?", SCPI_CoreEseQ, 0},
    {"*ESR?", SCPI_CoreEsrQ, 0},
    {"*IDN?", SCPI_CoreIdnQ, 0},
    {"*OPC", scpi_opc, 0},
    {"*OPC?", scpi_opcQ, 0},
    {"*RST", SCPI_CoreRst, 0},  // OK? should be equal to StatusPreset?
    {"*SRE", SCPI_CoreSre, 0},
    {"*SRE?", SCPI_CoreSreQ, 0},
    {"*STB?", SCPI_CoreStbQ, 0},
 //   {"*TST?", My_CoreTstQ, 0},
    {"*WAI", SCPI_CoreWai, 0},

    /* Required SCPI commands (SCPI std V1999.0 4.2.1) */
    {"SYSTem:ERRor[:NEXT]?", SCPI_SystemErrorNextQ, 0},
    {"SYSTem:ERRor:COUNt?", SCPI_SystemErrorCountQ, 0},
    {"SYSTem:VERSion?", SCPI_SystemVersionQ, 0},

    //{"STATus:OPERation?", scpi_stub_callback, 0},
    //{"STATus:OPERation:EVENt?", scpi_stub_callback, 0},
    //{"STATus:OPERation:CONDition?", scpi_stub_callback, 0},
    //{"STATus:OPERation:ENABle", scpi_stub_callback, 0},
    //{"STATus:OPERation:ENABle?", scpi_stub_callback, 0},

    {"STATus:QUEStionable[:EVENt]?", SCPI_StatusQuestionableEventQ, 0},
    //{"STATus:QUEStionable:CONDition?", scpi_stub_callback, 0},
    {"STATus:QUEStionable:ENABle", SCPI_StatusQuestionableEnable, 0},
    {"STATus:QUEStionable:ENABle?", SCPI_StatusQuestionableEnableQ, 0},

    {"STATus:PRESet", SCPI_StatusPreset, 0}, //TODO: Reset to defaults?

    // === End of mandatory SCPI sections

    /* Calibration */
    // Enter/exit/query calibration mode
    {"CALibration[:MODE]", scpi_cmd_cal, 0},        // ON/OFF/1/0
    {"CALibration[:MODE]?", scpi_cmd_calQ, 0},

    {"CALibration:INIT:EEPROM", scpi_cmd_cal_init_eeprom, 0},
    {"CALibration:INIT[:EEPROM]?", scpi_cmd_cal_init_eepromQ, 0},

    // Select what value to calibrate
    {"CALibration:TYPe", scpi_cmd_cal_type, 0},     // IMONHigh|IMONLow|UMONHigh|... see cal_type_list in scpi-def.cpp
    {"CALibration:TYPe?", scpi_cmd_cal_typeQ, 0},

    // Select calibration point
    {"CALibration:POInt", scpi_cmd_cal_point, 0},   // Number
    {"CALibration:POInt?", scpi_cmd_cal_pointQ, 0},
    {"CALibration:POInt:MAX?", scpi_cmd_cal_point_maxQ, 0},

    // Setpoint for this calibration point
    {"CALibration:SET", scpi_cmd_cal_set, 0},       // Float
    {"CALibration:SET?", scpi_cmd_cal_setQ, 0},

    // Query adc value for this calibration point
    {"CALibration:ADC?", scpi_cmd_cal_adcQ, 0},

    // Perform calibration measurement
    {"CALibration:MEASure", scpi_cmd_cal_meas, 0},
    // Get calibration measured result
    {"CALibration:MEASure?", scpi_cmd_cal_measQ, 0},
    // Calibration routine running?
    {"CALibration:MEASure:RUNning?", scpi_cmd_cal_meas_runQ, 0},

    // Save this calibration TYPE to EEPROM, not just a single point.
    {"CALibration[:TYPe]:SAVE", scpi_cmd_cal_type_save, 0},

    // Reset calibration points to running values when entered calibration
    {"CALibration[:TYPe]:RESET", scpi_cmd_cal_type_reset, 0},

    // Debug commands
    /*
    {"DEBug:FLOW:QUEue:SIZe?"}
    {"DEBug:FLOW:QUEue:HIGHest?"}
    {"DEBug:FLOW:QUEue[:CURRent]?"}
    {"DEBug:LVGL:MEMory:TOTal?"}
    {"DEBug:LVGL:MEMory:FREE?"}
    {"DEBug:LVGL:MEMory:FREE:BIGgest?"}
    */
    {"DEBug:EEPROM:CLEAR", scpi_cmd_deb_eeprom_clear, 0},
    {"DEBug:MEM:HEAP?", scpi_cmd_deb_mem_heapQ, 0},
    {"DEBug:REBOOT", scpi_cmd_deb_reboot, 0},
    {"DEBug:WDOG:THRESholds:MAX?", scpi_cmd_deb_wdog_thres_maxQ, 0},

    /* Fetch. This reads the last measured value, doesn't trigger and wait like measure */
    {"FETCh[:SCALar]:CURRent[:DC]?", scpi_cmd_fetch_current, 0},
    {"FETCh[:SCALar]:CURRent[:DC]:STATistics?", scpi_cmd_fetch_curr_statQ, 0}, // <empty>|MIN|MAX|AVG|COUNT
    {"FETCh[:SCALar]:VOLTage[:DC]?", scpi_cmd_fetch_voltage, 0},
    {"FETCh[:SCALar]:VOLTage[:DC]:STATistics?", scpi_cmd_fetch_volt_statQ, 0}, // <empty>|MIN|MAX|AVG|COUNT
    {"FETCh[:SCALar]:POWer[:DC]?", scpi_cmd_fetch_power, 0},
    {"FETCh[:SCALar]:POWer[:DC]:STATistics?", scpi_cmd_fetch_pow_statQ, 0},    // <empty>|MIN|MAX|AVG|COUNT
    {"FETCh:CAPacity?", scpi_cmd_fetch_cap, 0},

    // Current measurement stats
    {"[SENSe]:CURRent:STATistics[:ON]", scpi_cmd_sense_curr_stat,0}, // ON|OFF|1|0
    {"[SENSe]:CURRent:STATistics[:ON]?", scpi_cmd_sense_curr_statQ,0},
    {"[SENSe]:CURRent:STATistics:CLEar", scpi_cmd_sense_curr_stat_clear,0},

    
    // Averaging functions for measurements
    {"[SENSe]:NPLCycles", scpi_cmd_sense_nplc, 0},  // integer: 1-100
    {"[SENSe]:NPLCycles?", scpi_cmd_sense_nplcQ, 0},
    {"[SENSe]:PLFreq", scpi_cmd_sense_plfreq, 0},   // 50|60
    {"[SENSe]:PLFreq?", scpi_cmd_sense_plfreqQ, 0},
    
    // Power measurement stats
    {"[SENSe]:POWer:STATistics[:ON]", scpi_cmd_sense_pow_stat,0}, // ON|OFF|1|0
    {"[SENSe]:POWer:STATistics[:ON]?", scpi_cmd_sense_pow_statQ,0},
    {"[SENSe]:POWer:STATistics:CLEar", scpi_cmd_sense_pow_stat_clear,0},

    // Remote voltage sensing
    {"[SENSe]:VOLTage:REMote", scpi_cmd_sense_volt_remote, 0},   // ON|OFF|1|0
    {"[SENSe]:VOLTage:REMote?", scpi_cmd_sense_volt_remoteQ, 0},
    {"[SENSe]:VOLTage:REMote:ERRor[:TRIPped]?", scpi_cmd_sense_volt_remote_errorQ, 0}, // Sense error tripped?

    // Voltage measurement stats
    {"[SENSe]:VOLTage:STATistics[:ON]", scpi_cmd_sense_volt_stat,0}, // ON|OFF|1|0
    {"[SENSe]:VOLTage:STATistics[:ON]?", scpi_cmd_sense_volt_statQ,0},
    {"[SENSe]:VOLTage:STATistics:CLEar", scpi_cmd_sense_volt_stat_clear,0},
    
    // ON/OFF state
    {"[SOURce]:INPut[:STATe]", scpi_cmd_source_input_state, 0},  // ON|OFF|1|0
    {"[Source]:INPut[:STATe]?", scpi_cmd_source_input_stateQ, 0},

    // Main mode
    {"[SOURce]:INPut:MODE", scpi_cmd_source_mode, 0},   // CC|CV|CR|CP
    {"[SOURce]:INPut:MODE?", scpi_cmd_source_modeQ, 0},
    
    // Global protection
    {"[SOURce]:INPut:PROTection:CLEar", scpi_cmd_source_input_prot_clear, 0},  // no arguments
    {"[SOURce]:INPut:PROTection:TRIPped?", scpi_cmd_source_input_prot_tripQ, 0},

    // SCPI watchdog protection. Enter protection state if SCPI communication stops.
    {"[SOURce]:INPut:PROTection:WDOG", scpi_cmd_source_input_prot_wdog, 0},  // ON|OFF|1|0
    {"[SOURce]:INPut:PROTection:WDOG?", scpi_cmd_source_input_prot_wdogQ, 0},
    {"[SOURce]:INPut:PROTection:WDOG:CLEar", scpi_cmd_source_input_prot_wdog_clear, 0}, 
    {"[SOURce]:INPut:PROTection:WDOG:DELay", scpi_cmd_source_input_prot_wdog_del, 0},  // 1-3600
    {"[SOURce]:INPut:PROTection:WDOG:DELay?", scpi_cmd_source_input_prot_wdog_delQ, 0},
    {"[SOURce]:INPut:PROTection:WDOG:PET", scpi_cmd_source_input_prot_wdog_pet, 0},  
    {"[SOURce]:INPut:PROTection:WDOG:TYPe", scpi_cmd_source_input_prot_wdog_type, 0},  // ACTivity|PET (ACT=default)
    {"[SOURce]:INPut:PROTection:WDOG:TYPe?", scpi_cmd_source_input_prot_wdog_typeQ, 0},
    {"[SOURce]:INPut:PROTection:WDOG:TRIPped?", scpi_cmd_source_input_prot_wdog_tripQ, 0},
    
    // Capacity set.query commands
    {"[SOURce]:CAPacity[:STATe]", scpi_cmd_source_cap, 0},  // ON|OFF|1|0
    {"[SOURce]:CAPacity[:STATe]?", scpi_cmd_source_capQ, 0},

    // The limit setion disables the load if a limit is reached.
    {"[SOURce]:CAPacity:LIMit:CLEar", scpi_cmd_source_cap_limit_clear, 0},  // ON|OFF|1|0
    {"[SOURce]:CAPacity:LIMit:TRIPped?", scpi_cmd_source_cap_limit_tripQ, 0},
    {"[SOURce]:CAPacity:LIMit[:ENable]", scpi_cmd_source_cap_limit, 0}, // 1/0  Enable/disable capacity limits
    {"[SOURce]:CAPacity:LIMit[:ENable]?", scpi_cmd_source_cap_limitQ, 0},
    {"[SOURce]:CAPacity:LIMit:AH[:STOP]", scpi_cmd_source_cap_ahstop, 0},  // float,  Ah limit
    {"[SOURce]:CAPacity:LIMit:AH[:STOP]?", scpi_cmd_source_cap_ahstopQ, 0},
    {"[SOURce]:CAPacity:LIMit:TIMe[:STOP]", scpi_cmd_source_cap_timestop, 0}, // // float,  max. time limit in seconds
    {"[SOURce]:CAPacity:LIMit:TIMe[:STOP]?", scpi_cmd_source_cap_timestopQ, 0},
    {"[SOURce]:CAPacity:LIMit:VOLTage[:STOP]", scpi_cmd_source_cap_voltstop, 0},   // float, min. Volt limit 
    {"[SOURce]:CAPacity:LIMit:VOLTage[:STOP]?", scpi_cmd_source_cap_voltstopQ, 0},
    {"[SOURce]:CAPacity:LIMit:WH[:STOP]", scpi_cmd_source_cap_whstop, 0},  // float,  Wh limit
    {"[SOURce]:CAPacity:LIMit:WH[:STOP]?", scpi_cmd_source_cap_whstopQ, 0},
    {"[SOURce]:CAPacity:ZERO", scpi_cmd_source_cap_zero, 0}, // Reset capacity values to zero
    
    // Current set commands
    // Set/query current set
    {"[SOURce]:CURRent[:LEVel][:IMMediate][:AMPLitude]", scpi_cmd_source_current,0},    // float | min|max|default in Amps
    {"[SOURce]:CURRent[:LEVel][:IMMediate][:AMPLitude]?", scpi_cmd_source_currentQ,0},  
    
    // Set/query over current protection level
    {"[SOURce]:CURRent:PROTection[:LEVel]", scpi_cmd_source_current_prot_level,0},  // float|MIN|MAX|DEFault in Amps
    {"[SOURce]:CURRent:PROTection[:LEVel]?", scpi_cmd_source_current_prot_levelQ,0},
    
    // Set/query current range
    {"[SOURce]:CURRent:RANGe", scpi_cmd_source_current_range,0},    // L|H|float. float= determines range based on given value
    {"[SOURce]:CURRent:RANGe?", scpi_cmd_source_current_rangeQ,0},
    
    // Power set commands
    // Set/query power set level
    {"[SOURce]:POWer[:LEVel][:IMMediate][:AMPLitude]", scpi_cmd_source_pow,0},    // float|MIN|MAX|DEFault in Watt
    {"[SOURce]:POWer[:LEVel][:IMMediate][:AMPLitude]?", scpi_cmd_source_powQ,0},
    
    // Set/query power protection level and delay
    {"[SOURce]:POWer:PROTection[:LEVel]", scpi_cmd_source_pow_prot_level,0},  // float|MIN|MAX|DEFault in Watt
    {"[SOURce]:POWer:PROTection[:LEVel]?", scpi_cmd_source_pow_prot_levelQ,0},
    {"[SOURce]:POWer:PROTection:DELay[:TIMe]", scpi_cmd_source_pow_prot_delay,0}, // float|MIN|MAX|DEFault in seconds
    {"[SOURce]:POWer:PROTection:DELay[:TIMe]?", scpi_cmd_source_pow_prot_delayQ,0},

    // Resistance set/query commands
    {"[SOURce]:RESistance[:LEVel][:IMMediate][:AMPLitude]", scpi_cmd_source_res,0},  // float|MIN|MAX|DEFault in Ohm
    {"[SOURce]:RESistance[:LEVel][:IMMediate][:AMPLitude]?", scpi_cmd_source_resQ,0},

    // Voltage set/query commands
    {"[SOURce]:VOLTage[:LEVel][:IMMediate][:AMPLitude]", scpi_cmd_source_voltage,0}, // float|MIN|MAX|DEFault in Volt
    {"[SOURce]:VOLTage[:LEVel][:IMMediate][:AMPLitude]?", scpi_cmd_source_voltageQ,0},
    
    // Over voltage protection set/query commands
    {"[SOURce]:VOLTage:PROTection[:LEVel]", scpi_cmd_source_voltage_prot_level,0}, // float|MIN|MAX|DEFault Volt
    {"[SOURce]:VOLTage:PROTection[:LEVel]?", scpi_cmd_source_voltage_prot_levelQ,0},
    
    // Set/query voltage range 
    {"[SOURce]:VOLTage:RANGe", scpi_cmd_source_voltage_range,0}, // L|H|float = determines smalles range for given voltage level
    {"[SOURce]:VOLTage:RANGe?", scpi_cmd_source_voltage_rangeQ,0},
    
    // Von set/query sommands
    {"[SOURce]:VOLTage[:LEVel]:ON[:IMMediate][:AMPLitude]", scpi_cmd_source_voltage_on,0}, // float|MIN|MAX|DEFault in Volt
    {"[SOURce]:VOLTage[:LEVel]:ON[:IMMediate][:AMPLitude]?", scpi_cmd_source_voltage_onQ,0},
    // Set/query Von mode
    {"[SOURce]:VOLTage:ON:LATCh", scpi_cmd_source_voltage_on_latch,0},  // OFF|ON|INhibit
    {"[SOURce]:VOLTage:ON:LATCh?", scpi_cmd_source_voltage_on_latchQ,0},

    // System commands (in BB3 this section is module specific, not system e.g.: MODULE#:SYS:....?)
    {"SYSTem:BEEP", scpi_cmd_syst_beep,0},  // 0-2500ms
    {"SYSTem:BEEP:DURation", scpi_cmd_syst_beep_dur,0},  // 0-2500ms
    {"SYSTem:BEEP:DURation?", scpi_cmd_syst_beep_durQ,0},  
    {"SYSTem:BEEP:ON:PROTection", scpi_cmd_syst_beep_on_prot,0},  // ON/OFF/1/0
    {"SYSTem:BEEP:ON:PROTection?", scpi_cmd_syst_beep_on_protQ,0}, 
    {"SYSTem:BEEP:ON:CAPacity", scpi_cmd_syst_beep_on_cap,0},  // ON/OFF/1/0
    {"SYSTem:BEEP:ON:CAPacity?", scpi_cmd_syst_beep_on_capQ,0},  
    {"SYSTem:BEEP:ON:POLarity", scpi_cmd_syst_beep_on_pol,0},  // ON/OFF/1/0
    {"SYSTem:BEEP:ON:POLarity?", scpi_cmd_syst_beep_on_polQ,0},  
    {"SYSTem:BEEP:ON:SENSE", scpi_cmd_syst_beep_on_sense,0},  // ON/OFF/1/0
    {"SYSTem:BEEP:ON:SENSE?", scpi_cmd_syst_beep_on_senseQ,0},  
    {"SYSTem:BEEP:ON:ENCoder", scpi_cmd_syst_beep_on_enc,0},  // ON/OFF/1/0
    {"SYSTem:BEEP:ON:ENCoder?", scpi_cmd_syst_beep_on_encQ,0},  
    
    {"SYSTem:FAN:MODE", scpi_cmd_syst_fan_mode,0},  // AUTO | MANual
    {"SYSTem:FAN:MODE?", scpi_cmd_syst_fan_modeQ,0},  // AUTO | MANual
    {"SYSTem:FAN:RPM?", scpi_cmd_syst_fan_rpmQ,0},  
    {"SYSTem:FAN:SPEED", scpi_cmd_syst_fan_speed,0},  // 0-100 | MIN|MAX|DEFAULT
    {"SYSTem:FAN:SPEED?", scpi_cmd_syst_fan_speedQ,0},  
 
    {"SYSTem:TEMPerature?", scpi_cmd_syst_tempQ,0},  
    {"SYSTem:TEMPerature:PROTextion[:LEVel]", scpi_cmd_syst_temp_prot,0}, // float|MIN|MAX|DEFault in degrees Celsius 
    {"SYSTem:TEMPerature:PROTextion[:LEVel]?", scpi_cmd_syst_temp_protQ,0},
    {"SYSTem:TEMPerature:PROTextion:DELay[:TIMe]", scpi_cmd_syst_temp_prot_del,0}, // float|MIN|MAX|DEFault in seconds
    {"SYSTem:TEMPerature:PROTextion:DELay[:TIMe]?", scpi_cmd_syst_temp_prot_delQ,0},

    SCPI_CMD_LIST_END
};

}