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

#include <stm32f10x.h>

#include "hal/interrupt/systick.hpp"

namespace hal
{
namespace interrupt
{
namespace
{
static std::chrono::milliseconds period(100);
static std::chrono::milliseconds ticks(0);
static SystickHandler callback = [](std::chrono::milliseconds){};
}

void set_systick_handler(const SystickHandler& handler)
{
    callback = handler;
}

void set_systick_period(const std::chrono::milliseconds& time)
{
    period = time;
    SysTick_Config(SystemCoreClock / time.count());
}

void set_systick_priority(uint8_t priority)
{
    NVIC_SetPriority(SysTick_IRQn, priority);
}

std::chrono::milliseconds get_ticks()
{
    return ticks;
}


} // namespace interrupt
} // namespace hal

extern "C"
{

void SysTick_Handler(void)
{
    hal::interrupt::ticks += hal::interrupt::period;
    hal::interrupt::callback(hal::interrupt::ticks);
}

}

