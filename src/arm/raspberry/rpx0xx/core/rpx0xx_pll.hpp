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

#include <hardware/structs/pll.h>

namespace hal 
{
namespace core 
{

class Pll
{
public:
    Pll(pll_hw_t* pll);

    Pll& refdiv(uint32_t div);
    Pll& vcofreq(uint32_t freq);
    Pll& postdiv1(uint32_t div);
    Pll& postdiv2(uint32_t div);

    void init();
private:
    pll_hw_t* pll_;
    uint32_t refdiv_;
    uint32_t freq_;
    uint32_t post_div_1_;
    uint32_t post_div_2_;
};

} // namespace core
} // namespace hal

