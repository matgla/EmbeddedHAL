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

#include <cstdio>

#include <stm32f10x.h>

#include "hal/interrupt/svc.hpp"

namespace hal
{
namespace interrupt
{
namespace
{
static SvcHandler callback = [](uint32_t, void*, void*){};
}

void set_svc_handler(const SvcHandler& handler)
{
    callback = handler;
}

void set_svc_priority(uint8_t priority)
{
    NVIC_SetPriority(SVCall_IRQn, priority);
}

} // namespace interrupt
} // namespace hal

extern "C"
{

void SVC_Handler(void)
{
    uint32_t number;
    void* arg;
    void* out;

    asm volatile("mov %0, r0" :"=r"(number));
    asm volatile("mov %0, r1" :"=r"(arg));
    asm volatile("mov %0, r2" :"=r"(out));

    hal::interrupt::callback(number, arg, out);
}

}

