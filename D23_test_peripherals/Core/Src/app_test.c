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
extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim4;

app_test_typedef _test = {
	.gpo_cn49_square = false,
	.gpi_cn50_square = false,

};
/**************************************************************************
 functions
**************************************************************************/
void app_test_GPO_CN49_set (bool var) {
	_test.gpo_cn49_square = var;
}

void app_test_GPI_CN50_set (bool var) {
	_test.gpi_cn50_square = var;
}

void app_test_UART_CN48_set (bool var) {
	_test.uart_cn48 = var;
}

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

uint32_t app_test_GPI_CN50_read (void) {

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

uint8_t app_test_GPI_CN50_square(uint32_t time) {

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

uint8_t app_test_UART_CN48_test(uint32_t time) {

	uint8_t ret = 0;
	uint8_t test[] = "Hello World!";
	uint8_t singleData = 0;

    if (time == 0) {
        // Assign a default value if time is NULL
        time = 500;
    }

    static uint32_t lastExecutionTime = 0;
    uint32_t currentTime = HAL_GetTick();
    if ((currentTime - lastExecutionTime) > time) {
		lastExecutionTime = currentTime;

		HAL_UART_Transmit(&huart3, test, sizeof(test), 0xFFFF );
    }
    else {
    	if (HAL_UART_Receive(&huart3, &singleData, 1, 0xFF) == HAL_OK) {
    		if (singleData != 0) {
    			ret = 1;
    			printf("%d\n", singleData);
    		}
    	}
    }

    return ret;
}

uint8_t app_test_TIM_CN34_start(void) {
	uint8_t ret = 0;

	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);

	return ret;
}

uint8_t app_test_TIM_CN34_stop(void) {
	uint8_t ret = 0;

	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_4);

	return ret;
}

void app_test_manager_sm (void) {

	if (_test.gpo_cn49_square) {
		app_test_GPO_CN49_square(0);
	}
	if (_test.gpi_cn50_square) {
		app_test_GPI_CN50_square(0);
	}
	if (_test.uart_cn48) {
		app_test_UART_CN48_test(0);
	}

}
