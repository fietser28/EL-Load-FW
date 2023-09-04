#ifndef EEZ_LVGL_UI_STRUCTS_H
#define EEZ_LVGL_UI_STRUCTS_H

#include <eez/flow/flow.h>
#include <stdint.h>
#include <stdbool.h>

#include "vars.h"

using namespace eez;

enum FlowStructures {
    FLOW_STRUCTURE_SET_PROPERTIES = 16384,
    FLOW_STRUCTURE_CAL_POINT = 16385,
    FLOW_STRUCTURE_CAL_CONFIG = 16386,
    FLOW_STRUCTURE_KEYBOARD_INPUT = 16387
};

enum FlowArrayOfStructures {
    FLOW_ARRAY_OF_STRUCTURE_SET_PROPERTIES = 81920,
    FLOW_ARRAY_OF_STRUCTURE_CAL_POINT = 81921,
    FLOW_ARRAY_OF_STRUCTURE_CAL_CONFIG = 81922,
    FLOW_ARRAY_OF_STRUCTURE_KEYBOARD_INPUT = 81923
};

enum setPropertiesFlowStructureFields {
    FLOW_STRUCTURE_SET_PROPERTIES_FIELD_SET_NAME = 0,
    FLOW_STRUCTURE_SET_PROPERTIES_FIELD_SET_UNIT = 1,
    FLOW_STRUCTURE_SET_PROPERTIES_FIELD_SET_VALUE_MIN = 2,
    FLOW_STRUCTURE_SET_PROPERTIES_FIELD_SET_VALUE_MAX = 3,
    FLOW_STRUCTURE_SET_PROPERTIES_NUM_FIELDS
};

enum calPointFlowStructureFields {
    FLOW_STRUCTURE_CAL_POINT_FIELD_SET = 0,
    FLOW_STRUCTURE_CAL_POINT_FIELD_MEASURE = 1,
    FLOW_STRUCTURE_CAL_POINT_NUM_FIELDS
};

enum calConfigFlowStructureFields {
    FLOW_STRUCTURE_CAL_CONFIG_FIELD_NAME = 0,
    FLOW_STRUCTURE_CAL_CONFIG_FIELD_UNIT = 1,
    FLOW_STRUCTURE_CAL_CONFIG_FIELD_INSTRUCTION = 2,
    FLOW_STRUCTURE_CAL_CONFIG_FIELD_SET_TYPE = 3,
    FLOW_STRUCTURE_CAL_CONFIG_NUM_FIELDS
};

enum keyboardInputFlowStructureFields {
    FLOW_STRUCTURE_KEYBOARD_INPUT_FIELD_NAME = 0,
    FLOW_STRUCTURE_KEYBOARD_INPUT_FIELD_MIN = 1,
    FLOW_STRUCTURE_KEYBOARD_INPUT_FIELD_MAX = 2,
    FLOW_STRUCTURE_KEYBOARD_INPUT_FIELD_UNIT = 3,
    FLOW_STRUCTURE_KEYBOARD_INPUT_NUM_FIELDS
};

struct setPropertiesValue {
    Value value;
    
    setPropertiesValue() {
        value = Value::makeArrayRef(FLOW_STRUCTURE_SET_PROPERTIES_NUM_FIELDS, FLOW_STRUCTURE_SET_PROPERTIES, 0);
    }
    
    setPropertiesValue(Value value) : value(value) {}
    
    operator Value() const { return value; }
    
    operator bool() const { return value.isArray(); }
    
    const char *setName() {
        return value.getArray()->values[FLOW_STRUCTURE_SET_PROPERTIES_FIELD_SET_NAME].getString();
    }
    void setName(const char *setName) {
        value.getArray()->values[FLOW_STRUCTURE_SET_PROPERTIES_FIELD_SET_NAME] = StringValue(setName);
    }
    
    const char *setUnit() {
        return value.getArray()->values[FLOW_STRUCTURE_SET_PROPERTIES_FIELD_SET_UNIT].getString();
    }
    void setUnit(const char *setUnit) {
        value.getArray()->values[FLOW_STRUCTURE_SET_PROPERTIES_FIELD_SET_UNIT] = StringValue(setUnit);
    }
    
    float setValueMin() {
        return value.getArray()->values[FLOW_STRUCTURE_SET_PROPERTIES_FIELD_SET_VALUE_MIN].getFloat();
    }
    void setValueMin(float setValueMin) {
        value.getArray()->values[FLOW_STRUCTURE_SET_PROPERTIES_FIELD_SET_VALUE_MIN] = FloatValue(setValueMin);
    }
    
    float setValueMax() {
        return value.getArray()->values[FLOW_STRUCTURE_SET_PROPERTIES_FIELD_SET_VALUE_MAX].getFloat();
    }
    void setValueMax(float setValueMax) {
        value.getArray()->values[FLOW_STRUCTURE_SET_PROPERTIES_FIELD_SET_VALUE_MAX] = FloatValue(setValueMax);
    }
};

typedef ArrayOf<setPropertiesValue, FLOW_ARRAY_OF_STRUCTURE_SET_PROPERTIES> ArrayOfsetPropertiesValue;
struct calPointValue {
    Value value;
    
