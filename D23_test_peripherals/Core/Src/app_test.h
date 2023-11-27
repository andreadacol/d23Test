/*
 * app_peripheral_tests.h
 *
 *  Created on: Nov 22, 2023
 *      Author: andreadacol
 */

#ifndef SRC_APP_TEST_H_
#define SRC_APP_TEST_H_

#include <main.h>
/**************************************************************************
 functions
**************************************************************************/

void app_test_GPO_CN49_start (void);
void app_test_GPO_CN49_stop (void);
uint32_t app_test_GPO_CN50_read(void);
void app_test_GPO_CN49_square(uint32_t time);
uint8_t app_test_GPO_CN50_square(uint32_t time);



#endif /* SRC_APP_TEST_H_ */
