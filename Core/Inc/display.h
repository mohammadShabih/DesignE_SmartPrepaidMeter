#include "ssd1306.h"
#include "ssd1306_defines.h"
#include "fonts.h"
#include "stdio.h"

extern RTC_HandleTypeDef hrtc;

void update_display_buf(system_state current_state, char *buf, double apparent, double energy, double units, double v_rms, double i_rms, double phase, double real, double reactive, double pow_fact, double max_power, double min_units, char *units_buf);
void write_default(float apparent, float energy, float units, char *buf);
void write_disp1(float v_rms, float i_rms, float phase, char *buf);
void write_disp2(float real, float reactive, float pow_fact, char *buf);
void write_disp3(float max_power, float min_units, char *buf);
void write_menu1(char *buf);
void write_load_menu(char *buf);
void write_load_on(char *buf);
void write_load_off(char *buf);
void write_menu2(char *buf);
void write_unit_menu(char *buf);
void write_unit_on(char *buf);
void write_unit_off(char *buf);
void write_menu3(char *buf, char *units_buf);
void write_rfid(char *buf);