    calPointValue() {
        value = Value::makeArrayRef(FLOW_STRUCTURE_CAL_POINT_NUM_FIELDS, FLOW_STRUCTURE_CAL_POINT, 0);
    }
    
    calPointValue(Value value) : value(value) {}
    
    operator Value() const { return value; }
    
    operator bool() const { return value.isArray(); }
    
    float set() {
        return value.getArray()->values[FLOW_STRUCTURE_CAL_POINT_FIELD_SET].getFloat();
    }
    void set(float set) {
        value.getArray()->values[FLOW_STRUCTURE_CAL_POINT_FIELD_SET] = FloatValue(set);
    }
    
    float measure() {
        return value.getArray()->values[FLOW_STRUCTURE_CAL_POINT_FIELD_MEASURE].getFloat();
    }
    void measure(float measure) {
        value.getArray()->values[FLOW_STRUCTURE_CAL_POINT_FIELD_MEASURE] = FloatValue(measure);
    }
};

typedef ArrayOf<calPointValue, FLOW_ARRAY_OF_STRUCTURE_CAL_POINT> ArrayOfcalPointValue;
struct calConfigValue {
    Value value;
    
    calConfigValue() {
        value = Value::makeArrayRef(FLOW_STRUCTURE_CAL_CONFIG_NUM_FIELDS, FLOW_STRUCTURE_CAL_CONFIG, 0);
    }
    
    calConfigValue(Value value) : value(value) {}
    
    operator Value() const { return value; }
    
    operator bool() const { return value.isArray(); }
    
    const char *name() {
        return value.getArray()->values[FLOW_STRUCTURE_CAL_CONFIG_FIELD_NAME].getString();
    }
    void name(const char *name) {
        value.getArray()->values[FLOW_STRUCTURE_CAL_CONFIG_FIELD_NAME] = StringValue(name);
    }
    
    const char *unit() {
        return value.getArray()->values[FLOW_STRUCTURE_CAL_CONFIG_FIELD_UNIT].getString();
    }
    void unit(const char *unit) {
        value.getArray()->values[FLOW_STRUCTURE_CAL_CONFIG_FIELD_UNIT] = StringValue(unit);
    }
    
    const char *instruction() {
        return value.getArray()->values[FLOW_STRUCTURE_CAL_CONFIG_FIELD_INSTRUCTION].getString();
    }
    void instruction(const char *instruction) {
        value.getArray()->values[FLOW_STRUCTURE_CAL_CONFIG_FIELD_INSTRUCTION] = StringValue(instruction);
    }
    
    int setType() {
        return value.getArray()->values[FLOW_STRUCTURE_CAL_CONFIG_FIELD_SET_TYPE].getInt();
    }
    void setType(int setType) {
        value.getArray()->values[FLOW_STRUCTURE_CAL_CONFIG_FIELD_SET_TYPE] = IntegerValue(setType);
    }
};

typedef ArrayOf<calConfigValue, FLOW_ARRAY_OF_STRUCTURE_CAL_CONFIG> ArrayOfcalConfigValue;
struct keyboardInputValue {
    Value value;
    
    keyboardInputValue() {
        value = Value::makeArrayRef(FLOW_STRUCTURE_KEYBOARD_INPUT_NUM_FIELDS, FLOW_STRUCTURE_KEYBOARD_INPUT, 0);
    }
    
    keyboardInputValue(Value value) : value(value) {}
    
    operator Value() const { return value; }
    
    operator bool() const { return value.isArray(); }
    
    const char *name() {
        return value.getArray()->values[FLOW_STRUCTURE_KEYBOARD_INPUT_FIELD_NAME].getString();
    }
    void name(const char *name) {
        value.getArray()->values[FLOW_STRUCTURE_KEYBOARD_INPUT_FIELD_NAME] = StringValue(name);
    }
    
    float min() {
        return value.getArray()->values[FLOW_STRUCTURE_KEYBOARD_INPUT_FIELD_MIN].getFloat();
    }
    void min(float min) {
        value.getArray()->values[FLOW_STRUCTURE_KEYBOARD_INPUT_FIELD_MIN] = FloatValue(min);
    }
    
    float max() {
        return value.getArray()->values[FLOW_STRUCTURE_KEYBOARD_INPUT_FIELD_MAX].getFloat();
    }
    void max(float max) {
        value.getArray()->values[FLOW_STRUCTURE_KEYBOARD_INPUT_FIELD_MAX] = FloatValue(max);
    }
    
    const char *unit() {
        return value.getArray()->values[FLOW_STRUCTURE_KEYBOARD_INPUT_FIELD_UNIT].getString();
    }
    void unit(const char *unit) {
        value.getArray()->values[FLOW_STRUCTURE_KEYBOARD_INPUT_FIELD_UNIT] = StringValue(unit);
    }
};

typedef ArrayOf<keyboardInputValue, FLOW_ARRAY_OF_STRUCTURE_KEYBOARD_INPUT> ArrayOfkeyboardInputValue;


#endif /*EEZ_LVGL_UI_STRUCTS_H*/
