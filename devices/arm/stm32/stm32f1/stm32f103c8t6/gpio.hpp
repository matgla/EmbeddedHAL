#pragma once

#include "hal/gpio/digital_input_output_pin.hpp"
#include "arm/stm32/stm32f1xx/gpio/stm32f1xx_gpio.hpp"

namespace hal
{
namespace gpio
{
using DigitalInputOutputPin = hal::stm32f1xx::gpio::Stm32GpioCommon;
}
namespace devices
{

/* --------------------- GPIO -------------------------- */
namespace gpio
{

using PA0  = hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 0, RCC_APB2ENR_IOPAEN>;
using PA1  = hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 1, RCC_APB2ENR_IOPAEN>;
using PA2  = hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 2, RCC_APB2ENR_IOPAEN>;
using PA3  = hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 3, RCC_APB2ENR_IOPAEN>;
using PA4  = hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 4, RCC_APB2ENR_IOPAEN>;
using PA5  = hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 5, RCC_APB2ENR_IOPAEN>;
using PA6  = hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 6, RCC_APB2ENR_IOPAEN>;
using PA7  = hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 7, RCC_APB2ENR_IOPAEN>;
using PA8  = hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 8, RCC_APB2ENR_IOPAEN>;
using PA9  = hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 9, RCC_APB2ENR_IOPAEN>;
using PA10 = hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 10, RCC_APB2ENR_IOPAEN>;
using PA11 = hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 11, RCC_APB2ENR_IOPAEN>;
using PA12 = hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 12, RCC_APB2ENR_IOPAEN>;
using PA13 = hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 13, RCC_APB2ENR_IOPAEN>;
using PA14 = hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 14, RCC_APB2ENR_IOPAEN>;
using PA15 = hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 15, RCC_APB2ENR_IOPAEN>;

using PB0  = hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 0, RCC_APB2ENR_IOPBEN>;
using PB1  = hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 1, RCC_APB2ENR_IOPBEN>;
using PB2  = hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 2, RCC_APB2ENR_IOPBEN>;
using PB3  = hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 3, RCC_APB2ENR_IOPBEN>;
using PB4  = hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 4, RCC_APB2ENR_IOPBEN>;
using PB5  = hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 5, RCC_APB2ENR_IOPBEN>;
using PB6  = hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 6, RCC_APB2ENR_IOPBEN>;
using PB7  = hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 7, RCC_APB2ENR_IOPBEN>;
using PB8  = hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 8, RCC_APB2ENR_IOPBEN>;
using PB9  = hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 9, RCC_APB2ENR_IOPBEN>;
using PB10 = hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 10, RCC_APB2ENR_IOPBEN>;
using PB11 = hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 11, RCC_APB2ENR_IOPBEN>;
using PB12 = hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 12, RCC_APB2ENR_IOPBEN>;
using PB13 = hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 13, RCC_APB2ENR_IOPBEN>;
using PB14 = hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 14, RCC_APB2ENR_IOPBEN>;
using PB15 = hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 15, RCC_APB2ENR_IOPBEN>;

using PC13 = hal::stm32f1xx::gpio::StmGpio<GPIOC_BASE, 13, RCC_APB2ENR_IOPCEN>;
using PC14 = hal::stm32f1xx::gpio::StmGpio<GPIOC_BASE, 14, RCC_APB2ENR_IOPCEN>;
using PC15 = hal::stm32f1xx::gpio::StmGpio<GPIOC_BASE, 15, RCC_APB2ENR_IOPCEN>;

using PD0  = hal::stm32f1xx::gpio::StmGpio<GPIOD_BASE, 0, RCC_APB2ENR_IOPDEN>;
using PD1  = hal::stm32f1xx::gpio::StmGpio<GPIOD_BASE, 1, RCC_APB2ENR_IOPDEN>;

} // namespace gpio


} // namespace devices
} // namespace hal
