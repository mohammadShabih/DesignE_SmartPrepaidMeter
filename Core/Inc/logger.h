#include "main.h"
#include "integer.h"
#include "ff.h"
#include "stdio.h"
#include "string.h"

extern UART_HandleTypeDef huart2;
extern RTC_HandleTypeDef hrtc;

void log_data(double v_rms, double i_rms, double phase, double total_units);
void log_data_uart(char *log_data, double Ipp, double Vpp, double apparent, double energy, double units, double v_rms, double i_rms, double phase, double real, double reactive, double pow_fact, double max_power, double min_units);
