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

#include <eul/memory_ptr.hpp>

#include <stm32f4xx.h>

#include "hal/gpio/digital_input_output_pin.hpp"

namespace hal
{
namespace gpio
{

class DigitalInputOutputPin::Impl : public DigitalInputOutputPin
{
public:
    Impl(uint32_t port_offset, uint8_t pin, uint8_t rcc_mask);
    void init(const Input mode, const PullUpPullDown pupd);
    void init(const Output mode, const Speed speed, const PullUpPullDown pupd);
    void init(const Alternate mode, const Speed speed, const PullUpPullDown pupd);
    void set_high();
    void set_low();
    bool read() const;
    void set_alternate_function(uint32_t function);
private:
    void init_clocks();
    void configure_port(uint32_t mode, uint32_t type, uint32_t pupdr, uint32_t speed);

    const uint8_t pin_;
    const uint8_t rcc_mask_;
    const uint16_t port_offset_;
};

} // namespace gpio
} // namespace hal

