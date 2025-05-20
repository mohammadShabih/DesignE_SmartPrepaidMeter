#include "keypad.h"
extern huart2;

char get_command(uint8_t row, uint8_t col) {
	char input[4][3] = {{'1', '2', '3'},{'4', '5', '6'},{'7', '8', '9'},{'*', '0', '#'}};
	return input[row-1][col-1];
}

void debounce_rising(uint8_t row, uint8_t *command_flag, uint8_t *button_pressed) {
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) && (row == 1)) {
		*command_flag = 1;
		*button_pressed = 1;
	}
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) && (row == 2)) {
		*command_flag = 1;
		*button_pressed = 1;
	}
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) && (row == 3)) {
		*command_flag = 1;
		*button_pressed = 1;
	}
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15) && (row == 4)) {
		*command_flag = 1;
		*button_pressed = 1;
	}
	return;
}

void debounce_falling(uint8_t row, uint8_t *button_pressed) {
	if ((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == 0) && (row == 1)) {
		*button_pressed = 0;
	}
	if ((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == 0) && (row == 2)) {
		*button_pressed = 0;
	}
	if ((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) == 0) && (row == 3)) {
		*button_pressed = 0;
	}
	if ((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15) == 0) && (row == 4)) {
		*button_pressed = 0;
	}
}

void column_drive(uint8_t *col) {
	if (*col == 1) {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);
	}
	else if (*col == 2) {
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);
	}
	else if (*col == 3) {
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
		*col = 0;
	}
	*col += 1;
}
