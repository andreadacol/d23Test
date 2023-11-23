/*
 * app_term_manager.c
 *
 *  Created on: Nov 22, 2023
 *      Author: andreadacol
 */
/**************************************************************************
 includes
**************************************************************************/
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

/**************************************************************************
 private functions
**************************************************************************/
bool _app_term_cmd () {
	bool ret = false;

    if ( memcmp(rcvData, CMD_HELP, sizeof(CMD_HELP)) == 0 ) {

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

	if( rcvDataPtr == NULL ) {
		rcvDataPtr = rcvData;
	}

	uint8_t singleData = 0;

	HAL_UART_Receive(&huart1, &singleData, 1, 0xFF);

	if ((singleData == 0x08) && (pos != 0)) {
		rcvDataPtr--;
		pos--;
		HAL_UART_Transmit(&huart1, (uint8_t*)"\b \b", 3, 0xFF);
	}
	else if ( singleData == 0x0D ) {
		rcvDataPtr++;
		*rcvDataPtr = '\0';

		_app_term_cmd(rcvData);

	    HAL_UART_Transmit(&huart1, (uint8_t*)"\r\n", 2, 0xFF);
	    rcvDataPtr = rcvData;
	    pos = 0;
	}
	else {
		if ( singleData != 0 ) {
			*rcvDataPtr = singleData;
			rcvDataPtr++;
			pos++;
			HAL_UART_Transmit(&huart1, &singleData, 1, 0xFF);
		}

	}

	//HAL_UART_Transmit(&huart1, &rcvData, 1, 0xFF);

}
