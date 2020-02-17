#include "hal/core/criticalSection.hpp"

#include <stm32f10x.h>

#include <cstdio>

extern "C"
{
    void SVC_Handler();
}

volatile uint32_t old;
volatile uint32_t counter = 0;

void SVC_Handler()
{
    uint32_t number;
    asm volatile("mov %0, r0" :"=r"(number));
    if (number == 1)
    {
        printf("Disable interrupts!!!!!!!! %d\n", counter);
        old = NVIC->ISER[0];
        NVIC->ICER[0] = 0xffffffff;
        __disable_irq();
        __disable_fault_irq();
        ++counter;
    }
    else if (number == 2 && counter != 1)
    {
        --counter;
    }
    else if (number == 2 && counter == 1)
    {
        printf("Enable interrupts!!!!!!!! %d\n", counter);
        NVIC->ISER[0] = old;
        __enable_irq();
        __enable_fault_irq();
        --counter;
    }
}

namespace hal
{
namespace core
{

static inline uint32_t get_PRIMASK()
{
    uint32_t mask;
    asm inline volatile(
        "mrs %0, primask\n" : "=r"(mask));
    return mask;
}

void startCriticalSection()
{
    asm volatile inline("mov r0, %0" ::"r"(1));
    asm volatile inline("svc 0");
    asm volatile inline("isb");
}

void stopCriticalSection()
{
    asm volatile inline("mov r0, %0" ::"r"(2));
    asm volatile inline("svc 0");
    asm volatile inline("isb");
}

} // namespace core
} // namespace hal
