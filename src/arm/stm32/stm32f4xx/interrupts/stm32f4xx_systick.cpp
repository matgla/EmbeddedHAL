// This file is part of Embedded HAL project.
// Copyright (C) 2020 Mateusz Stadnik
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <chrono>

#include <stm32f4xx.h>
#include <cstdio>

#include "hal/interrupt/systick.hpp"

#include <stm32f401ceu6_usart.hpp>
#include <eul/utils/string.hpp>


namespace hal
{
namespace interrupt
{
namespace
{

static std::chrono::milliseconds period(100);
static std::chrono::milliseconds ticks(0);

static SystickHandler callback = [](std::chrono::milliseconds){};

static auto& usart = hal::interfaces::USART_1();
}

void reset_ticks_counter()
{
    ticks = std::chrono::milliseconds(0);
}

void reset_systick_handler()
{
    callback = [](std::chrono::milliseconds){};
}

void set_systick_handler(const SystickHandler& handler)
{
    callback = handler;
}

void set_systick_period(std::chrono::milliseconds time)
{
    period = time;
    SysTick_Config(SystemCoreClock / (1000 / time.count()));

    char data[100];
    eul::utils::itoa(SystemCoreClock, data);
    usart.write("Set systick period: ");
    usart.write(data);
    usart.write("\n");
}

void set_systick_priority(uint8_t priority)
{
    NVIC_SetPriority(SysTick_IRQn, priority);
}

std::chrono::milliseconds get_ticks()
{
    return ticks;
}

void disable_systick()
{
    SysTick->CTRL = SysTick->CTRL & ~(SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk);
}


} // namespace interrupt
} // namespace hal

extern "C"
{

void SysTick_Handler(void)
{
    #ifdef STM32_MICROSECONDS_COUNTER
    volatile unsigned int *DWT_CYCCNT   = (volatile unsigned int *)0xE0001004;
    uint32_t dwt_backup =  *DWT_CYCCNT;
    #endif
    hal::interrupt::ticks += hal::interrupt::period;
    hal::interrupt::callback(hal::interrupt::ticks);
    #ifdef STM32_MICROSECONDS_COUNTER
    *DWT_CYCCNT = (*DWT_CYCCNT) - dwt_backup;
    #endif
}

}
