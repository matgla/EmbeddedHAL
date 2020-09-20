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

#include <cstdint>

#include <eul/function.hpp>

namespace hal
{
namespace clock
{

class Clock
{
public:
    using OnCoreClockChangeCallback = eul::function<void(), 2 * sizeof(void*)>;
    static uint32_t get_core_clock();

    // TODO: add clock source
    static void set_core_clock(const uint32_t clock);

    static void set_core_clock_change_callback(const OnCoreClockChangeCallback& callback);

private:
    static OnCoreClockChangeCallback on_core_clock_change_callback_;
};

} // namespace clock
} // namespace hal
