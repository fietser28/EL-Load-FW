#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

extern bool get_var_startup_done();
extern void set_var_startup_done(bool value);
extern const char *get_var_imon();
extern void set_var_imon(const char *value);
extern const char *get_var_umon();
extern void set_var_umon(const char *value);
extern const char *get_var_pmon();
extern void set_var_pmon(const char *value);
extern const char *get_var_rmon();
extern void set_var_rmon(const char *value);
extern const char *get_var_ahmon();
extern void set_var_ahmon(const char *value);
extern const char *get_var_whmon();
extern void set_var_whmon(const char *value);
extern const char *get_var_montime();
extern void set_var_montime(const char *value);
extern bool get_var_on();
extern void set_var_on(bool value);
extern bool get_var_alive();
extern void set_var_alive(bool value);
extern bool get_var_precording();
extern void set_var_precording(bool value);
extern const char *get_var_logtxt();
extern void set_var_logtxt(const char *value);
extern int32_t get_var_nplc();
extern void set_var_nplc(int32_t value);
extern int32_t get_var_plfreq();
extern void set_var_plfreq(int32_t value);
extern float get_var_sample_rate();
extern void set_var_sample_rate(float value);
extern int32_t get_var_adc_osr();
extern void set_var_adc_osr(int32_t value);


#endif /*EEZ_LVGL_UI_VARS_H*/