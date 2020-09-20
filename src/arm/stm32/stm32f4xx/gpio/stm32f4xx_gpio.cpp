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

#include "arm/stm32/stm32f4xx/gpio/stm32f4xx_gpio.hpp"


#include "hal/gpio/digital_input_output_pin.hpp"

namespace hal
{
namespace gpio
{

#define impl static_cast<DigitalInputOutputPin::Impl*>(this)
#define const_impl static_cast<const DigitalInputOutputPin::Impl*>(this)

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

constexpr uint32_t get_mode(hal::gpio::Input m)
{
    if (m == hal::gpio::Input::Analog)
    {
        return 0x03;
    }

    return 0x00;
}

constexpr uint32_t get_type(hal::gpio::Input m)
{
    if (m == hal::gpio::Input::PullUpDown)
    {
        return 0x00;
    }

    if (m == hal::gpio::Input::Floating)
    {
        return 0x00;
    }

    return 0x00;
}

constexpr uint32_t get_type(hal::gpio::Output m)
{
    if (m == hal::gpio::Output::PushPull)
    {
        return 0x00;
    }

    if (m == hal::gpio::Output::OpenDrain)
    {
        return 0x01;
    }

    return 0x00;
}

constexpr uint32_t get_type(hal::gpio::Alternate m)
{
    if (m == hal::gpio::Alternate::PushPull)
    {
        return 0x00;
    }

    if (m == hal::gpio::Alternate::OpenDrain)
    {
        return 0x01;
    }

    return 0x00;
}


constexpr uint32_t get_pupdr(hal::gpio::PullUpPullDown m)
{
    switch (m)
    {
        case hal::gpio::PullUpPullDown::None: return 0x00;
        case hal::gpio::PullUpPullDown::Up: return 0x01;
        case hal::gpio::PullUpPullDown::Down: return 0x02;
    }
    return 0x00;
}


constexpr uint32_t get_mode(hal::gpio::Output m)
{
    return 0x01;
}

constexpr uint32_t get_alternate_mode(hal::gpio::Output m)
{
    return 0x02;
}

constexpr uint32_t get_speed(hal::gpio::Speed s)
{
    switch (s)
    {
        case hal::gpio::Speed::Default:
        case hal::gpio::Speed::Low:
            return 0x0;
        case hal::gpio::Speed::Medium:
            return 0x1;
        case hal::gpio::Speed::Fast:
            return 0x2;
        case hal::gpio::Speed::High:
            return 0x3;
    }
    return 0x0;
}

constexpr eul::memory_ptr<GPIO_TypeDef> port(uint32_t port_offset)
{
    return eul::memory_ptr<GPIO_TypeDef>(AHB1PERIPH_BASE | port_offset);
}

} // namespace

DigitalInputOutputPin::Impl::Impl(uint32_t port, uint8_t pin, uint8_t rcc_mask)
    : pin_(pin)
    , rcc_mask_(rcc_mask)
    , port_offset_(port & 0xFFFF)
{
}

void DigitalInputOutputPin::Impl::init(const Input mode, const PullUpPullDown pupd)
{
    init_clocks();
    configure_port(get_mode(mode), 0, get_pupdr(pupd), 0);
    set_low();
}

void DigitalInputOutputPin::Impl::init(const Output mode, const Speed speed, const PullUpPullDown pupd)
{
    init_clocks();
    configure_port(0x01, get_type(mode), get_pupdr(pupd), get_speed(speed));
}

void DigitalInputOutputPin::Impl::init(const Alternate mode, const Speed speed, const PullUpPullDown pupd)
{
    configure_port(0x02, get_type(mode), get_pupdr(pupd), get_speed(speed));
}

void DigitalInputOutputPin::Impl::set_high()
{
    port(port_offset_)->BSRR = port(port_offset_)->BSRR | (1 << pin_);
}

void DigitalInputOutputPin::Impl::set_low()
{
    port(port_offset_)->BSRR = port(port_offset_)->BSRR | (1 << pin_ << 16);
}

bool DigitalInputOutputPin::Impl::read() const
{
    return (port(port_offset_)->IDR & (1 << pin_)) !=0;
}

void DigitalInputOutputPin::Impl::init_clocks()
{
    RCC->AHB1ENR = RCC->AHB1ENR | rcc_mask_;
}

void DigitalInputOutputPin::Impl::configure_port(uint32_t mode, uint32_t type, uint32_t pupdr, uint32_t speed)
{
    constexpr uint32_t mode_mask = 0x03;
    port(port_offset_)->MODER = port(port_offset_)->MODER & ~(mode_mask << pin_ * 2);
    port(port_offset_)->MODER = port(port_offset_)->MODER | (mode << pin_ * 2);

    constexpr uint32_t otype_mask = 0x01;
    port(port_offset_)->OTYPER = port(port_offset_)->OTYPER & ~(otype_mask << pin_);
    port(port_offset_)->OTYPER = port(port_offset_)->OTYPER | (type << pin_);

    constexpr uint32_t speed_mask = 0x02;
    port(port_offset_)->OSPEEDR = port(port_offset_)->OSPEEDR & ~(speed_mask << pin_ * 2);
    port(port_offset_)->OSPEEDR = port(port_offset_)->OSPEEDR | (speed << pin_ * 2);

    constexpr uint32_t pupd_mask = 0x02;
    port(port_offset_)->PUPDR = port(port_offset_)->PUPDR & ~(pupd_mask << pin_ * 2);
    port(port_offset_)->PUPDR = port(port_offset_)->PUPDR | (pupdr << pin_ * 2);
}

void DigitalInputOutputPin::Impl::set_alternate_function(uint32_t function)
{
    constexpr uint32_t af_mask = 0xF;
    if (pin_ < 8)
    {
        port(port_offset_)->AFR[0] = port(port_offset_)->AFR[0] & ~(af_mask << pin_ * 4);
        port(port_offset_)->AFR[0] = port(port_offset_)->AFR[0] | (function << pin_ * 4);
    }
    else
    {
        port(port_offset_)->AFR[1] = port(port_offset_)->AFR[1] & ~(af_mask << (pin_ - 8) * 4);
        port(port_offset_)->AFR[1] = port(port_offset_)->AFR[1] | (function << (pin_ - 8) * 4);
    }
}


} // namespace gpio
} // namespace hal
