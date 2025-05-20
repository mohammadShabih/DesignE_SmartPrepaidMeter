#include "logger.h"

void clear_sd_file(void) {
    FATFS FatFs;    // File system object
    FIL fil;        // File object
    FRESULT fres;   // FatFs result code

    fres = f_mount(&FatFs, "", 1);
    if (fres != FR_OK) {
        myprintf("f_mount error (%i)\r\n", fres);
        return;
    }

    fres = f_open(&fil, "DATA.csv", FA_WRITE | FA_CREATE_ALWAYS);
    if (fres != FR_OK) {
        myprintf("f_open error when clearing file (%i)\r\n", fres);
        f_mount(NULL, "", 1);  // Unmount before returning
        return;
    }

    f_close(&fil);

    f_mount(NULL, "", 1);

    myprintf("DATA.CSV cleared and recreated.\r\n");
}

void log_data(double v_rms, double i_rms, double phase, double total_units) {
	FATFS FatFs; 	//Fatfs handle
	FIL fil; 		//File handle
	FRESULT fres; //Result after operations
	UINT bytesWrote;
	fres = f_mount(&FatFs, "", 1);
	  if (fres != FR_OK) {
	      myprintf("f_mount error (%i)\r\n", fres);
	      while (1);
	  }

	    if (f_open(&fil, "DATA.csv", FA_WRITE | FA_OPEN_ALWAYS | FA_CREATE_ALWAYS) == FR_OK) {
		  	RTC_TimeTypeDef currentTime;
		  	RTC_DateTypeDef currentDate;
		  	HAL_RTC_GetTime(&hrtc, &currentTime, RTC_FORMAT_BIN);
		  	HAL_RTC_GetDate(&hrtc, &currentDate, RTC_FORMAT_BIN);

		  	char timestamp[32];
		  	snprintf(timestamp, sizeof(timestamp), "%04d/%02d/%02d %02d:%02d:%02d",
		  			2000 + currentDate.Year, currentDate.Month, currentDate.Date,
		  			currentTime.Hours, currentTime.Minutes, currentTime.Seconds);

		  	char line[70];
		  	snprintf(line, sizeof(line), "%s,%05.1f,%d,%05.3f,%07.3f\r\n", timestamp, v_rms, (int)i_rms * 1000, phase, total_units);

		  	fres = f_write(&fil, line, strlen(line), &bytesWrote);
		  	if (fres != FR_OK) {
		  		  		myprintf("f_write error (%i), wrote %u bytes\r\n", fres, bytesWrote);
		  		  	}
	    }
	    f_close(&fil);
	    f_mount(NULL, "", 0);
}

void read_data(TCHAR *readlogData) {
	FATFS FatFs; 	//Fatfs handle
	FIL fil; 		//File handle
	FRESULT fres; //Result after operations
	FRESULT *rres;
	fres = f_mount(&FatFs, "", 1);
	if (fres != FR_OK) {
		myprintf("f_mount error (%i)\r\n", fres);
		while (1);
	  }
	if (f_open(&fil, "DATA.csv", FA_READ) == FR_OK) {
		rres = f_gets(readlogData, 30, &fil);
		if(rres != 0) {
			myprintf("Read string from 'test.txt' contents: %s\r\n", readlogData);
		} else {
			myprintf("f_gets error (%i)\r\n", fres);
		}
	}

	f_close(&fil);
	f_mount(NULL, "", 0);
}


void log_data_uart(char *log_data, double Ipp, double Vpp, double apparent, double energy, double units, double v_rms, double i_rms, double phase, double real, double reactive, double pow_fact, double max_power, double min_units){
	sprintf(log_data, "%.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f\n", Ipp, Vpp, i_rms, v_rms, phase, apparent, real, reactive, pow_fact);
	HAL_UART_Transmit(&huart2, (uint8_t*)log_data, strlen(log_data), 2000);
}
