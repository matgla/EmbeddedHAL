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

#pragma once 

#include "hal/interfaces/usart.hpp"

#include "hal/gpio/digital_input_output_pin.hpp"

namespace hal 
{
namespace interfaces 
{

class Usart::Impl : public Usart
{
public: 
    Impl(gpio::DigitalInputOutputPin& rx, 
        gpio::DigitalInputOutputPin& tx, 
        uint8_t uart_number);

    uint8_t uart_number;
    OnDataCallback on_data;
};

} // namespace interfaces
} // namespace hal

