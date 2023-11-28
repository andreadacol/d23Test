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
#include "app_term_manager.h"

/**************************************************************************
 defines
**************************************************************************/
#define MAX_LEN 			30

#define CMD_START 	 		"start"
#define CMD_STOP  	 		"stop"

#define CMD_READ 			"read"

#define CMD_HELP 		 	"help"
#define CMD_GPO_CN49 	 	"gpo"
#define CMD_GPI_CN50 	 	"gpi"
#define CMD_GPO_CN49_SQUARE	"gpo_square"
#define CMD_GPI_CN50_SQUARE	"gpi_square"
#define CMD_UART_CN48		"serialCN48"
#define CMD_TIM_CN34		"timerCN48"
#define CMD_UART_CN28		"mdbCN28"
#define CMD_UART1_CN32		"usart1CN32"
#define CMD_UART5_CN32		"usart5CN32"

#define CHAR_BACKSPACE  	0x08
#define CHAR_RETURN			0x0D
#define CHAR_SPACE			0x20

/**************************************************************************
 typedef
**************************************************************************/

/**************************************************************************
 global vars
**************************************************************************/
extern UART_HandleTypeDef huart1;

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
	uint8_t cmd1[] = "	gpo			enable-disable all output gpios (gpo start stop) \r\n";
	uint8_t cmd2[] = "	gpi			read current state of all input gpios \r\n";
	uint8_t cmd3[] = "	gpo_square	enable-disable square output at 1 Hz (gpo_square start stop)\r\n";
	uint8_t cmd4[] = "	gpi_square	read current state of all input gpios at 1 Hz (gpi_square start stop) \r\n";
	uint8_t cmd5[] = "	serialCN48	start stop  \r\n";
	uint8_t cmd6[] = "	mdbCN28		start stop  \r\n";
	uint8_t cmd7[] = "	usart1CN32	start stop  \r\n";
	uint8_t cmd8[] = "	usart5CN32	start stop  \r\n";
	uint8_t cmd9[] = "	timerCN34	start stop  \r\n";

	_send_data(cmd0, sizeof(cmd0));
	_send_data(cmd1, sizeof(cmd1));
	_send_data(cmd2, sizeof(cmd2));
	_send_data(cmd3, sizeof(cmd3));
	_send_data(cmd4, sizeof(cmd4));
	_send_data(cmd5, sizeof(cmd5));
	_send_data(cmd6, sizeof(cmd6));
	_send_data(cmd7, sizeof(cmd7));
	_send_data(cmd8, sizeof(cmd8));
	_send_data(cmd9, sizeof(cmd9));
	_send_new_line();
	_send_header();
}

static bool _gpo_cmd (uint8_t *data) {
	bool ret = false;
	uint8_t cnt = 0;

	uint8_t start_msg[] = "GPO start command received: all gpos are enabled \r\n";
	uint8_t stop_msg[] = "GPO start command received: all gpos are stopped \r\n";

	do {
		if ( data[sizeof(CMD_GPO_CN49)-1+cnt] != CHAR_SPACE ) {
			break;
		}
		cnt++;
	} while (cnt < 30);

	// check for commands:
	if (cnt != 0) {
		if (memcmp(&data[sizeof(CMD_GPO_CN49)-1+cnt], CMD_START, sizeof(CMD_START)-1) == 0) {
			app_test_GPO_CN49_start();
			_send_data(start_msg, sizeof(start_msg));
			_send_header();
			ret = true;
		}
		else if (memcmp(&data[sizeof(CMD_GPO_CN49)-1+cnt], CMD_STOP, sizeof(CMD_STOP)-1) == 0) {
			app_test_GPO_CN49_stop();
			_send_data(stop_msg, sizeof(stop_msg));
			_send_header();
			ret = true;
		}
	}

	return ret;
}

static bool _gpi_cmd (uint8_t *data) {
	bool ret = false;
	uint8_t cnt = 0;
	uint32_t pinMask = 0;

	uint8_t read_msg[30] = {0};

	do {
		if ( data[sizeof(CMD_GPI_CN50)-1+cnt] != CHAR_SPACE ) {
			break;
		}
		cnt++;
	} while (cnt < 30);


	// check for commands:
	if (cnt != 0) {
		if (memcmp(&data[sizeof(CMD_GPI_CN50)-1+cnt], CMD_READ, sizeof(CMD_READ)-1) == 0) {
			pinMask = app_test_GPI_CN50_read();
			sprintf((char *)read_msg, "GPI read mask: %d", (int)pinMask);
			_send_data(read_msg, sizeof(read_msg));
			_send_new_line();
			_send_header();
			ret = true;
		}
	}

	return ret;
}

