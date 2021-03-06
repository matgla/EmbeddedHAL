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

#include "hal/interrupt/pendsv.hpp"

#include <cstdio>

#include <stm32f4xx.h>

namespace hal
{
namespace interrupt
{
namespace
{
static PendSvHandler callback = [](){};
}

void set_pendsv_handler(const PendSvHandler& handler)
{
    callback = handler;
}

void set_pendsv_priority(uint8_t priority)
{
    NVIC_SetPriority(PendSV_IRQn, priority);
}

void trigger_pendsv()
{
    SCB->ICSR = SCB->ICSR | SCB_ICSR_PENDSVSET_Msk;
}

} // namespace interrupt
} // namespace hal

extern "C"
{

void __attribute__((weak)) PendSV_Handler(void)
{
    if (hal::interrupt::callback)
    {
        hal::interrupt::callback();
    }
}

}

