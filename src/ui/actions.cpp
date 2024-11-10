// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "lvgl.h"
#include "main.h"
#include "actions.h"
#include "vars.h"
#include "structs.h"
#include "ui_glue.h"
#include "ranges.h"
#include "scpi-def.h"
#include "eeprom.h"

/*
void action_getrollerindex(lv_event_t * e) {
    lv_obj_t *roller = lv_event_get_target(e);
    uint16_t myindex = lv_roller_get_selected(roller);
    //set_var_roller1index(myindex);
}
*/

void action_getdropdownindex(lv_event_t * e) {
    lv_obj_t *dropdown = (lv_obj_t *)lv_event_get_target(e);
    uint16_t myindex = lv_dropdown_get_selected(dropdown);
    //set_var_dropdownmodeindex(myindex);
}

extern "C" {

void action_clear_power(lv_event_t * e) {
    state.clearPower();
}

void action_toggle_record(lv_event_t * e) {
    state.toggleRecord();  

}

void action_text_area_disable_blink(lv_event_t * e) {
    lv_obj_t *textarea = (lv_obj_t *)lv_event_get_target(e);
    if (lv_obj_check_type(textarea, &lv_textarea_class)) {
        lv_obj_set_style_anim_time(textarea, 0, LV_PART_CURSOR | LV_STATE_FOCUSED);
        lv_obj_refresh_style(textarea, LV_PART_CURSOR, LV_STYLE_PROP_ANY);
    }
};

// Calibration page
void action_cal_refresh_measured(lv_event_t *e) { calActions.fetchMeasured(); };
void action_cal_reset_values(lv_event_t *e)    { calActions.resetValues(); };
void action_cal_store_values(lv_event_t *e)    { calActions.storeValues(); };
void action_cal_set_dac(lv_event_t *e)         { calActions.setDAC(); };
void action_cal_store_defaults(lv_event_t * e) { calActions.storeDefaults(); };


void action_display_off(lv_event_t * e) {
    digitalWrite(TFT_BL, LOW);
};

void action_display_on(lv_event_t * e) {
      digitalWrite(TFT_BL, HIGH);
};

void action_get_type_data(lv_event_t * e) {

    ranges_e range = (ranges_e)flow::getGlobalVariable(FLOW_GLOBAL_VARIABLE_RANGE_TYPE).getInt();
    
    setPropertiesValue properties = flow::getGlobalVariable(FLOW_GLOBAL_VARIABLE_RANGE_PROPERTIES);

    properties.setName(ranges[range].setName);
    properties.setUnit(ranges[range].unitName);
    properties.setValueMin(ranges[range].minValue);
    properties.setValueMax(ranges[range].maxValue);
    properties.setValueDefault(ranges[range].defValue);
};

void action_clear_capacity_limits(lv_event_t * e) {
    state.clearCapacityLimit();
};


void action_scpi_busy_incr(lv_event_t * e) { dcl::scpi::scpi_busy_inc(); };
void action_scpi_busy_decr(lv_event_t * e) { dcl::scpi::scpi_busy_dec(); };

extern void action_beep(lv_event_t * e) 
{
    using namespace eez;
    using namespace eez::flow;

    Value duration = getUserProperty(ACTION_BEEP_PROPERTY_DURATION);
    beep(duration.getFloat() == 0 ? state.getBeepDefaultDuration() : duration.getFloat());
};

void action_clear_stat(lv_event_t * e) 
{
  using namespace eez;
  using namespace eez::flow;

  statsType_e type = (statsType_e)getUserProperty(ACTION_CLEAR_STAT_PROPERTY_TYPE).getInt();
  switch(type) 
  {
    case statsType_e::statsType_e_I:
      state.clearImonStat();
      break;
    case statsType_e::statsType_e_U:
      state.clearUmonStat();
      break;
    case statsType_e::statsType_e_P:
      state.clearPmonStat();
      break;
  }
};

void action_format_stat(lv_event_t * e)
{
    using namespace eez;
    using namespace eez::flow;

    char str[20];
    statsType_e type = (statsType_e)getUserProperty(ACTION_FORMAT_STAT_PROPERTY_TYPE).getInt();
    measureStat fromstat;
    ArrayOfstatsValue statsAll = flow::getGlobalVariable(FLOW_GLOBAL_VARIABLE_STATS_ALL);
    statsValue tostat;
    uint32_t tostatIndex;
    switch(type)
    {
        case statsType_e::statsType_e_I:
        fromstat = localstatecopy.ImonStats;
        tostatIndex = statsType_e::statsType_e_I;
        break;
        case statsType_e::statsType_e_U:
        fromstat = localstatecopy.UmonStats;
        tostatIndex = statsType_e::statsType_e_U;
        break;
        case statsType_e::statsType_e_P:
        fromstat = localstatecopy.PmonStats;
        tostatIndex = statsType_e::statsType_e_P;
        break;
    }

    formatStatValue(str,  type, fromstat.min == INFINITY ? 0 :fromstat.min);
    statsAll.at(tostatIndex).min(str);    
    formatStatValue(str,  type, fromstat.avg);
    statsAll.at(tostatIndex).avg(str);    
    formatStatValue(str,  type, fromstat.max);
    statsAll.at(tostatIndex).max(str);    
    value2str(str, fromstat.count, 0, 6, 6, true, "");
    statsAll.at(tostatIndex).count(str);    
}

} // extern "C"