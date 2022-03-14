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

#include "arm/raspberry/rpx0xx/gpio/rpx0xx_gpio.hpp"

#include <hardware/uart.h>
#include <hardware/gpio.h>

namespace hal 
{
namespace interfaces 
{

#define impl static_cast<Usart::Impl*>(this)
#define const_impl static_cast<const Usart::Impl*>(this)

void Usart::init(uint32_t baudrate)
{
   uart_init(impl->uart_number, baudrate);    
}

void Usart::deinit() 
{
   uart_deinit(impl->uart_number);
}

void Usart::write(const StreamType& data)
{
   uart_write_blocking(impl->uart_number, data.data(), data.size());
}

void Usart::write(const std::string_view& str)
{
   uart_puts(impl->instance, str.data());
}

void Usart::on_data(const OnDataCallback& callback)
{
   impl->on_data = callback; 
}

uint8_t Usart::read() const 
{
   return uart_getc(const_impl->instance);
}

Usart::Impl::Impl(gpio::DigitalInputOutputPin& rx, gpio::DigitalInputOutputPin& tx, uint8_t usart_numer)
    : uart_number(usart_numer)
{
   const auto* rx_impl = static_cast<hal::gpio::DigitalInputOutputPin::Impl*>(&rx);
   const auto* tx_impl = static_cast<hal::gpio::DigitalInputOutputPin::Impl*>(&tx);
    
   gpio_set_function(rx_impl->pin, GPIO_FUNC_UART);
   gpio_set_function(tx_impl->pin, GPIO_FUNC_UART);
}

} // namespace interfaces
} // namespace hal

