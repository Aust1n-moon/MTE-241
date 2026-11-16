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
#include "kernel.h"

/**
  * @brief  The application entry point.
  * @retval int
  */

void jumpAssembly(void* fcn)
{
	__asm("MOV PC, R0");
}

void print_continuously(void* args)
{
	while (1)
	{
		printf("Thread 1\r\n");
    osYield();
	}
}

void print_again(void* args)
{
  while(1)
  {
    printf("Thread 2\r\n");
    osYield();
  }
}

void print_success(void)
{
	__asm("SVC #17");
}

void print_a(void)
{
	__asm("SVC #1");
}

void print_b(void)
{
	__asm("SVC #2");
}


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

//  jumpAssembly((void*)print_continuously);
  print_success();
  print_a();
  print_b();

  // uint32_t* MSP_INIT_VAL = *(uint32_t**)0x0;
  // stackptr = (uint32_t*)((uint32_t)MSP_INIT_VAL - 0x400);

  // *(--stackptr) = 1 << 24;
  // *(--stackptr) = (uint32_t)print_continuously;
  // for (int i = 0; i<14; i++)
  // {
	//   *(--stackptr) = 0xA;
  // }

  // __asm("SVC #3");

  osKernelInitialize();
  osCreateThread(print_continuously);
  osCreateThread(print_again);
  osKernelStart();
  

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
//	  printf("Hello, world!\r\n");

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

