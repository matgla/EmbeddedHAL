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

#pragma once 

#include <cstdint>

constexpr unsigned long long int operator "" _Hz(unsigned long long int value)
{
    return value; 
}

constexpr unsigned long long int operator "" _KHz(unsigned long long int value)
{
    return value * 1000; 
}

constexpr unsigned long long int operator "" _MHz(unsigned long long int value)
{
    return value * 1000000; 
}

constexpr unsigned long long int operator "" _GHz(unsigned long long int value)
{
    return value * 1000000000; 
}
