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

#include "arm/stm32/stm32f1xx/gpio/stm32f1xx_gpio.hpp"


#include "hal/gpio/digital_input_output_pin.hpp"

namespace hal
{
namespace gpio
{

#define impl static_cast<DigitalInputOutputPin::Impl*>(this)
#define const_impl static_cast<const DigitalInputOutputPin::Impl*>(this)

void DigitalInputOutputPin::init(const hal::gpio::Input mode)
{
    impl->init(mode);
}

void DigitalInputOutputPin::init(const hal::gpio::Output mode, const hal::gpio::Speed speed)
{
    impl->init(mode, speed);
}

void DigitalInputOutputPin::setHigh()
{
    impl->setHigh();
}

void DigitalInputOutputPin::setLow()
{
    impl->setLow();
}

bool DigitalInputOutputPin::read() const
{
    return const_impl->read();
}

namespace
{

constexpr uint8_t get_pin_mask(uint8_t o, uint8_t s)
{
    return (o << 2) | s;
}

constexpr uint32_t set_pin_mask(uint32_t reg, uint32_t pin, uint8_t mask)
{
    reg &= ~(0xF << pin * 4);       // reset pin state
    return reg | (mask << pin * 4); // set pin state
}

constexpr uint32_t get_port_state(uint32_t reg, uint32_t pin, uint8_t o, uint8_t s)
{
    return set_pin_mask(reg, pin, get_pin_mask(o, s));
}

constexpr uint8_t get_mode_mask(hal::gpio::Input m)
{
    switch (m)
    {
        case hal::gpio::Input::Analog:
            return 0x00;
        case hal::gpio::Input::InputFloating:
            return 0x01;
        case hal::gpio::Input::InputPullUpDown:
            return 0x02;
    }
    return 0x0;
}

constexpr uint8_t get_mode_mask(hal::gpio::Output m)
{
    switch (m)
    {
        case hal::gpio::Output::OutputPushPull:
            return 0x0;
        case hal::gpio::Output::OutputOpenDrain:
            return 0x1;
    }
    return 0x0;
}

constexpr uint8_t get_alternate_mode_mask(hal::gpio::Output m)
{
    switch (m)
    {
        case hal::gpio::Output::OutputPushPull:
            return 0x2;
        case hal::gpio::Output::OutputOpenDrain:
            return 0x3;
    }
    return 0x0;
}

constexpr uint8_t get_speed_mask(hal::gpio::Speed s)
{
    switch (s)
    {
        case hal::gpio::Speed::Default:
        case hal::gpio::Speed::Low:
            return 0x1;
        case hal::gpio::Speed::Medium:
            return 0x2;
        case hal::gpio::Speed::High:
            return 0x3;
    }
    return 0x0;
}

} // namespace

DigitalInputOutputPin::Impl::Impl(uint32_t port, uint32_t pin, uint32_t rcc_mask)
    : port_(port)
    , pin_(pin)
    , rcc_mask_(rcc_mask)
{
}

void DigitalInputOutputPin::Impl::init(const hal::gpio::Input mode)
{
    initClocks();
    configurePort(get_mode_mask(mode), 0x0);
    port_->BSRR = port_->BSRR | (1 << pin_);
}

void DigitalInputOutputPin::Impl::init(const hal::gpio::Output mode, const hal::gpio::Speed speed)
{
    initClocks();
    configurePort(get_mode_mask(mode), get_speed_mask(speed));
}

void DigitalInputOutputPin::Impl::init(const hal::gpio::Output mode, const hal::gpio::Speed speed, Function function)
{
    if (function == Function::Standard)
    {
        init(mode, speed);
    }
    else if (function == Function::Alternate)
    {
        initClocks();
        configurePort(get_alternate_mode_mask(mode), get_speed_mask(speed));
    }
}

void DigitalInputOutputPin::Impl::setHigh()
{
    port_->BSRR = port_->BSRR | (1 << pin_);
}

void DigitalInputOutputPin::Impl::setLow()
{
    port_->BRR = port_->BRR | (1 << pin_);
}

bool DigitalInputOutputPin::Impl::read() const
{
    return (port_->IDR & (1 << pin_)) !=0;
}

void DigitalInputOutputPin::Impl::initClocks()
{
    RCC->APB2ENR = RCC->APB2ENR | rcc_mask_;
}

void DigitalInputOutputPin::Impl::configurePort(uint8_t mode, uint8_t speed)
{
    if (pin_ <= 7)
    {
        port_->CRL = get_port_state(port_->CRL, pin_, mode, speed);
    }
    else
    {
        port_->CRH = get_port_state(port_->CRH, pin_ - 8, mode, speed);
    }
}

} // namespace gpio
} // namespace hal
