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
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart5;

extern TIM_HandleTypeDef  htim1;
extern TIM_HandleTypeDef  htim4;

extern SPI_HandleTypeDef  hspi1;
extern SPI_HandleTypeDef  hspi2;

extern I2C_HandleTypeDef  hi2c1;
extern I2C_HandleTypeDef  hi2c2;

app_test_typedef _test = {
	.gpo_cn49_square 	= false,
	.gpi_cn50_square 	= false,
	.uart_cn48 			= false,
	.uart_cn28 			= false,
	.uart1_cn32 		= false,
	.uart5_cn32 		= false,
	.spi_px30 			= false,
	.spi_cn39 			= false,
	.i2c1_cn33 			= false,
	.i2c2_cn33 			= false,
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

void app_test_UART_CN28_set (bool var) {
	_test.uart_cn28 = var;
}

void app_test_UART1_CN32_set (bool var) {
	_test.uart1_cn32 = var;
}

void app_test_UART5_CN32_set (bool var) {
	_test.uart5_cn32 = var;
}

void app_test_SPI_PX30_set (bool var) {
	_test.spi_px30 = var;
}

void app_test_SPI_CN39_set (bool var) {
	_test.spi_cn39 = var;
}

void app_test_I2C1_CN33_set (bool var) {
	_test.i2c1_cn33 = var;
}

void app_test_I2C2_CN33_set (bool var) {
	_test.i2c2_cn33 = var;
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
	uint8_t test[] = "Hello World!\r\n";
	uint8_t singleData = 0;

    if (time == 0) {
        // Assign a default value if time is NULL
        time = 500;
    }

    static uint32_t lastExecutionTime = 0;
    uint32_t currentTime = HAL_GetTick();
    if ((currentTime - lastExecutionTime) > time) {
		lastExecutionTime = currentTime;

		HAL_UART_Transmit(&huart3, test, sizeof(test), 0xFF );
    }
    else {
    	if (HAL_UART_Receive(&huart3, &singleData, 1, 1) == HAL_OK) {
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

uint8_t app_test_UART_CN28_test(uint32_t time) {

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

		HAL_UART_Transmit(&huart2, test, sizeof(test), 0xFF );
    }
    else {
    	if (HAL_UART_Receive(&huart2, &singleData, 1, 0xFF) == HAL_OK) {
    		if (singleData != 0) {
    			ret = 1;
    			printf("%d\n", singleData);
    		}
    	}
    }

    return ret;
}

uint8_t app_test_UART1_CN32_test(uint32_t time) {

	uint8_t ret = 0;
	uint8_t test[] = "Hello World!\r\n";
	uint8_t singleData = 0;

    if (time == 0) {
        // Assign a default value if time is NULL
        time = 500;
    }

    static uint32_t lastExecutionTime = 0;
    uint32_t currentTime = HAL_GetTick();
    if ((currentTime - lastExecutionTime) > time) {
		lastExecutionTime = currentTime;

		HAL_UART_Transmit(&huart1, test, sizeof(test), 0xFF );
    }
    else {
    	if (HAL_UART_Receive(&huart1, &singleData, 1, 0xFF) == HAL_OK) {
    		if (singleData != 0) {
    			ret = 1;
    			printf("%d\n", singleData);
    		}
    	}
    }

    return ret;
}

uint8_t app_test_UART5_CN32_test(uint32_t time) {

	uint8_t ret = 0;
	uint8_t test[] = "Hello World!\r\n";
	uint8_t singleData = 0;

    if (time == 0) {
        // Assign a default value if time is NULL
        time = 500;
    }

    static uint32_t lastExecutionTime = 0;
    uint32_t currentTime = HAL_GetTick();
    if ((currentTime - lastExecutionTime) > time) {
		lastExecutionTime = currentTime;

		HAL_UART_Transmit(&huart5, test, sizeof(test), 0xFF );
    }
    else {
    	if (HAL_UART_Receive(&huart5, &singleData, 1, 0xFF) == HAL_OK) {
    		if (singleData != 0) {
    			ret = 1;
    			printf("%d\n", singleData);
    		}
    	}
    }

    return ret;
}

uint8_t app_test_SPI_PX30_echo (void) {

	uint8_t ret = 0;

	uint8_t dataRcv[16] = {0};

	if ( HAL_SPI_Receive(&hspi1, dataRcv, sizeof(dataRcv), 1000) == HAL_OK ) {
		HAL_UART_Transmit(&huart1, (uint8_t*)"spi receive\r\n", 13, 0xFFFF);

		HAL_SPI_Transmit(&hspi1, dataRcv, sizeof(dataRcv), 1000);
	}

    return ret;
}

uint8_t app_test_SPI_CN39_echo (void) {

	uint8_t ret = 0;

	uint8_t dataRcv[16] = {0};
	uint8_t dataTrn[16];

	for (uint8_t ind = 0; ind < 16; ind++) {
		dataTrn[ind] = ind;
	}

//	HAL_UART_Transmit(&huart1, (uint8_t*)"spi receive\r\n", 13, 0xFFFF);
//
//	if(HAL_SPI_TransmitReceive(&hspi2, (uint8_t*)dataTrn, (uint8_t *)dataRcv, 16, 5000) == HAL_OK) {
//
//		if (memcmp(dataTrn, dataRcv, 16) == 0) {
////			HAL_UART_Transmit(&huart1, (uint8_t*)"spi receive\r\n", 13, 0xFFFF);
//		}
//
//	}
	/* USER CODE BEGIN PV */
	/* Buffer used for transmission */
	uint8_t aTxBuffer[] = "ciao";

	uint8_t BUFFERSIZE = sizeof(aTxBuffer)-1;

	/* Buffer used for reception */
	uint8_t aRxBuffer[BUFFERSIZE];

	for(uint8_t ind =0; ind< sizeof(aRxBuffer); ind ++)
		aRxBuffer[ind] = ind;

	 switch (HAL_SPI_TransmitReceive(&hspi1, (uint8_t *)aTxBuffer, (uint8_t *)aRxBuffer, BUFFERSIZE, 30000))
	  {
	    case HAL_OK:
	      /* Communication is completed ___________________________________________ */
	      /* Compare the sent and received buffers */
	      if (memcmp((uint8_t *)aTxBuffer, (uint8_t *)aRxBuffer, BUFFERSIZE))
	      {
	        /* Transfer error in transmission process */
	    	  dataRcv[0] = 0;
	      }
	      /* Turn LED1 on: Transfer in transmission process is correct */
	      break;

	    case HAL_TIMEOUT:
	      /* A Timeout Occur ______________________________________________________*/
	      /* Call Timeout Handler */
	      break;
	    /* An Error Occur ______________________________________________________ */
	    case HAL_ERROR:
	      /* Call Timeout Handler */
	      break;
	    default:
	      break;
	  }


	HAL_Delay(100);

    return ret;
}

uint8_t app_test_I2C1_CN33_echo (void) {

	uint8_t ret = 0;

	uint8_t dataRcv[16] = {0};
	uint8_t dataTrn[16];

	for (uint8_t ind = 0; ind < 16; ind++) {
		dataTrn[ind] = ind;
	}


	/*##-2- Start the transmission process #####################################*/
	/* While the I2C in reception process, user can transmit data through
	 "aTxBuffer" buffer */
	/* Timeout is set to 10S */
	while(HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)I2C_ADDRESS, (uint8_t*)dataTrn, 16, 1000)!= HAL_OK)
	{
		/* Error_Handler() function is called when Timeout error occurs.
		   When Acknowledge failure occurs (Slave don't acknowledge its address)
		   Master restarts communication */
		if (HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF)
		{
//			Error_Handler();
		}
	}

	  /*##-3- Put I2C peripheral in reception process ############################*/
	  /* Timeout is set to 10S */
	  while(HAL_I2C_Master_Receive(&hi2c1, (uint16_t)I2C_ADDRESS, (uint8_t *)dataRcv, 16, 10000) != HAL_OK)
	  {
	    /* Error_Handler() function is called when Timeout error occurs.
	       When Acknowledge failure occurs (Slave don't acknowledge it's address)
	       Master restarts communication */
	    if (HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF)
	    {
//	      Error_Handler();
	    }
	  }


//	/*##-2- Put I2C peripheral in reception process ############################*/
//	  /* Timeout is set to 10S  */
//	  if(HAL_I2C_Slave_Receive(&hi2c1, (uint8_t *)dataRcv, 16, 10000) != HAL_OK)
//	  {
//	    /* Transfer error in reception process */
////	    Error_Handler();
//	  }
//	  else {
//		  /*##-3- Start the transmission process #####################################*/
//		  /* While the I2C is in reception process, user can transmit data through
//		     "aTxBuffer" buffer */
//		  /* Timeout is set to 10S */
//		  if(HAL_I2C_Slave_Transmit(&hi2c1, (uint8_t*)dataRcv, 16, 10000)!= HAL_OK)
//		  {
//		    /* Transfer error in transmission process */
//	//	    Error_Handler();
//		  }
//	  }



	HAL_Delay(10);

    return ret;
}

uint8_t app_test_I2C2_CN33_echo (void) {

	uint8_t ret = 0;

	uint8_t dataRcv[16] = {0};
	uint8_t dataTrn[16];

	for (uint8_t ind = 0; ind < 16; ind++) {
		dataTrn[ind] = ind;
	}


	/*##-2- Start the transmission process #####################################*/
	/* While the I2C in reception process, user can transmit data through
	 "aTxBuffer" buffer */
	/* Timeout is set to 10S */
	while(HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)I2C_ADDRESS, (uint8_t*)dataTrn, 16, 10)!= HAL_OK)
	{
		/* Error_Handler() function is called when Timeout error occurs.
		   When Acknowledge failure occurs (Slave don't acknowledge its address)
		   Master restarts communication */
		if (HAL_I2C_GetError(&hi2c2) != HAL_I2C_ERROR_AF)
		{
//			Error_Handler();
		}
	}

	  /*##-3- Put I2C peripheral in reception process ############################*/
	  /* Timeout is set to 10S */
	  while(HAL_I2C_Master_Receive(&hi2c2, (uint16_t)I2C_ADDRESS, (uint8_t *)dataRcv, 16, 10000) != HAL_OK)
	  {
	    /* Error_Handler() function is called when Timeout error occurs.
	       When Acknowledge failure occurs (Slave don't acknowledge it's address)
	       Master restarts communication */
	    if (HAL_I2C_GetError(&hi2c2) != HAL_I2C_ERROR_AF)
	    {
//	      Error_Handler();
	    }
	  }

	HAL_Delay(10);

    return ret;
}

