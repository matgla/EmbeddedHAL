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
#include <string_view>

#include <gsl/span>

#include <stm32f10x.h>

#include <eul/function.hpp>
#include <eul/memory_ptr.hpp>

#include "hal/interfaces/usart.hpp"
#include "hal/clock/clock.hpp"
#include "hal/gpio/digital_input_output_pin.hpp"
#include "arm/stm32/stm32f1xx/gpio/stm32f1xx_gpio.hpp"
#include "arm/stm32/stm32f1xx/clock/stm32f1xx_clock.hpp"

namespace hal
{
namespace interfaces
{

enum class Usart1Mapping
{
    /* Tx - PA9, Rx - PA10 */
    Standard,
    /* Tx - PB6, Rx - PB7 */
    Alternate
};

using Usart2Mapping = Usart1Mapping;

enum class Usart3Mapping
{
    Standard,
    PartialAlternate,
    Alternate
};

class Usart::Impl : public Usart
{
public:
    Impl(gpio::DigitalInputOutputPin& rx, gpio::DigitalInputOutputPin& tx, uint32_t usart_address);

    void init(const uint32_t baudrate);
    void set_baudrate(const uint32_t baudrate);

    void write(const StreamType& data);
    void write(const std::string_view& data);

    void on_data(const OnDataCallback& callback);
    void on_sent(const OnSentCallback& callback);

private:
    void write(const char byte);
    void set_baudrate(const uint32_t bus_frequency, const uint32_t baudrate);
    void init(const uint32_t bus_frequency, const uint32_t baudrate);
    void wait_for_tx();

    eul::memory_ptr<USART_TypeDef> usart_;
    hal::gpio::DigitalInputOutputPin& rx_;
    hal::gpio::DigitalInputOutputPin& tx_;
    Usart::OnDataCallback rx_callback_;
    Usart::OnSentCallback tx_callback_;
};

} // namespace interfaces
} // namespace hal
