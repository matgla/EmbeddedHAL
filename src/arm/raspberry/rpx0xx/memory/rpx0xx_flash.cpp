// This file is part of EmbeddedHAL project.
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

#include <hal/memory/flash.hpp>

extern "C"
{
#include <hardware/flash.h>
}

namespace hal 
{
namespace memory 
{

bool Flash::erase(std::size_t address, std::size_t size) 
{
    flash_range_erase(address, size);
    return true;
}

bool Flash::write(std::size_t address, std::span<const uint8_t> data)
{
    flash_range_program(address, data.data(), data.size());
    return true;
}

} // namespace memory
} // namespace hal