uint8_t app_test_USB_CN31_start(void) {
	uint8_t ret = 0;

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11 | GPIO_PIN_12, GPIO_PIN_SET);

	return ret;
}

uint8_t app_test_USB_CN31_stop(void) {
	uint8_t ret = 0;

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11 | GPIO_PIN_12, GPIO_PIN_RESET);

	return ret;
}

void app_test_manager_sm (void) {

	_test.spi_cn39 = true;

	if (_test.gpo_cn49_square) {
		app_test_GPO_CN49_square(0);
	}
	if (_test.gpi_cn50_square) {
		app_test_GPI_CN50_square(0);
	}
	if (_test.uart_cn48) {
		app_test_UART_CN48_test(0);
	}
	if (_test.uart_cn28) {
		app_test_UART_CN28_test(0);
	}
	if (_test.uart1_cn32) {
		app_test_UART1_CN32_test(0);
	}
	if (_test.uart5_cn32) {
		app_test_UART5_CN32_test(0);
	}
	if (_test.spi_px30) {
		app_test_SPI_PX30_echo();
	}
	if (_test.spi_px30) {
		app_test_SPI_PX30_echo();
	}
	if (_test.spi_cn39) {
		app_test_SPI_CN39_echo();
	}
	if (_test.i2c1_cn33) {
		app_test_I2C1_CN33_echo();
	}
	if (_test.i2c2_cn33) {
		app_test_I2C2_CN33_echo();
	}

//	HAL_UART_Transmit(&huart1, (uint8_t*)"_test variable", 14, 0xFFFF);
//	uint8_t print[10] = {0};
//	sprintf(print, "%d \r\n", (int)_test.spi_px30);
//	HAL_UART_Transmit(&huart1, print, 14, 0xFFFF);

}
