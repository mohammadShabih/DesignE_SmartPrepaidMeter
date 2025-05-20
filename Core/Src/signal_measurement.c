#include "signal_measurement.h"

void calculate_rms(uint16_t *adc_buf, int size, double *v_rms, double *i_rms, double *voltage_buf, double *current_buf, double *voltage_mean, double *current_mean, double *max_v, double *max_i) {
    double voltage_sum = 0;
    double current_sum = 0;
    int v_index = 0, i_index = 0;
    *max_i = 0;
    *max_v = 0;
    double min_i = 3.3;
    double min_v = 3.3;
    double val = 0;
    //double Vpp, Ipp;

    for (int k = 0; k < size; k++) {
        val =  3.3 * ((double)adc_buf[k]) / 4095.0;
        if (k % 2 == 0) {
            voltage_buf[v_index++] = val;
            voltage_sum += val;
            if (val > *max_v) {
            	*max_v = val;
            }
            if (val < min_v) {
            	min_v = val;
            }
        } else {
            current_buf[i_index++] = val;
            current_sum += val;
            if (val > *max_i) {
            	*max_i = val;
            }
            if (val < min_i) {
            	min_i = val;
            }
        }
    }
    //Vpp = max_v - min_v;
    //Ipp = max_i - min_i;

    *voltage_mean = voltage_sum / (size / 2);
    *current_mean = current_sum / (size / 2);
    *max_i = (*max_i - *current_mean) * 12;
	*max_v = (*max_v - *voltage_mean) * 270;

    voltage_sum = 0;
    current_sum = 0;

    for (int i = 0; i < size / 2; i++) {
        double v = voltage_buf[i] - *voltage_mean;
        voltage_sum += v * v;

        double c = current_buf[i] - *current_mean;
        current_sum += c * c;
    }

    *v_rms = sqrt(voltage_sum / (size / 2)) * 247;
    *i_rms = sqrt(current_sum / (size / 2)) * 16;
}

void phase_calc_IQ(double *voltage_buf, double *current_buf, int size, double voltage_mean, double current_mean, double *phase_diff_rad, double *ref_sin, double *ref_cos) {
    double v_sum_sin = 0;
    double v_sum_cos = 0;
    double i_sum_sin = 0;
    double i_sum_cos = 0;
    double V, I;
    double v_phase_rad;
    double i_phase_rad;
    //double angle;

    for (int i = 0; i < size; i++) {
        V = voltage_buf[i] - voltage_mean;
        v_sum_sin += V * ref_sin[i];
        v_sum_cos += V * ref_cos[i];

        I = current_buf[i] - current_mean;
        i_sum_sin += I * ref_sin[i];
        i_sum_cos += I * ref_cos[i];
    }

    v_phase_rad = atan2(v_sum_sin, v_sum_cos);
    i_phase_rad = atan2(i_sum_sin, i_sum_cos);

    *phase_diff_rad = i_phase_rad - v_phase_rad;
    *phase_diff_rad = wrap_to_half_pi(*phase_diff_rad);
    //*phase_diff_rad = *phase_diff_rad * (180/PI_F);
}


void reactive_pow(double *reactive, double v_rms, double i_rms, double phase) {
	*reactive = -1 * (v_rms) * (i_rms) * sinf(phase);
	// leading current
}

void real_pow(double *real, double v_rms, double i_rms, double phase) {
	*real = (v_rms) * (i_rms) * cosf(phase);
}

void apparent_pow(double *apparent, double v_rms, double i_rms) {
	*apparent = (v_rms) * (i_rms);
}

void power_fact(double *pow_fact, double real, double apparent) {
	*pow_fact = (real / apparent);
}

void max_power_calc(double *max_power,double max_v, double max_i) {
	*max_power = max_v * max_i;
}

double wrap_to_half_pi(double angle) {
    return asin(sin(angle));
}
