
#include "hal/time/time.hpp"

#include "hal/interrupt/systick.hpp"

#include <stm32f4xx.h>

#include <stm32f401ceu6_usart.hpp>
// #include <eul/utils/string.hpp>


namespace hal
{
namespace time
{

static auto& usart = hal::interfaces::USART_1();

volatile unsigned int *DWT_CYCCNT   = (volatile unsigned int *)0xE0001004;
volatile unsigned int *DWT_CONTROL  = (volatile unsigned int *)0xE0001000;
volatile unsigned int *SCB_DEMCR    = (volatile unsigned int *)0xE000EDFC;

void initialize_dwt_counter(void)
{
    *SCB_DEMCR = *SCB_DEMCR | 0x01000000;
    *DWT_CYCCNT = 0;
    *DWT_CONTROL = *DWT_CONTROL | 1;
}


void Time::init()
{
#ifdef STM32_MICROSECONDS_COUNTER
    initialize_dwt_counter();
#endif
}

std::chrono::milliseconds Time::milliseconds()
{
    return interrupt::get_ticks();
}

std::chrono::microseconds Time::microseconds()
{
    #ifdef STM32_MICROSECONDS_COUNTER

        return std::chrono::microseconds(interrupt::get_ticks().count() * 1000 + (*DWT_CYCCNT / (SystemCoreClock/1000000)));
    #endif
    return std::chrono::microseconds{0};
}

void sleep(std::chrono::microseconds time)
{
    auto previous = Time::microseconds();
    auto counter = previous;
    while (counter < time + previous)
    {
        counter = Time::microseconds();
    }
}

void sleep(std::chrono::milliseconds time)
{
    auto previous = Time::milliseconds();

    auto counter = previous;

    while (counter < time + previous)
    {
        counter = Time::milliseconds();
    }
}

void sleep(std::chrono::seconds time)
{
    sleep(std::chrono::duration_cast<std::chrono::milliseconds>(time));
}

} // namespace time
} // namespace hal




