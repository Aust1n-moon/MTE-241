#ifndef __kernel_h
#define __kernel_h

#include <stdint.h>

#define STACK_SIZE 0x400
#define STACK_POOL_SIZE 0x4000
#define MAX_THREADS (STACK_POOL_SIZE / STACK_SIZE - 1)
#define YIELD 4

void SVC_Handler_Main(unsigned int *svc_args);
void runFirstThread(void);
uint32_t* allocateStack(void);

typedef struct k_thread{
    uint32_t* sp;
    void (*thread_function)(void*);
}thread;

int osCreateThread(void (*thread_fp)(void*));
void osKernelInitialize(void);
void osKernelStart(void);
void osYield(void);

#endif