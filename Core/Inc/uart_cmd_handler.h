#include "main.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

extern UART_HandleTypeDef huart2;
extern RTC_HandleTypeDef hrtc;

void uart_cmd_handle(uint8_t *load_flag, uint8_t *dump_flag, uint8_t *log_flag, uint8_t *clf_flag, uint8_t *half_units_cmd, char *command_buf, uint8_t *buf_index, uint8_t *recieved_byte, uint8_t *stat_flag, double *total_units, uint8_t *rfid_flag, uint8_t *uart_add_units, uint32_t *rfid_start_time);
void stat_transmit(float v_rms, float i_rms, float phase, float apparent, float real, float reactive, float pow_fact, float max_power, float total_units, float energy);
