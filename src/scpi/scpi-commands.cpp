

#include "scpi/scpi.h"

#include "main.h"
#include "scpi-def.h"

using namespace dcl;

namespace dcl::scpi {

const scpi_command_t scpi_commands[] = {
    /* IEEE Mandated Commands (SCPI std V1999.0 4.1.1) */
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

    /* Calibration */
    {"CALibration[:MODE]", scpi_cmd_cal, 0},
    {"CALibration[:MODE]?", scpi_cmd_calQ, 0},

    {"CALibration:TYPe", scpi_cmd_cal_type, 0},
    {"CALibration:TYPe?", scpi_cmd_cal_typeQ, 0},

    {"CALibration:POInt", scpi_cmd_cal_point, 0},
    {"CALibration:POInt?", scpi_cmd_cal_pointQ, 0},
    {"CALibration:POInt:MAX?", scpi_cmd_cal_point_maxQ, 0},

    {"CALibration:SET", scpi_cmd_cal_set, 0},
    {"CALibration:SET?", scpi_cmd_cal_setQ, 0},

    {"CALibration:ADC?", scpi_cmd_cal_adcQ, 0},

    {"CALibration:MEASure?", scpi_cmd_cal_measQ, 0},

//    {"CALibration:CURRent[:DATA]", scpi_cmd_cal_curr, 0},
//    {"CALibration:CLEar", scpi_cmd_cal_cle, 0},

    {"CALibration:MEASure", scpi_cmd_cal_meas, 0},

    //{"CALibration:STATe", scpi_cmd_cal_stat, 0},
    {"CALibration[:TYPe]:SAVE", scpi_cmd_cal_type_save, 0},
    {"CALibration[:TYPe]:RESET", scpi_cmd_cal_type_reset, 0},
//    {"CALibration:TYPE", scpi_cmd_cal_type, 0},

//    {"CALibration:VOLTage[:DATA]", scpi_cmd_cal_volt, 0},


    /* Fetch */
    {"FETCh[:SCALar]:CURRent[:DC]?", scpi_cmd_fetch_current, 0},
    {"FETCh[:SCALar]:VOLTage[:DC]?", scpi_cmd_fetch_voltage, 0},
    {"FETCh[:SCALar]:POWer[:DC]?", scpi_cmd_fetch_power, 0},
    {"FETCh:CAPacity?", scpi_cmd_fetch_cap, 0},

    // Averaging functions
    {"[SENSe]:NPLCycles", scpi_cmd_sense_nplc, 0},
    {"[SENSe]:NPLCycles?", scpi_cmd_sense_nplcQ, 0},
    {"[SENSe]:PLFreq", scpi_cmd_sense_plfreq, 0},
    {"[SENSe]:PLFreq?", scpi_cmd_sense_plfreqQ, 0},

    // Remote voltage sensing
    {"[SENSe]:VOLTage:REMote", scpi_cmd_sense_volt_remote, 0},
    {"[SENSe]:VOLTage:REMote?", scpi_cmd_sense_volt_remoteQ, 0},
    
    // ON/OFF state
    {"[SOURce]:INPut[:STATe]", scpi_cmd_source_input_state, 0},
    {"[Source]:INPut[:STATe]?", scpi_cmd_source_input_stateQ, 0},

    // Main mode
    {"[SOURce]:INPut:MODE", scpi_cmd_source_mode, 0},
    {"[SOURce]:INPut:MODE?", scpi_cmd_source_modeQ, 0},
    
    // Global protection
    {"[SOURce]:INPut:PROTection:CLEar", scpi_cmd_source_input_prot_clear, 0},
    {"[SOURce]:INPut:PROTection:TRIPped?", scpi_cmd_source_input_prot_tripQ, 0},

    // Capacity set commands
    {"[SOURce]:CAPacity[:STATe]", scpi_cmd_source_cap, 0},  // ON|OFF|1|0
    {"[SOURce]:CAPacity[:STATe]?", scpi_cmd_source_capQ, 0},
    {"[SOURce]:CAPacity:LIMit[:ENable]", scpi_cmd_source_cap_limit, 0}, // 1/0  Enable/disable capacity limits
    {"[SOURce]:CAPacity:LIMit[:ENable]?", scpi_cmd_source_cap_limitQ, 0},
    {"[SOURce]:CAPacity:LIMit:AH[:STOP]", scpi_cmd_source_cap_ahstop, 0},  // float,  Ah limit
    {"[SOURce]:CAPacity:LIMit:AH[:STOP]?", scpi_cmd_source_cap_ahstopQ, 0},
    {"[SOURce]:CAPacity:LIMit:TIMe[:STOP]", scpi_cmd_source_cap_timestop, 0}, // // float,  max. time limit in seconds
    {"[SOURce]:CAPacity:LIMit:TIMe[:STOP]?", scpi_cmd_source_cap_timestop, 0},
    {"[SOURce]:CAPacity:LIMit:VOLTage[:STOP]", scpi_cmd_source_cap_voltstop, 0},   // float, min. Volt limit 
    {"[SOURce]:CAPacity:LIMit:VOLTAge[:STOP]?", scpi_cmd_source_cap_voltstopQ, 0},
    {"[SOURce]:CAPacity:ZERO", scpi_cmd_source_cap_clear, 0}, // Reset capacity values to zero
    
    // Current set commands
    {"[SOURce]:CURRent[:LEVel][:IMMediate][:AMPLitude]", scpi_cmd_source_current,0},    // float | min|max|default
    {"[SOURce]:CURRent[:LEVel][:IMMediate][:AMPLitude]?", scpi_cmd_source_currentQ,0},  
    
    {"[SOURce]:CURRent:PROTection[:LEVel]", scpi_cmd_source_current_prot_level,0},
    {"[SOURce]:CURRent:PROTection[:LEVel]?", scpi_cmd_source_current_prot_levelQ,0},
    
    {"[SOURce]:CURRent:RANGe", scpi_cmd_source_current_range,0},
    {"[SOURce]:CURRent:RANGe?", scpi_cmd_source_current_rangeQ,0},
    
    // Power set commands
    {"[SOURce]:POWer[:LEVel][:IMMediate][:AMPLitude]", scpi_cmd_source_pow,0},
    {"[SOURce]:POWer[:LEVel][:IMMediate][:AMPLitude]?", scpi_cmd_source_powQ,0},
    
    {"[SOURce]:POWer:PROTection[:LEVel]", scpi_cmd_source_pow_prot_level,0},
    {"[SOURce]:POWer:PROTection[:LEVel]?", scpi_cmd_source_pow_prot_levelQ,0},

    {"[SOURce]:POWer:PROTection:DELay[:TIMe]", scpi_cmd_source_pow_prot_delay,0},
    {"[SOURce]:POWer:PROTection:DELay[:TIMe]?", scpi_cmd_source_pow_prot_delayQ,0},

    // Resistance set commands
    {"[SOURce]:RESistance[:LEVel][:IMMediate][:AMPLitude]", scpi_cmd_source_res,0},
    {"[SOURce]:RESistance[:LEVel][:IMMediate][:AMPLitude]?", scpi_cmd_source_resQ,0},

    // Voltage set commands
    {"[SOURce]:VOLTage[:LEVel][:IMMediate][:AMPLitude]", scpi_cmd_source_voltage,0},
    {"[SOURce]:VOLTage[:LEVel][:IMMediate][:AMPLitude]?", scpi_cmd_source_voltageQ,0},
    
    {"[SOURce]:VOLTage:PROTection[:LEVel]", scpi_cmd_source_voltage_prot_level,0},
    {"[SOURce]:VOLTage:PROTection[:LEVel]?", scpi_cmd_source_voltage_prot_levelQ,0},
    
    {"[SOURce]:VOLTage:RANGe", scpi_cmd_source_voltage_range,0},
    {"[SOURce]:VOLTage:RANGe?", scpi_cmd_source_voltage_rangeQ,0},
    
    // Von set sommands
    {"[SOURce]:VOLTage[:LEVel]:ON[:IMMediate][:AMPLitude]", scpi_cmd_source_voltage_on,0},
    {"[SOURce]:VOLTage[:LEVel]:ON[:IMMediate][:AMPLitude]?", scpi_cmd_source_voltage_onQ,0},
    {"[SOURce]:VOLTage:ON:LATCh", scpi_cmd_source_voltage_on_latch,0},
    {"[SOURce]:VOLTage:ON:LATCh?", scpi_cmd_source_voltage_on_latchQ,0},

    // System (in BB3 this section is module specific, not system: SYST:MODULE#:....?)
    {"SYSTem:FAN:MODE", scpi_cmd_syst_fan_mode,0},  // AUTO | MANual
    {"SYSTem:FAN:MODE?", scpi_cmd_syst_fan_modeQ,0},  // AUTO | MANual
    {"SYSTem:FAN:RPM?", scpi_cmd_syst_fan_rpmQ,0},  
    {"SYSTem:FAN:SPEED", scpi_cmd_syst_fan_speed,0},  // 0-100 | MIN|MAX|DEFAULT
    {"SYSTem:FAN:SPEED?", scpi_cmd_syst_fan_speedQ,0},  
 
    {"SYSTem:TEMPerature?", scpi_cmd_syst_tempQ,0},  
    {"SYSTem:TEMPerature:PROTextion[:LEVel]", scpi_cmd_syst_temp_prot,0},
    {"SYSTem:TEMPerature:PROTextion[:LEVel]?", scpi_cmd_syst_temp_protQ,0},
    {"SYSTem:TEMPerature:PROTextion:DELay[:TIMe]", scpi_cmd_syst_temp_prot_del,0},
    {"SYSTem:TEMPerature:PROTextion:DELay[:TIMe]?", scpi_cmd_syst_temp_prot_delQ,0},

    SCPI_CMD_LIST_END
};


}