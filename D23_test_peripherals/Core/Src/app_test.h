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
 defines
**************************************************************************/
#define I2C_ADDRESS        0x30F

/**************************************************************************
 typedef
**************************************************************************/
typedef struct {
	bool gpo_cn49_square;
	bool gpi_cn50_square;
	bool uart_cn48;
	bool uart_cn28;
	bool uart1_cn32;
	bool uart5_cn32;
	bool spi_px30;
	bool spi_cn39;
	bool i2c1_cn33;
	bool i2c2_cn33;
} app_test_typedef;

/**************************************************************************
 functions
**************************************************************************/
void 		app_test_GPO_CN49_set (bool var);
void 		app_test_GPI_CN50_set (bool var);
void 		app_test_UART_CN48_set (bool var);
void 		app_test_UART_CN28_set (bool var);
void 		app_test_UART1_CN32_set (bool var);
void 		app_test_UART5_CN32_set (bool var);
void 		app_test_SPI_PX30_set (bool var);
void 		app_test_SPI_CN39_set (bool var);
void 		app_test_I2C1_CN33_set (bool var);
void 		app_test_I2C2_CN33_set (bool var);

void 		app_test_GPO_CN49_start (void);
void 		app_test_GPO_CN49_stop (void);
uint32_t 	app_test_GPI_CN50_read(void);
void 		app_test_GPO_CN49_square(uint32_t time);
uint8_t 	app_test_GPI_CN50_square(uint32_t time);
uint8_t 	app_test_UART_CN48_test(uint32_t time);
uint8_t		app_test_TIM_CN34_start(void);
uint8_t		app_test_TIM_CN34_stop(void);
uint8_t 	app_test_UART_CN28_test(uint32_t time);
uint8_t 	app_test_UART1_CN32_test(uint32_t time);
uint8_t 	app_test_UART5_CN32_test(uint32_t time);
uint8_t 	app_test_SPI_PX30_echo (void);
uint8_t 	app_test_SPI_CN39_echo (void);
uint8_t 	app_test_I2C1_CN33_echo (void);
uint8_t 	app_test_I2C2_CN33_echo (void);
uint8_t 	app_test_USB_CN31_start(void);
uint8_t 	app_test_USB_CN31_stop(void);

void 		app_test_manager_sm (void);


#endif /* SRC_APP_TEST_H_ */