static bool _gpo_square_cmd (uint8_t *data) {
	bool ret = false;
	uint8_t cnt = 0;

	uint8_t enable_msg[] = "GPO square test enabled \r\n";
	uint8_t disable_msg[] = "GPO square test disabled \r\n";

	do {
		if ( data[sizeof(CMD_GPO_CN49_SQUARE)-1+cnt] != CHAR_SPACE ) {
			break;
		}
		cnt++;
	} while (cnt < 30);

	// check for commands:
	if (cnt != 0) {
		if (memcmp(&data[sizeof(CMD_GPO_CN49_SQUARE)-1+cnt], CMD_START, sizeof(CMD_START)-1) == 0) {
			app_test_GPO_CN49_set(true);
			_send_data(enable_msg, sizeof(enable_msg));
			_send_header();
			ret = true;
		}
		else if (memcmp(&data[sizeof(CMD_GPO_CN49_SQUARE)-1+cnt], CMD_STOP, sizeof(CMD_STOP)-1) == 0) {
			app_test_GPO_CN49_set(false);
			_send_data(disable_msg, sizeof(disable_msg));
			_send_header();
			ret = true;
		}
	}

	return ret;
}

static bool _gpi_square_cmd (uint8_t *data) {
	bool ret = false;
	uint8_t cnt = 0;

	uint8_t enable_msg[] = "GPI square test enabled \r\n";
	uint8_t disable_msg[] = "GPI square test disabled \r\n";

	do {
		if ( data[sizeof(CMD_GPI_CN50_SQUARE)-1+cnt] != CHAR_SPACE ) {
			break;
		}
		cnt++;
	} while (cnt < 30);

	// check for commands:
	if (cnt != 0) {
		if (memcmp(&data[sizeof(CMD_GPI_CN50_SQUARE)-1+cnt], CMD_START, sizeof(CMD_START)-1) == 0) {
			app_test_GPI_CN50_set(true);
			_send_data(enable_msg, sizeof(enable_msg));
			_send_header();
			ret = true;
		}
		else if (memcmp(&data[sizeof(CMD_GPI_CN50_SQUARE)-1+cnt], CMD_STOP, sizeof(CMD_STOP)-1) == 0) {
			app_test_GPI_CN50_set(false);
			_send_data(disable_msg, sizeof(disable_msg));
			_send_header();
			ret = true;
		}
	}

	return ret;
}

static bool _uart_cn48_cmd (uint8_t *data) {
	bool ret = false;
	uint8_t cnt = 0;

	uint8_t enable_msg[] = "SERIAL CN48 test enabled \r\n";
	uint8_t disable_msg[] = "SERIAL CN48  test disabled \r\n";

	do {
		if ( data[sizeof(CMD_UART_CN48)-1+cnt] != CHAR_SPACE ) {
			break;
		}
		cnt++;
	} while (cnt < 30);

	// check for commands:
	if (cnt != 0) {
		if (memcmp(&data[sizeof(CMD_UART_CN48)-1+cnt], CMD_START, sizeof(CMD_START)-1) == 0) {
			app_test_UART_CN48_set(true);
			_send_data(enable_msg, sizeof(enable_msg));
			_send_header();
			ret = true;
		}
		else if (memcmp(&data[sizeof(CMD_UART_CN48)-1+cnt], CMD_STOP, sizeof(CMD_STOP)-1) == 0) {
			app_test_UART_CN48_set(false);
			_send_data(disable_msg, sizeof(disable_msg));
			_send_header();
			ret = true;
		}
	}

	return ret;
}

static bool _uart_cn28_cmd (uint8_t *data) {
	bool ret = false;
	uint8_t cnt = 0;

	uint8_t enable_msg[] = "MDB CN28 test enabled \r\n";
	uint8_t disable_msg[] = "MDB CN28  test disabled \r\n";

	do {
		if ( data[sizeof(CMD_UART_CN28)-1+cnt] != CHAR_SPACE ) {
			break;
		}
		cnt++;
	} while (cnt < 30);

	// check for commands:
	if (cnt != 0) {
		if (memcmp(&data[sizeof(CMD_UART_CN28)-1+cnt], CMD_START, sizeof(CMD_START)-1) == 0) {
			app_test_UART_CN28_set(true);
			_send_data(enable_msg, sizeof(enable_msg));
			_send_header();
			ret = true;
		}
		else if (memcmp(&data[sizeof(CMD_UART_CN28)-1+cnt], CMD_STOP, sizeof(CMD_STOP)-1) == 0) {
			app_test_UART_CN28_set(false);
			_send_data(disable_msg, sizeof(disable_msg));
			_send_header();
			ret = true;
		}
	}

	return ret;
}

