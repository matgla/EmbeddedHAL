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

#include "arm/raspberry/rpx0xx/interfaces/rpx0xx_usart.hpp"

//#include <pico/stdlib.h>
#include <hardware/uart.h>

namespace hal 
{
namespace interfaces 
{

#define impl static_cast<Usart::Impl*>(this)
#define const_impl static_cast<const Usart::Impl*>(this)

void Usart::init(uint32_t baudrate)
{
    
}

void Usart::write(const StreamType& data)
{

}

void Usart::write(const std::string_view& str)
{

}

Usart::Impl::Impl(gpio::DigitalInputOutputPin& rx, gpio::DigitalInputOutputPin& tx)
{

}



} // namespace interfaces
} // namespace hal

