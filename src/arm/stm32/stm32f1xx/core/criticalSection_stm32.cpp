#include "hal/core/criticalSection.hpp"

#include <stm32f10x.h>

#include <cstdio>


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

volatile uint32_t old;
volatile uint32_t counter = 0;

void startCriticalSection()
{
    old = NVIC->ISER[0];
    NVIC->ICER[0] = 0xffffffff;
    __disable_irq();
    counter++;
}

void stopCriticalSection()
{
    if (counter == 1)
    {
        NVIC->ISER[0] = old;
        __enable_irq();
    }

    if (counter > 0)
    {
        --counter;
    }
}

} // namespace core
} // namespace hal
