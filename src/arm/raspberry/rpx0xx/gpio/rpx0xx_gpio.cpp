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

#include <hardware/gpio.h>

#include "arm/raspberry/rpx0xx/gpio/rpx0xx_gpio.hpp"

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
    gpio_put(pin, 1);
}

void DigitalInputOutputPin::Impl::set_low() 
{
    gpio_put(pin, 0);
}

void DigitalInputOutputPin::Impl::init()
{
    gpio_init(pin);
}

void DigitalInputOutputPin::Impl::set_output()
{
    gpio_set_dir(pin, GPIO_OUT);
}

void DigitalInputOutputPin::Impl::set_pull_up() 
{
    gpio_pull_up(pin);
}

void DigitalInputOutputPin::Impl::set_pull_down()
{
    gpio_pull_down(pin);
}

void DigitalInputOutputPin::Impl::disable_pulls()
{
    gpio_disable_pulls(pin);
}

} // namespace gpio
} // namespace hal

