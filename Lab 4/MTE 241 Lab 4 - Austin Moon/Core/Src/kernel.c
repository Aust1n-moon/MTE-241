#include "kernel.h"
#include "main.h"
#include <stdint.h>
#include <stdio.h>

thread threadArray[MAX_THREADS];
int numThreadsRunning = 0;   
int currentThread = 0;

void osSched(void)
{
	// PendSV pushed R4-R11 below PSP through R0 but didn't update PSP, so the frame starts 8 words lower
	threadArray[currentThread].sp = (uint32_t*)(__get_PSP() - 8*4);
	currentThread = (currentThread+1)%numThreadsRunning;
	__set_PSP((uint32_t)threadArray[currentThread].sp);
}

void SVC_Handler_Main( unsigned int *svc_args)
{
	unsigned int svc_number;

	svc_number = ((char *)svc_args[6])[-2];
	switch(svc_number)
	{
	case 1:
		printf("a\r\n");
		break;
	case 2:
		printf("b\r\n");
		break;
	case 17:
		printf("Success!\r\n");
		break;
	case 3:
        __set_PSP((uint32_t)threadArray[currentThread].sp);
        runFirstThread();
		break;
	case YIELD:
		//Pend an interrupt to do the context switch
		SCB->ICSR |=1<<28;
		__asm("isb");
		break;
	default:
		break;
	}
}

uint32_t LastStackTop;
uint32_t StackPoolEnd;

uint32_t* allocateStack(void)
{
    uint32_t StackTop = LastStackTop - STACK_SIZE;

    if (StackTop - STACK_SIZE < StackPoolEnd)
    {
        return NULL;
    }

    LastStackTop = StackTop;
    return (uint32_t*) StackTop;
}

int osCreateThread(void (*thread_fp)(void*))
{
	uint32_t* newstack = allocateStack();

	if (newstack == NULL)
	{
		return 0;
	}

	*(--newstack) = 1 << 24;
	*(--newstack) = (uint32_t)thread_fp;

	for (int i = 0; i<14; i++)
	{
    	*(--newstack) = 0xA;
	}

	threadArray[numThreadsRunning].sp = newstack;
	threadArray[numThreadsRunning].thread_function = thread_fp;
	numThreadsRunning++;
	return 1;
}

void osKernelInitialize(void)
{
	LastStackTop = *(uint32_t*)0x0;
	StackPoolEnd = LastStackTop - STACK_POOL_SIZE;
}

void osKernelStart(void)
{
	__asm("SVC #3");
}

void osYield(void)
{
	__asm("SVC #4");   
}