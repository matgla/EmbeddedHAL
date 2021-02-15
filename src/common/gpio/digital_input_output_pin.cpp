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

#include "hal/gpio/digital_input_output_pin.hpp"

namespace hal 
{
namespace gpio 
{

#define impl static_cast<DigitalInputOutputPin::Impl*>(this)
#define const_impl static_cast<DigitalInputOutputPin::Impl*>(this)

void DigitalInputOutputPin::init(const Input mode, const PullUpPullDown pupd)
{
    impl->init(mode, pupd);
}

void DigitalInputOutputPin::init(const Output mode, const Speed speed, const PullUpPullDown pupd)
{
    impl->init(mode, speed, pupd);
}

void DigitalInputOutputPin::init(const Alternate mode, const Speed speed, const PullUpPullDown pupd)
{
    impl->init(mode, speed, pupd);
}

void DigitalInputOutputPin::set_high()
{
    impl->set_high();
}

void DigitalInputOutputPin::set_low() 
{
    impl->set_low();
}

bool DigitalInputOutputPin::read() const 
{
    return const_impl->read();
}

} // namespace gpio
} // namespace hal

