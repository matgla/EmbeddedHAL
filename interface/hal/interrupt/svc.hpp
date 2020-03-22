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
namespace interrupt
{

using SvcHandler = eul::function<void(uint32_t number, void* args, void* return_value), 0>;
void set_svc_handler(const SvcHandler& handler);
void set_svc_priority(uint8_t priority);

} // namespace interrupt
} // namespace hal

