/*
 * app_peripheral_tests.h
 *
 *  Created on: Nov 22, 2023
 *      Author: andreadacol
 */

#ifndef SRC_APP_TEST_H_
#define SRC_APP_TEST_H_

/**************************************************************************
 include
**************************************************************************/
#include <main.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/**************************************************************************
 typedef
**************************************************************************/
typedef struct
{
	bool gpo_cn49_square;
	bool gpi_cn50_square;
	bool uart_cn48;
} app_test_typedef;

/**************************************************************************
 functions
**************************************************************************/
void 		app_test_GPO_CN49_set (bool var);
void 		app_test_GPI_CN50_set (bool var);
void 		app_test_UART_CN48_set (bool var);
void 		app_test_GPO_CN49_start (void);
void 		app_test_GPO_CN49_stop (void);
uint32_t 	app_test_GPI_CN50_read(void);
void 		app_test_GPO_CN49_square(uint32_t time);
uint8_t 	app_test_GPI_CN50_square(uint32_t time);
uint8_t 	app_test_UART_CN48_test(uint32_t time);

void 		app_test_manager_sm (void);


#endif /* SRC_APP_TEST_H_ */
