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

#include <cstdint>

#include "hal/gpio/digital_input_output_pin.hpp"

namespace hal 
{
namespace gpio 
{

enum class Function : uint32_t 
{
    xip  = 0, 
    spi  = 1,
    uart = 2,
    i2c  = 3,
    pwm  = 4,
    sio  = 5,
    pio0 = 6,
    pio1 = 7,
    gpck = 8,
    usb  = 9,
    none = 0x0f
};

class DigitalInputOutputPin::Impl : public DigitalInputOutputPin 
{
public: 
    Impl(int pin);
   
    void init(); 
    void set_output();

    void set_pull_up();
    void set_pull_down();
    void disable_pulls();

    void set_high();
    void set_low(); 

    bool read() const;
    
    void set_function(const Function function);
    const int pin;
};

} // namespace gpio
} // namespace hal

