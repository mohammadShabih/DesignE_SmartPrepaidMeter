#include "ui.h"

extern UART_HandleTypeDef huart2;

void handle_input(char keyboard_input, uint8_t *display_flag, system_state* current_state, uint8_t *state_iter, system_state *stack_stack, uint8_t *load_flag, uint8_t *rfid_flag, uint8_t *k_units_index, char *k_units_in_buf, double *total_units, uint8_t *rfid_in, uint32_t *rfid_start_time, uint8_t *unit_count_flag, uint8_t *unit_count_switch) {
	if (*current_state == DEFAULT_PAGE || *current_state == DISP_PAGE1 || *current_state == DISP_PAGE2 || *current_state == DISP_PAGE3) {
		handle_menu0(keyboard_input, display_flag, current_state, state_iter, stack_stack);
	}
	else if (*current_state == MENU_1) {
		handle_menu(keyboard_input, display_flag, current_state, state_iter, stack_stack, LOAD_MENU, MENU_2);
	}
	else if (*current_state == LOAD_MENU) {
		handle_menu(keyboard_input, display_flag, current_state, state_iter, stack_stack, LOAD_ON, LOAD_OFF);
	}
	else if (*current_state == LOAD_ON || *current_state == LOAD_OFF) {
		handle_confirm(keyboard_input, display_flag, current_state, state_iter, stack_stack, load_flag, 1, DEFAULT_PAGE);
	}
	else if (*current_state == MENU_2) {
		handle_menu(keyboard_input, display_flag, current_state, state_iter, stack_stack, UNIT_MENU, MENU_3);
	}
	else if (*current_state == UNIT_MENU) {
		handle_menu(keyboard_input, display_flag, current_state, state_iter, stack_stack, UNIT_ON, UNIT_OFF);
	}
	else if (*current_state == UNIT_ON || *current_state == UNIT_OFF) {
		handle_unit_confirm(keyboard_input, display_flag, current_state, state_iter, stack_stack, rfid_flag, 1, RFID_AUTH, unit_count_switch);
		*rfid_start_time =  HAL_GetTick();
	}
	else if (*current_state == MENU_3) {
		handle_menu3(keyboard_input, display_flag, current_state, state_iter, stack_stack, k_units_in_buf, k_units_index, total_units, rfid_start_time, rfid_flag);
	}
	else if (*current_state == RFID_AUTH) {
		//HAL_UART_Transmit(&huart2, (uint8_t *)"h", 1, HAL_MAX_DELAY);
		if (*unit_count_switch == 1) {
			*display_flag = 1;
			*rfid_in = 0;
			//HAL_UART_Transmit(&huart2, (uint8_t *)"l", 1, HAL_MAX_DELAY);
			while (*current_state != DEFAULT_PAGE) {
				pop(state_iter, stack_stack, current_state);
			}
			*unit_count_switch  = 0;
			*unit_count_flag ^= 1;
		}
		else {
			handle_rfid_auth(rfid_in, display_flag, current_state, state_iter, stack_stack, k_units_in_buf, total_units);
		}
	}
	return;
}

void handle_rfid_auth(uint8_t *rfid_in, uint8_t *display_flag, system_state *current_state, uint8_t *state_iter, system_state *state_stack, char *k_units_in_buf, double *total_units) {
	if (*rfid_in == 1) {
		//HAL_UART_Transmit(&huart2, (uint8_t *)"i", 1, HAL_MAX_DELAY);
		// add the units
		double add_watts, unit = 0;
		for (int i = 4; i >= 0; i--) {
			unit = (k_units_in_buf[i] - '0') * pow(10, abs(4-i));
			add_watts += unit;
		}
		*total_units += add_watts / 1000.0f;

		//HAL_UART_Transmit(&huart2, (uint8_t *)"j", 1, HAL_MAX_DELAY);

		// reset state
		memset(k_units_in_buf, 0, 5);
		//HAL_UART_Transmit(&huart2, (uint8_t *)"k", 1, HAL_MAX_DELAY);
		*display_flag = 1;
		*rfid_in = 0;
		//HAL_UART_Transmit(&huart2, (uint8_t *)"l", 1, HAL_MAX_DELAY);
		while (*current_state != DEFAULT_PAGE) {
			pop(state_iter, state_stack, current_state);
		}
		//HAL_UART_Transmit(&huart2, (uint8_t *)"m", 1, HAL_MAX_DELAY);
	}
	else {
		*display_flag = 1;
		while (*current_state != DEFAULT_PAGE) {
					pop(state_iter, state_stack, current_state);
				}
	}
	return;
}

