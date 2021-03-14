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

#include "arm/raspberry/rpx0xx/gpio/rpx0xx_gpio.hpp"

#include <hardware/structs/sio.h>
#include <hardware/structs/padsbank0.h>
#include <hardware/structs/iobank0.h>

#include "arm/raspberry/rpx0xx/core/rpx0xx_register_manipulator.hpp"

namespace hal 
{
namespace gpio 
{

#define impl static_cast<DigitalInputOutputPin::Impl*>(this)

void DigitalInputOutputPin::set_high()
{
    impl->set_high();
}

void DigitalInputOutputPin::set_low() 
{
    impl->set_low();
}

void DigitalInputOutputPin::init(hal::gpio::Output mode, hal::gpio::Speed speed, hal::gpio::PullUpPullDown pupd)
{
    impl->init();
    impl->set_output();
    switch (pupd) 
    {
        case hal::gpio::PullUpPullDown::None:
        {
            impl->disable_pulls();
        } break;
        case hal::gpio::PullUpPullDown::Up:
        {
            impl->set_pull_up();
        } break; 
        case hal::gpio::PullUpPullDown::Down:
        {
            impl->set_pull_down();
        } break;
    }
}

DigitalInputOutputPin::Impl::Impl(int pin) 
    : pin(pin) 
{
}

void DigitalInputOutputPin::Impl::set_high() 
{
    sio_hw->gpio_set = 1 << pin;
}

void DigitalInputOutputPin::Impl::set_low() 
{
    sio_hw->gpio_clr = 1 << pin;
}

void DigitalInputOutputPin::Impl::init()
{
    sio_hw->gpio_oe_clr = 1ul << pin;
    sio_hw->gpio_clr = 1 << pin;

    set_function(Function::sio); 
}

void DigitalInputOutputPin::Impl::set_output()
{
    sio_hw->gpio_oe_set = 1 << pin;
}

void DigitalInputOutputPin::Impl::set_pull_up() 
{
    core::AtomicRegister padsbank0(&padsbank0_hw->io[pin]);
    padsbank0.write_masked(1u << PADS_BANK0_GPIO0_PUE_LSB, PADS_BANK0_GPIO0_PUE_BITS);
}

void DigitalInputOutputPin::Impl::set_pull_down()
{
    core::AtomicRegister padsbank0(&padsbank0_hw->io[pin]);
    padsbank0.write_masked(1u << PADS_BANK0_GPIO0_PDE_LSB, PADS_BANK0_GPIO0_PDE_BITS);
}

void DigitalInputOutputPin::Impl::disable_pulls()
{
    core::AtomicRegister padsbank0(&padsbank0_hw->io[pin]);
    padsbank0.clear_bits(PADS_BANK0_GPIO0_PUE_BITS | PADS_BANK0_GPIO0_PDE_BITS);
}

void DigitalInputOutputPin::Impl::set_function(const Function function)
{
    core::AtomicRegister padsbank0(&padsbank0_hw->io[pin]);
    constexpr uint32_t mask = PADS_BANK0_GPIO0_IE_BITS | PADS_BANK0_GPIO0_OD_BITS;
    padsbank0.write_masked(PADS_BANK0_GPIO0_IE_BITS, mask);

    iobank0_hw->io[pin].ctrl = static_cast<uint32_t>(function) << IO_BANK0_GPIO0_CTRL_FUNCSEL_LSB;
}

} // namespace gpio
} // namespace hal