static bool _uart1_cn32_cmd (uint8_t *data) {
	bool ret = false;
	uint8_t cnt = 0;

	uint8_t enable_msg[] = "USART1 CN32 test enabled \r\n";
	uint8_t disable_msg[] = "USART1 CN32  test disabled \r\n";

	do {
		if ( data[sizeof(CMD_UART1_CN32)-1+cnt] != CHAR_SPACE ) {
			break;
		}
		cnt++;
	} while (cnt < 30);

	// check for commands:
	if (cnt != 0) {
		if (memcmp(&data[sizeof(CMD_UART1_CN32)-1+cnt], CMD_START, sizeof(CMD_START)-1) == 0) {
			app_test_UART1_CN32_set(true);
			_send_data(enable_msg, sizeof(enable_msg));
			_send_header();
			ret = true;
		}
		else if (memcmp(&data[sizeof(CMD_UART1_CN32)-1+cnt], CMD_STOP, sizeof(CMD_STOP)-1) == 0) {
			app_test_UART1_CN32_set(false);
			_send_data(disable_msg, sizeof(disable_msg));
			_send_header();
			ret = true;
		}
	}

	return ret;
}

static bool _uart5_cn32_cmd (uint8_t *data) {
	bool ret = false;
	uint8_t cnt = 0;

	uint8_t enable_msg[] = "USART5 CN32 test enabled \r\n";
	uint8_t disable_msg[] = "USART5 CN32  test disabled \r\n";

	do {
		if ( data[sizeof(CMD_UART5_CN32)-1+cnt] != CHAR_SPACE ) {
			break;
		}
		cnt++;
	} while (cnt < 30);

	// check for commands:
	if (cnt != 0) {
		if (memcmp(&data[sizeof(CMD_UART1_CN32)-1+cnt], CMD_START, sizeof(CMD_START)-1) == 0) {
			app_test_UART1_CN32_set(true);
			_send_data(enable_msg, sizeof(enable_msg));
			_send_header();
			ret = true;
		}
		else if (memcmp(&data[sizeof(CMD_UART1_CN32)-1+cnt], CMD_STOP, sizeof(CMD_STOP)-1) == 0) {
			app_test_UART1_CN32_set(false);
			_send_data(disable_msg, sizeof(disable_msg));
			_send_header();
			ret = true;
		}
	}

	return ret;
}

static bool _tim_cn34_cmd (uint8_t *data) {
	bool ret = false;
	uint8_t cnt = 0;

	uint8_t enable_msg[] = "TIMER CN34 test enabled \r\n";
	uint8_t disable_msg[] = "TIMER CN34  test disabled \r\n";

	do {
		if ( data[sizeof(CMD_TIM_CN34)-1+cnt] != CHAR_SPACE ) {
			break;
		}
		cnt++;
	} while (cnt < 30);

	// check for commands:
	if (cnt != 0) {
		if (memcmp(&data[sizeof(CMD_TIM_CN34)-1+cnt], CMD_START, sizeof(CMD_START)-1) == 0) {
			app_test_GPI_CN50_set(true);
			_send_data(enable_msg, sizeof(enable_msg));
			_send_header();
			ret = true;
		}
		else if (memcmp(&data[sizeof(CMD_UART_CN48)-1+cnt], CMD_STOP, sizeof(CMD_STOP)-1) == 0) {
			app_test_GPI_CN50_set(false);
			_send_data(disable_msg, sizeof(disable_msg));
			_send_header();
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
    else if ( memcmp(data, CMD_GPO_CN49, sizeof(CMD_GPO_CN49)-1) == 0  ) {
    	ret = _gpo_cmd(data);
    }
    else if ( memcmp(data, CMD_GPI_CN50, sizeof(CMD_GPI_CN50)-1) == 0  ) {
    	ret = _gpi_cmd(data);
    }
    else if ( memcmp(data, CMD_GPO_CN49_SQUARE, sizeof(CMD_GPO_CN49_SQUARE)-1) == 0  ) {
    	ret = _gpo_square_cmd(data);
    }
    else if ( memcmp(data, CMD_GPI_CN50_SQUARE, sizeof(CMD_GPI_CN50_SQUARE)-1) == 0  ) {
    	ret = _gpi_square_cmd(data);
    }
    else if ( memcmp(data, CMD_UART_CN48, sizeof(CMD_UART_CN48)-1) == 0  ) {
    	ret = _uart_cn48_cmd(data);
    }
    else if ( memcmp(data, CMD_UART_CN28, sizeof(CMD_UART_CN28)-1) == 0  ) {
    	ret = _uart_cn28_cmd(data);
    }
    else if ( memcmp(data, CMD_UART1_CN32, sizeof(CMD_UART1_CN32)-1) == 0  ) {
    	ret = _uart1_cn32_cmd(data);
    }
    else if ( memcmp(data, CMD_UART5_CN32, sizeof(CMD_UART5_CN32)-1) == 0  ) {
    	ret = _uart5_cn32_cmd(data);
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
void app_term_manager_sm (void) {

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