void handle_menu0(char keyboard_input, uint8_t *display_flag, system_state *current_state, uint8_t *state_iter, system_state *state_stack) {
	if (keyboard_input == '0') {
		*display_flag = 1;
		*current_state = DEFAULT_PAGE;
	}
	else if (keyboard_input == '1') {
		*display_flag = 1;
		*current_state = DISP_PAGE1;
	}
	else if (keyboard_input == '2') {
		*display_flag = 1;
		*current_state = DISP_PAGE2;
	}
	else if (keyboard_input == '3') {
		*display_flag = 1;
		*current_state = DISP_PAGE3;
	}
	else if (keyboard_input == '*') {
		*display_flag = 1;
		*current_state = MENU_1;
		push(state_iter, state_stack, MENU_1);
	}
	return;
}

void handle_menu(char keyboard_input, uint8_t *display_flag, system_state* current_state, uint8_t *state_iter, system_state *state_stack, system_state state1, system_state state2) {
	if (keyboard_input == '1') {
		*display_flag = 1;
		*current_state = state1;
		push(state_iter, state_stack, state1);
	}
	else if (keyboard_input == '2') {
		*display_flag = 1;
		*current_state = state2;
		push(state_iter, state_stack, state2);
	}
	else if (keyboard_input == '#') {
		*display_flag = 1;
		pop(state_iter, state_stack, current_state);
	}
	return;
}

void handle_confirm(char keyboard_input, uint8_t *display_flag, system_state *current_state, uint8_t *state_iter, system_state *state_stack, uint8_t *flag, uint8_t on_off, system_state next_state) {
	if (keyboard_input == '*') {
		*display_flag = 1;
		*current_state = next_state;
		*state_iter = 0;
		*flag = on_off;
	}
	else if (keyboard_input == '#') {
		*display_flag = 1;
		pop(state_iter, state_stack, current_state);
	}
	return;
}

void handle_unit_confirm(char keyboard_input, uint8_t *display_flag, system_state *current_state, uint8_t *state_iter, system_state *state_stack, uint8_t *flag, uint8_t on_off, system_state next_state, uint8_t *unit_count_switch) {
	if (keyboard_input == '*') {
		*display_flag = 1;
		*current_state = next_state;
		*state_iter = 0;
		*flag = on_off;
		*unit_count_switch = 1;
	}
	else if (keyboard_input == '#') {
		*display_flag = 1;
		pop(state_iter, state_stack, current_state);
	}
	return;
}

void handle_menu3(char keyboard_input, uint8_t *display_flag, system_state *current_state, uint8_t *state_iter, system_state *state_stack, char *k_units_in_buf, uint8_t *k_units_index, double *total_units, uint32_t *rfid_start_time, uint8_t *rfid_flag) {
	if (keyboard_input != '#' && *k_units_index < 5) {
		k_units_in_buf[*k_units_index] = keyboard_input;
		*k_units_index += 1;
		*display_flag = 1;
	}
	else if (keyboard_input == '*' || *k_units_index == 5) {
		*display_flag = 1;
		*rfid_flag = 1;
		*current_state = RFID_AUTH;
		*k_units_index = 0;
		push(state_iter, state_stack, RFID_AUTH);
		*rfid_start_time = HAL_GetTick();
	}
	else if (keyboard_input == '#') {
		*display_flag = 1;
		pop(state_iter, state_stack, current_state);
	}
}

void pop(uint8_t *state_iter, system_state *state_stack, system_state *current_state) {
	(*state_iter)--;
	if (*state_iter > 0) {
		*current_state = state_stack[*state_iter-1];
	}
	else if (*state_iter == 0) {
		state_stack[*state_iter] = DEFAULT_PAGE;
		*current_state = DEFAULT_PAGE;
	}
}

void push(uint8_t *state_iter, system_state *state_stack, system_state new_state) {
	if (*state_iter < 5) {
		state_stack[*state_iter] = new_state;
		(*state_iter)++;
	}
}

