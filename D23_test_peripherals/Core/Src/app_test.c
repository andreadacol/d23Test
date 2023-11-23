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
