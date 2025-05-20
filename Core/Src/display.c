#include "display.h"


void update_display_buf(system_state current_state, char *buf, double apparent, double energy, double units, double v_rms, double i_rms, double phase, double real, double reactive, double pow_fact, double max_power, double min_units, char *units_buf){
	if (current_state == DEFAULT_PAGE) {
		write_default(apparent, energy, units, buf);
	}
	else if (current_state == DISP_PAGE1) {
		write_disp1(v_rms, i_rms, phase, buf);
	}
	else if (current_state == DISP_PAGE2) {
		write_disp2(real, reactive, pow_fact, buf);
	}
	else if (current_state == DISP_PAGE3) {
		write_disp3(max_power, min_units, buf);
	}
	else if (current_state == MENU_1) {
		write_menu1(buf);
	}
	else if (current_state == LOAD_MENU) {
		write_load_menu(buf);
	}
	else if (current_state == LOAD_ON) {
		write_load_on(buf);
	}
	else if (current_state == LOAD_OFF) {
		write_load_off(buf);
	}
	else if (current_state == MENU_2) {
		write_menu2(buf);
	}
	else if (current_state == UNIT_MENU) {
		write_unit_menu(buf);
	}
	else if (current_state == UNIT_ON) {
		write_unit_on(buf);
	}
	else if (current_state == UNIT_OFF) {
		write_unit_off(buf);
	}
	else if (current_state == MENU_3) {
		write_menu3(buf, units_buf);
	}
	else if (current_state == RFID_AUTH){
		write_rfid(buf);
	}
}

void write_default(float apparent, float energy, float units, char *buf) {
	ssd1306_Clear();

	sprintf(buf, "Apparent: %.0fVA", apparent);
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "Energy/d: %.0fWh", energy);
	ssd1306_SetCursor(0, 10);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "Units: %6.3fkWh", units);
	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString(buf, Font_7x10);

	ssd1306_UpdateScreen();
}

void write_disp1(float v_rms, float i_rms, float phase, char *buf) {
    ssd1306_Clear();

    sprintf(buf, "Voltage: %4.1fV", v_rms);
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString(buf, Font_7x10);

    sprintf(buf, "Current: %.0fmA", i_rms*1000);
    ssd1306_SetCursor(0, 10);
    ssd1306_WriteString(buf, Font_7x10);

    sprintf(buf, "Phase: %4.1fRad", phase);
    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString(buf, Font_7x10);

    ssd1306_UpdateScreen();
}

void write_disp2(float real, float reactive, float pow_fact, char *buf) {
    ssd1306_Clear();

    sprintf(buf, "Real: %.0fW", real);
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString(buf, Font_7x10);

    sprintf(buf, "Reactive: %.0fVAR", reactive);
    ssd1306_SetCursor(0, 10);
    ssd1306_WriteString(buf, Font_7x10);

    sprintf(buf, "PowerFact: %4.3f", pow_fact);
    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString(buf, Font_7x10);

    ssd1306_UpdateScreen();
}

void write_disp3(float max_power, float min_units, char *buf) {
	ssd1306_Clear();
	RTC_TimeTypeDef currentTime;
	RTC_DateTypeDef currentDate;
	HAL_RTC_GetTime(&hrtc, &currentTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &currentDate, RTC_FORMAT_BIN);

	sprintf(buf, "%02d:%02d:%02d %02d/%02d/%02d",
	 currentTime.Hours, currentTime.Minutes, currentTime.Seconds,
	 currentDate.Year, currentDate.Month, currentDate.Date);
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "Max Power: %.0fW", max_power);
	ssd1306_SetCursor(0, 10);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "Min Units: %.0fkwh", min_units);
	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString(buf, Font_7x10);

	ssd1306_UpdateScreen();
}

void write_menu1(char *buf) {
	ssd1306_Clear();

	sprintf(buf, "Menu(Lv1 1):");
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "1: Load On/Off");
	ssd1306_SetCursor(0, 10);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "2: manage Units");
	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString(buf, Font_7x10);

	ssd1306_UpdateScreen();

}
void write_load_menu(char *buf) {
	ssd1306_Clear();
	sprintf(buf, "Load on/off");
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "1=ON");
	ssd1306_SetCursor(0, 10);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "2=OFF");
	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "'*' to confirm");
	ssd1306_SetCursor(0, 30);
	ssd1306_WriteString(buf, Font_7x10);

	ssd1306_UpdateScreen();
}

void write_menu2(char *buf) {
	ssd1306_Clear();
	sprintf(buf, "Menu(Lv1 2):");
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "1: Count On/Off");
	ssd1306_SetCursor(0, 10);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "2: Add Units");
	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString(buf, Font_7x10);

	ssd1306_UpdateScreen();
}

void write_unit_menu(char *buf) {
	ssd1306_Clear();
	sprintf(buf, "Unit Count on/off");
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "1=ON");
	ssd1306_SetCursor(0, 10);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "2=OFF");
	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "'*' to confirm");
	ssd1306_SetCursor(0, 30);
	ssd1306_WriteString(buf, Font_7x10);

	ssd1306_UpdateScreen();
}

void write_menu3(char *buf, char *units_buf) {
	ssd1306_Clear();
	sprintf(buf, "Units to add:");
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, units_buf);
	ssd1306_SetCursor(0, 10);
	ssd1306_WriteString(units_buf, Font_7x10);


	sprintf(buf, "'*' to confirm");
	ssd1306_SetCursor(0, 30);
	ssd1306_WriteString(buf, Font_7x10);

	ssd1306_UpdateScreen();

}

void write_load_on(char *buf) {
	ssd1306_Clear();
	sprintf(buf, "Load on/off");
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "1=ON#");
	ssd1306_SetCursor(0, 10);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "2=OFF");
	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "'*' to confirm");
	ssd1306_SetCursor(0, 30);
	ssd1306_WriteString(buf, Font_7x10);

	ssd1306_UpdateScreen();
}

void write_load_off(char *buf) {
	ssd1306_Clear();
	sprintf(buf, "Load on/off");
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "1=ON");
	ssd1306_SetCursor(0, 10);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "2=OFF#");
	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "'*' to confirm");
	ssd1306_SetCursor(0, 30);
	ssd1306_WriteString(buf, Font_7x10);

	ssd1306_UpdateScreen();
}

void write_unit_on(char *buf) {
	ssd1306_Clear();
	sprintf(buf, "Unit Count on/off");
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "1=ON#");
	ssd1306_SetCursor(0, 10);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "2=OFF");
	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "'*' to confirm");
	ssd1306_SetCursor(0, 30);
	ssd1306_WriteString(buf, Font_7x10);

	ssd1306_UpdateScreen();
}

void write_unit_off(char *buf) {
	ssd1306_Clear();
	sprintf(buf, "Unit Count on/off");
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "1=ON");
	ssd1306_SetCursor(0, 10);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "2=OFF#");
	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString(buf, Font_7x10);

	sprintf(buf, "'*' to confirm");
	ssd1306_SetCursor(0, 30);
	ssd1306_WriteString(buf, Font_7x10);

	ssd1306_UpdateScreen();
}

void write_rfid(char *buf) {
	ssd1306_Clear();
	sprintf(buf, "Present Tag Card");
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(buf, Font_7x10);
	ssd1306_UpdateScreen();

}
