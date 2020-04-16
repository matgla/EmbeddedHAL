#pragma once

#include "hal/interfaces/i2c.hpp"

#include "arm/stm32/stm32f1xx/interfaces/stm32f1xx_i2c.hpp"
#include "devices/arm/stm32/stm32f1/stm32f103c8t6/gpio.hpp"

namespace hal
{
namespace devices
{
namespace interfaces
{

using I2C_1 = hal::interfaces::I2C<hal::stm32f1xx::interfaces::I2C_1<
    hal::devices::gpio::PB6,
    hal::devices::gpio::PB7,
    hal::stm32f1xx::interfaces::I2C1Mapping::Standard>>;

}
}
}

