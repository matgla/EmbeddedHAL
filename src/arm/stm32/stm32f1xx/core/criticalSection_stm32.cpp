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
