

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
    {"*OPC", SCPI_CoreOpc, 0},
    {"*OPC?", SCPI_CoreOpcQ, 0},
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

    /* Fetch */
    {"FETCh[:SCALar]:CURRent[:DC]?", scpi_cmd_fetch_current, 0},
    {"FETCh[:SCALar]:VOLTage[:DC]?", scpi_cmd_fetch_voltage, 0},
    {"FETCh[:SCALar]:POWer[:DC]?", scpi_cmd_fetch_power, 0},

    // Averaging functions
    {"[SENSe]:NPLCycles", scpi_cmd_sense_nplc, 0},
    {"[SENSe]:NPLCycles?", scpi_cmd_sense_nplcQ, 0},
    {"[SENSe]:PLFreq", scpi_cmd_sense_plfreq, 0},
    {"[SENSe]:PLFreq?", scpi_cmd_sense_plfreqQ, 0},

    // Remote voltage sensing
    {"[SENSe]:VOLTage:REMote", scpi_cmd_sense_volt_remote, 0},
    {"[SENSe]:VOLTage:REMote?", scpi_cmd_sense_volt_remoteQ, 0},
    
    // Main mode
    {"[SOURce]:INPut:MODE", scpi_cmd_source_mode, 0},
    {"[SOURce]:INPut:MODE?", scpi_cmd_source_modeQ, 0},
    
    // Global protection
    {"[SOURce]:INPut:PROTection:CLEar", scpi_cmd_source_input_prot_clear, 0},
    {"[SOURce]:INPut:PROTection:TRIPped?", scpi_cmd_source_input_prot_tripQ, 0},

    // Current set commands
    {"[SOURce]:CURRent[:LEVel][:IMMediate][:AMPLitude]", scpi_cmd_source_current,0},
    {"[SOURce]:CURRent[:LEVel][:IMMediate][:AMPLitude]?", scpi_cmd_source_currentQ,0},
    
    {"[SOURce]:CURRent:PROTection[:LEVel]", scpi_cmd_source_current_prot_level,0},
    {"[SOURce]:CURRent:PROTection[:LEVel]?", scpi_cmd_source_current_prot_levelQ,0},
    
    {"[SOURce]:CURRent:RANGe", scpi_cmd_source_current_range,0},
    {"[SOURce]:CURRent:RANGe?", scpi_cmd_source_current_rangeQ,0},
    
    // Voltage set commands
    {"[SOURce]:VOLTage[:LEVel][:IMMediate][:AMPLitude]", scpi_cmd_source_voltage,0},
    {"[SOURce]:VOLTage[:LEVel][:IMMediate][:AMPLitude]?", scpi_cmd_source_voltageQ,0},
    
    {"[SOURce]:VOLTage:PROTection[:LEVel]", scpi_cmd_source_voltage_prot_level,0},
    {"[SOURce]:VOLTage:PROTection[:LEVel]?", scpi_cmd_source_voltage_prot_levelQ,0},
    
    {"[SOURce]:VOLTage:RANGe", scpi_cmd_source_voltage_range,0},
    {"[SOURce]:VOLTage:RANGe?", scpi_cmd_source_voltage_rangeQ,0},
    


    /* DMM */
//    {"MEASure:VOLTage:DC?", DMM_MeasureVoltageDcQ, 0},
//    {"CONFigure:VOLTage:DC", DMM_ConfigureVoltageDc, 0},
//    {"MEASure:VOLTage:DC:RATio?", SCPI_StubQ, 0},
//    {"MEASure:VOLTage:AC?", DMM_MeasureVoltageAcQ, 0},
//    {"MEASure:CURRent:DC?", SCPI_StubQ, 0},
//    {"MEASure:CURRent:AC?", SCPI_StubQ, 0},
//    {"MEASure:RESistance?", SCPI_StubQ, 0},
//    {"MEASure:FRESistance?", SCPI_StubQ, 0},
//    {"MEASure:FREQuency?", SCPI_StubQ, 0},
//    {"MEASure:PERiod?", SCPI_StubQ, 0},

 //   {"SYSTem:COMMunication:TCPIP:CONTROL?", SCPI_SystemCommTcpipControlQ, 0},

//    {"TEST:BOOL", TEST_Bool, 0},
//    {"TEST:CHOice?", TEST_ChoiceQ, 0},
//    {"TEST#:NUMbers#", TEST_Numbers, 0},
//    {"TEST:TEXT", TEST_Text, 0},
//    {"TEST:ARBitrary?", TEST_ArbQ, 0},
//    {"TEST:CHANnellist", TEST_Chanlst, 0},

    SCPI_CMD_LIST_END
};


}