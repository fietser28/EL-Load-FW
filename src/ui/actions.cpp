// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "lvgl.h"
#include "main.h"
#include "actions.h"
#include "vars.h"
#include "events.h"
#include "structs.h"
#include "ui_glue.h"
#include "ranges.h"
#include "scpi-def.h"
#include "eeprom.h"

extern "C" {

void action_clear_power(lv_event_t * e) {
    state.clearPower();
}

void action_toggle_record(lv_event_t * e) {
    state.toggleRecord();  

}


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
    
    //SERIALDEBUG.printf("keyboard range: %d\n", range);

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

    formatStatValue(str,  type, fromstat.min == INFINITY ? 0 :fromstat.min, false);
    statsAll.at(tostatIndex).min(str);    
    formatStatValue(str,  type, fromstat.avg, false);
    statsAll.at(tostatIndex).avg(str);    
    formatStatValue(str,  type, fromstat.max, false);
    statsAll.at(tostatIndex).max(str);    
    value2str(str, fromstat.count, 0, 6, 6, true, "");
    statsAll.at(tostatIndex).count(str);    
    formatStatValue(str, type, fromstat.count == 0 ? 0.0f : sqrt(fromstat.M2 / (float)fromstat.count), true);
    statsAll.at(tostatIndex).dev(str);    
}

void action_events_table_setup(lv_event_t * e) {
    using namespace eez;
    using namespace eez::flow;

    lv_obj_t* table = objects.events_table;

    lv_obj_set_style_width(table,15, LV_PART_SCROLLBAR);
    lv_table_set_column_count(table, 1);
    lv_table_set_column_width(table, 0, 305);

};

void action_events_table_load(lv_event_t * e)
{
    using namespace dcl::events;
    using namespace eez::flow;

    static char cellbuff[eventTextMaxSize];
    lv_obj_t* table = objects.events_table;

    eventType_e filter = (eventType_e)getGlobalVariable(FLOW_GLOBAL_VARIABLE_EVENT_FILTER_SET).getInt();
    
    uint16_t c = 0;
    uint16_t i = 0;
    
    // Clear table
    lv_table_set_row_count(table, 0);

    auto addrow = [&]
    {
        if (g_eventList[i].type >= filter)
        {
            uint32_t h = g_eventList[i].timeStamp / (3600 * 1000);
            uint32_t m = g_eventList[i].timeStamp / (60 * 1000) - h * 3600;
            uint32_t s = g_eventList[i].timeStamp / 1000 - h * 3600 - m * 60;
            snprintf(cellbuff, eventTextMaxSize, "%s %02d:%02d:%02d %s", EVENT_TYPE_NAMES[g_eventList[i].type], h, m, s, g_eventList[i].msg);
            lv_table_set_cell_value(table, c, 0, cellbuff);
            lv_table_add_cell_ctrl(table, c, 0, LV_TABLE_CELL_CTRL_TEXT_CROP);
            c++;
        };
        i++;
    };

    if (g_eventListHead >= g_eventListTail)
    {
        i = g_eventListTail;

        while(i <= g_eventListHead && i < eventQueueSize)
        {
            addrow();
        } 
    };
    if (g_eventListHead < g_eventListTail) 
    {
        i = g_eventListTail;
        while(i < eventQueueSize)
        {
            addrow();
        } 
        i = 0;
        while(i <= g_eventListHead) 
        {
            addrow();
        }
    };

    // Jump to last line
    lv_table_set_selected_cell(table, c, 0);
};

} // extern "C"