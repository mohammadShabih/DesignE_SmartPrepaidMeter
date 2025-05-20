#include "uart_cmd_handler.h"

void uart_cmd_handle(
    uint8_t *load_flag, uint8_t *dump_flag, uint8_t *log_flag, uint8_t *clf_flag,
    uint8_t *half_units_cmd, char *command_buf, uint8_t *buf_index, uint8_t *received_byte,
    uint8_t *stat_flag, double *total_units, uint8_t *rfid_flag,
    uint8_t *uart_add_units, uint32_t *rfid_start_time
) {

    if (*received_byte == '\n') {
        command_buf[*buf_index] = '\0';

        if (strcmp(LOAD, command_buf) == 0) {
            *load_flag = 1;
        }
        else if (strcmp(STAT, command_buf) == 0) {
            *stat_flag = 1;
        }
        else if (strcmp(SD_LOG, command_buf) == 0) {
            *log_flag ^= 1;
        }
        else if (strcmp(CLF, command_buf) == 0) {
            *clf_flag = 1;
        }
        else if ((*buf_index == 6) && (*half_units_cmd == 1)) {
            *rfid_flag = 1;
            *uart_add_units = 1;
            *half_units_cmd = 0;
            *rfid_start_time = HAL_GetTick();
        }
        else if (strcmp(DUMP, command_buf) == 0) {
            *dump_flag = 1;
        }

	if (*rfid_flag != 1) {
		memset(command_buf, 0, MAX_CMD_LEN);
	}
	*buf_index = 0;
    } else {
        if (*buf_index != MAX_CMD_LEN - 1) {
            command_buf[*buf_index] = *received_byte;
            (*buf_index)++;
        } else {
            memset(command_buf, 0, MAX_CMD_LEN);
            *buf_index = 0;
        }

        if (strcmp(UNITS, command_buf) == 0) {
            *half_units_cmd = 1;
            memset(command_buf, 0, MAX_CMD_LEN);
            *buf_index = 0;
        }
    }
    HAL_UART_Transmit(&huart2, (uint8_t *)command_buf, strlen(command_buf), HAL_MAX_DELAY);

}

void stat_transmit(float v_rms, float i_rms, float phase, float apparent, float real, float reactive, float pow_fact, float max_power, float total_units, float energy) {
	RTC_TimeTypeDef currentTime;
	RTC_DateTypeDef currentDate;
	HAL_RTC_GetTime(&hrtc, &currentTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &currentDate, RTC_FORMAT_BIN);
	energy = 0;
	char tx_buffer[MAX_TRNSMT_LEN];
	int offset = 0;
	offset += sprintf(tx_buffer + offset, "%04d/%02d/%02d %02d:%02d:%02d\n", currentDate.Year, currentDate.Month, currentDate.Date, currentTime.Hours, currentTime.Minutes, currentTime.Seconds);  // 20 bytes

	offset += sprintf(tx_buffer + offset, "Voltage:     %05.1fV\n", v_rms);               // 20 bytes
	offset += sprintf(tx_buffer + offset, "Current:    %05.0fmA\n", i_rms * 1000);        // 20 bytes
	offset += sprintf(tx_buffer + offset, "Phase:     %1.3frad\n", phase);                // 20 bytes
	offset += sprintf(tx_buffer + offset, "Apparent:    %04.0fVA\n", apparent);           // 20 bytes
	offset += sprintf(tx_buffer + offset, "Real:         %04.0fW\n", real);                // 20 bytes
	offset += sprintf(tx_buffer + offset, "Reactive:   %04.0fVAR\n", reactive);          // 20 bytes
	offset += sprintf(tx_buffer + offset, "PowerFact:    %1.3f\n", pow_fact);               // 20 bytes
	offset += sprintf(tx_buffer + offset, "Energy/d:   %05.0fWh\n", energy);              // 20 bytes
	offset += sprintf(tx_buffer + offset, "MaxPower:     %04.0fW\n", max_power);            // 20 bytes
	offset += sprintf(tx_buffer + offset, "Units:   %07.3fkWh\n", total_units);          // 20 bytes

	HAL_UART_Transmit(&huart2, (uint8_t*)tx_buffer, strlen(tx_buffer), 1000);
	return;
}
