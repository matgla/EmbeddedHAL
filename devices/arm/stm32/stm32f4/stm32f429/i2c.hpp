#pragma once

#include "hal/interfaces/i2c.hpp"

#include "arm/stm32/stm32f4xx/interfaces/stm32f4xx_i2c.hpp"
#include "devices/arm/stm32/stm32f4/stm32f429/gpio.hpp"

namespace hal
{

namespace interfaces
{
using I2C = hal::stm32f4xx::interfaces::I2CCommon;
} // namespace interfaces

namespace devices
{
namespace interfaces
{

// using I2C_1 = hal::stm32f4xx::interfaces::I2C_1<
//     hal::devices::gpio::PB6,
//     hal::devices::gpio::PB7,
//     hal::stm32f1xx::interfaces::I2C1Mapping::Standard>;

}
}
}

