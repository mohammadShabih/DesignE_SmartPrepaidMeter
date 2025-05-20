#include "main.h"
#include "math.h"
#include "string.h"
//extern uint8_t load_flag;
//extern uint8_t unit_flag;

void handle_input(char keyboard_input, uint8_t *display_flag, system_state* current_state, uint8_t *state_iter, system_state *stack_stack, uint8_t *load_flag, uint8_t *rfid_flag, uint8_t *k_units_index, char *k_units_in_buf, double *total_units, uint8_t *rfid_in, uint32_t *rfid_start_time, uint8_t *unit_count_flag, uint8_t *unit_count_switch) {
void handle_menu0(char keyboard_input, uint8_t *display_flag, system_state *current_state, uint8_t *state_iter, system_state *state_stack);
void handle_menu(char keyboard_input, uint8_t *display_flag, system_state* current_state, uint8_t *state_iter, system_state *state_stack, system_state state1, system_state state2);
void handle_confirm(char keyboard_input, uint8_t *display_flag, system_state *current_state, uint8_t *state_iter, system_state *state_stack, uint8_t *flag, uint8_t on_off, system_state next_state);
void pop(uint8_t *state_iter, system_state *state_stack, system_state *current_state);
void push(uint8_t *state_iter, system_state *state_stack, system_state new_state);
void send_state_stack(system_state *state_stack, uint8_t state_iter);
void handle_rfid_auth(uint8_t *rfid_in, uint8_t *display_flag, system_state *current_state, uint8_t *state_iter, system_state *state_stack, char *k_units_in_buf, double *total_units);
void handle_menu3(char keyboard_input, uint8_t *display_flag, system_state *current_state, uint8_t *state_iter, system_state *state_stack, char *k_units_in_buf, uint8_t *k_units_index, double *total_units, uint32_t *rfid_start_time, uint8_t *rfid_flag);
