#include "stdint.h"
#include "math.h"

#define PI_F 3.1415926f

void reactive_pow(double *reactive, double v_rms, double i_rms, double phase);
void real_pow(double *real, double v_rms, double i_rms, double phase);
void apparent_pow(double *apparent, double v_rms, double i_rms);
void power_fact(double *pow_fact, double real, double apparent);
void max_power_calc(double *max_power,double max_v, double max_i);
double wrap_to_half_pi(double angle);
void phase_calc_IQ(double *voltage_buf, double *current_buf, int size, double voltage_mean, double current_mean, double *phase_diff_rad, double *ref_sin, double *ref_cos);
double wrap_to_half_pi(double angle);
void calculate_rms(uint16_t *adc_buf, int size, double *v_rms, double *i_rms, double *voltage_buf, double *current_buf, double *voltage_mean, double *current_mean, double *max_v, double *max_i);
