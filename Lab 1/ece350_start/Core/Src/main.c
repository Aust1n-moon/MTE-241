/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h> //You are permitted to use this library, but currently only printf is implemented. Anything else is up to you!

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* MCU Configuration: Don't change this or the whole chip won't work!*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* MCU Configuration is now complete. Start writing your code below this line */
  uint32_t* MSP_INIT_VAL = *(uint32_t**)0x0;
  printf("MSP Init is: %p\r\n", MSP_INIT_VAL);
  uint32_t PSP_val = (uint32_t)MSP_INIT_VAL - 0x400;

  __set_PSP(PSP_val);
  __set_CONTROL(0x02);

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	//addr_stack_j = msp_init_val - main_stack_size - (j-1)thread_stack_size
	//MSP_INIT_VAL = 0x20018000
	//PSP_val = 0x20017c00

	//

	//register msp = 0x20017ff0
  }
  /* USER CODE END 3 */
}

