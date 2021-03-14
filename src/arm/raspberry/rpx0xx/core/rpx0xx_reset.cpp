// This file is part of embeddedHAL project.
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

#include "arm/raspberry/rpx0xx/core/rpx0xx_reset.hpp"

#include <hardware/structs/resets.h>

#include "arm/raspberry/rpx0xx/core/rpx0xx_register_manipulator.hpp"

namespace hal 
{
namespace core 
{

void reset_on(uint32_t mask)
{
    AtomicRegister resets(&resets_hw->reset);
    resets.set_bits(mask);
}

void reset_off(uint32_t mask)
{
    AtomicRegister resets(&resets_hw->reset);
    resets.clear_bits(mask);
}

void reset_off_and_wait(uint32_t mask)
{
    reset_off(mask);
    while (~(resets_hw->reset_done & mask));
}

} // namespace core
} // namespace hal

