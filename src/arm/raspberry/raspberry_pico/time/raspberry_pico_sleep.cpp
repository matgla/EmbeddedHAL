// This file is part of msboot project.
// Copyright (C) 2021 Mateusz Stadnik
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

#include "hal/time/sleep.hpp"

#include "pico/stdlib.h"

namespace hal 
{
namespace time 
{

void sleep(std::chrono::microseconds time)
{
    sleep_us(time.count());
}

void sleep(std::chrono::milliseconds time) 
{
    sleep_ms(time.count());
}

} // namespace time
} // namespace hal

