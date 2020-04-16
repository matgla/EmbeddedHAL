#pragma once

#include "hal/interfaces/usart.hpp"
#include "arm/stm32/stm32f1xx/interfaces/stm32f1xx_usart.hpp"
#include "devices/arm/stm32/stm32f1/stm32f103c8t6/gpio.hpp"

namespace hal
{
namespace devices
{
namespace interfaces
{

using Usart1 = hal::stm32f1xx::interfaces::Usart1<
    hal::devices::gpio::PA10,
    hal::devices::gpio::PA9,
    hal::stm32f1xx::interfaces::Usart1Mapping::Standard
>;

}
}
}

