#pragma once

#include "arm/stm32/stm32f4xx/interfaces/stm32f4xx_usart.hpp"
#include "devices/arm/stm32/stm32f4/stm32f429/gpio.hpp"

namespace hal
{
namespace interfaces
{
    using Usart = hal::stm32f4xx::interfaces::UsartCommon;
}

namespace devices
{
namespace interfaces
{

// using Usart1 = hal::stm32f1xx::interfaces::Usart1<
//     hal::devices::gpio::PA10,
//     hal::devices::gpio::PA9,
//     hal::stm32f1xx::interfaces::Usart1Mapping::Standard
// >;

}
}
}
