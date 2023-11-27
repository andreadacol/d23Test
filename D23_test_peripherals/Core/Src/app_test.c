/*
 * app_peripheral_tests.c
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
 global vars
**************************************************************************/

/**************************************************************************
 functions
**************************************************************************/
void app_test_GPO_CN49_start (void) {

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
						  |GPIO_PIN_6, GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_6, GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
						  |GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
						  |GPIO_PIN_11, GPIO_PIN_SET);

}


void app_test_GPO_CN49_stop (void) {

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
						  |GPIO_PIN_6, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_6, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
						  |GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
						  |GPIO_PIN_11, GPIO_PIN_RESET);
}

uint32_t app_test_GPO_CN50_read (void) {

	uint8_t bitmask = 0;
	uint32_t newPinMask = 0;

    // Check if the specified time has elapsed since the last execution
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_9);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_0);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_1);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_8);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_9);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_10);	bitmask ++;

    return newPinMask;
}

void app_test_GPO_CN49_square(uint32_t time) {

    if (time == 0) {
        // Assign a default value if time is NULL
        time = 500;
    }

    static uint32_t lastExecutionTime = 0;
    uint32_t currentTime = HAL_GetTick();

    static uint8_t phase = 0;

    // Check if the specified time has elapsed since the last execution
    if ((currentTime - lastExecutionTime) >= time) {
        // Toggle the state
        if (phase) {
            app_test_GPO_CN49_start();
            phase = 0;
        } else {
            app_test_GPO_CN49_stop();
            phase = 1;
        }

        // Update the last execution time
        lastExecutionTime = currentTime;
    }
}

uint8_t app_test_GPO_CN50_square(uint32_t time) {

	static uint32_t pinMask = 0;
	uint8_t bitmask = 0;
	uint32_t newPinMask = 0;
	uint8_t ret = 0;

    if (time == 0) {
        // Assign a default value if time is NULL
        time = 500;
    }


    static uint32_t lastExecutionTime = 0;
    uint32_t currentTime = HAL_GetTick();
    if ((currentTime - lastExecutionTime) <= time) return 2;
    lastExecutionTime = currentTime;

    // Check if the specified time has elapsed since the last execution
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_9);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_0);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_1);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_8);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_9);	bitmask ++;
	newPinMask += bitmask * HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_10);	bitmask ++;

    if ((pinMask & newPinMask) == 0) {
    	ret = 1;
    } else {
    	printf("error on GPI, untoggled pin mask %d\n", !(pinMask & newPinMask));
    }

    pinMask = newPinMask;

    return ret;
}
