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

#pragma once

#include <chrono>
#include <cstdint>

#include <eul/function.hpp>

namespace hal
{
namespace interrupt
{

using SystickHandler = eul::function<void(std::chrono::milliseconds), 0>;
void set_systick_handler(const SystickHandler& handler);
void set_systick_priority(uint8_t priority);
void set_systick_period(std::chrono::milliseconds time);

std::chrono::milliseconds get_ticks();
void disable_systick();

void reset_ticks_counter();
void reset_systick_handler();

} // namespace interrupt
} // namespace hal

