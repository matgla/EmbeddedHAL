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


#include "arm/stm32/stm32f4xx/clock/stm32f4xx_clock.hpp"

#include <eul/function.hpp>
#include <eul/utils/unused.hpp>
#include <stm32f4xx.h>

namespace hal
{
namespace clock
{

Clock::OnCoreClockChangeCallback Clock::on_core_clock_change_callback_ = []() {};


uint32_t Clock::get_core_clock()
{
    return SystemCoreClock;
}

void Clock::set_core_clock(const uint32_t clock)
{
    UNUSED1(clock);
    on_core_clock_change_callback_();
}

void Clock::set_core_clock_change_callback(const OnCoreClockChangeCallback& callback)
{
    on_core_clock_change_callback_ = callback;
}


} // namespace clock
} // namespace hal
