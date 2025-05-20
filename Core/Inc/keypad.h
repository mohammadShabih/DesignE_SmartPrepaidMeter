#include "stdint.h"
#include "stm32g0xx_hal.h"

char get_command(uint8_t row, uint8_t col);

void debounce_rising(uint8_t row, uint8_t *command_flag, uint8_t *button_pressed);

void column_drive(uint8_t *col);

void debounce_falling(uint8_t row, uint8_t *button_pressed);
