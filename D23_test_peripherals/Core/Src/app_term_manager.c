/*
 * app_term_manager.c
 *
 *  Created on: Nov 22, 2023
 *      Author: andreadacol
 */
/**************************************************************************
 includes
**************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "app_test.h"
#include "main.h"

/**************************************************************************
 defines
**************************************************************************/
#define MAX_LEN 30

#define CMD_START 	"start"
#define CMD_STOP  	"stop"

#define CMD_HELP 	"help"
#define CMD_GPO 	"gpo"


#define CHAR_BACKSPACE  0x08
#define CHAR_RETURN		0x0D
#define CHAR_SPACE		0x20

/**************************************************************************
 typedef
**************************************************************************/
typedef enum {
	APP_TERM_COMMAND_NONE = 0x00,
	APP_TERM_COMMAND_GPO_CN49,
	APP_TERM_COMMAND_GPI_CN50,

} app_term_command_enum_t;


/**************************************************************************
 global vars
**************************************************************************/
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart5;

/**************************************************************************
 private functions - send functions
**************************************************************************/
static void _send_header (void) {
	uint8_t header[3] = ">: ";
	HAL_UART_Transmit(&huart1, header, 3, 0xFFFF);
}

static void _send_new_line (void) {
	HAL_UART_Transmit(&huart1, (uint8_t*)"\r\n", 2, 0xFFFF);
}

static void _send_data (uint8_t * data, uint16_t size ) {
	HAL_UART_Transmit(&huart1, data, size, 0xFFFF);
}

/**************************************************************************
 private functions - cmd description
**************************************************************************/
static void _usages_cmd (void) {

	uint8_t cmd0[] = "Commands: \r\n";
	uint8_t cmd1[] = "	gpo		enable-disable all output gpios (gpo start stop) \r\n";
	uint8_t cmd2[] = "	gpi		read current state of all input gpios \r\n";

	_send_data(cmd0, sizeof(cmd0));
	_send_data(cmd1, sizeof(cmd1));
	_send_data(cmd2, sizeof(cmd2));
	_send_new_line();
}

static bool _gpo_cmd (uint8_t *data) {
	bool ret = false;
	uint8_t cnt = 0;

	do {
		if ( data[sizeof(CMD_GPO)-1+cnt] != CHAR_SPACE ) {
			break;
		}
		cnt++;
	} while (cnt < 30);


	// check for commands:
	if (cnt != 0) {
		if (memcmp(&data[sizeof(CMD_GPO)-1+cnt], CMD_START, sizeof(CMD_START)-1) == 0) {
			app_test_GPO_CN49_start();
			ret = true;
		}
		else if (memcmp(&data[sizeof(CMD_GPO)-1+cnt], CMD_STOP, sizeof(CMD_STOP)-1) == 0) {
			app_test_GPO_CN49_stop();
			ret = true;
		}
	}

	return ret;
}

/**************************************************************************
 private functions - command manager
**************************************************************************/
static bool _app_term_cmd (uint8_t * data) {
	bool ret = false;
	_send_new_line();

    if ( memcmp(data, CMD_HELP, sizeof(CMD_HELP)-1) == 0 ) {
    	_usages_cmd();
    	ret = true;
    }
    else if ( memcmp(data, CMD_GPO, sizeof(CMD_GPO)-1) == 0  ) {
    	ret = _gpo_cmd(data);
    }


	if (!ret) {
		if (data[0] != 0x00) {
			_send_data((uint8_t*)"Unknown command! \r\n", 17);
			_send_new_line();
		}
		_send_header();
	}

	return ret;
}

/**************************************************************************
 functions
**************************************************************************/
void app_term_manager_state_machine (void) {

	static uint8_t pos = 0;
	static uint8_t rcvData[MAX_LEN];
	static uint8_t * rcvDataPtr = NULL;

	static bool first_time = true;

	uint8_t singleData = 0;

	if (rcvDataPtr == NULL) {
		rcvDataPtr = rcvData;
	}

	if (first_time) {
		_send_data((uint8_t*)"\r\nD23 -- TEST STM32\r\n", 22);
		_send_header();
		first_time = false;
	}

	// checking received data from terminal
	HAL_UART_Receive(&huart1, &singleData, 1, 0xFF);

	// backspace command received
	if ((singleData == CHAR_BACKSPACE) && (pos != 0)) {

		_send_data((uint8_t*)"\b \b", 3);

		rcvDataPtr--;
		pos--;
	}
	else if ( singleData == CHAR_RETURN ) {
		rcvDataPtr++;
		*rcvDataPtr = '\0';

		// parsing received command
		_app_term_cmd(rcvData);

	    rcvDataPtr = rcvData;
	    pos = 0;
	    memset(rcvData, 0x00, sizeof(rcvData));
	}
	else {
		if ( singleData != 0 ) {
			*rcvDataPtr = singleData;

			// print back received character on terminal
			_send_data(&singleData, 1);

			rcvDataPtr++;
			pos++;
		}

	}

}
