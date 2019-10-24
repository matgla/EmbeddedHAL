#pragma once

#include "hal/gpio/digital_input_output_pin.hpp"
#include "arm/stm32/stm32f1xx/gpio/stm32f1xx_gpio.hpp"

namespace hal
{
namespace devices
{

/* --------------------- GPIO -------------------------- */
namespace gpio
{

using PA0  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 0, RCC_APB2ENR_IOPAEN>>;
using PA1  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 1, RCC_APB2ENR_IOPAEN>>;
using PA2  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 2, RCC_APB2ENR_IOPAEN>>;
using PA3  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 3, RCC_APB2ENR_IOPAEN>>;
using PA4  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 4, RCC_APB2ENR_IOPAEN>>;
using PA5  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 5, RCC_APB2ENR_IOPAEN>>;
using PA6  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 6, RCC_APB2ENR_IOPAEN>>;
using PA7  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 7, RCC_APB2ENR_IOPAEN>>;
using PA8  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 8, RCC_APB2ENR_IOPAEN>>;
using PA9  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 9, RCC_APB2ENR_IOPAEN>>;
using PA10 = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 10, RCC_APB2ENR_IOPAEN>>;
using PA11 = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 11, RCC_APB2ENR_IOPAEN>>;
using PA12 = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 12, RCC_APB2ENR_IOPAEN>>;
using PA13 = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 13, RCC_APB2ENR_IOPAEN>>;
using PA14 = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 14, RCC_APB2ENR_IOPAEN>>;
using PA15 = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOA_BASE, 15, RCC_APB2ENR_IOPAEN>>;

using PB0  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 0, RCC_APB2ENR_IOPBEN>>;
using PB1  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 1, RCC_APB2ENR_IOPBEN>>;
using PB2  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 2, RCC_APB2ENR_IOPBEN>>;
using PB3  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 3, RCC_APB2ENR_IOPBEN>>;
using PB4  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 4, RCC_APB2ENR_IOPBEN>>;
using PB5  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 5, RCC_APB2ENR_IOPBEN>>;
using PB6  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 6, RCC_APB2ENR_IOPBEN>>;
using PB7  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 7, RCC_APB2ENR_IOPBEN>>;
using PB8  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 8, RCC_APB2ENR_IOPBEN>>;
using PB9  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 9, RCC_APB2ENR_IOPBEN>>;
using PB10 = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 10, RCC_APB2ENR_IOPBEN>>;
using PB11 = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 11, RCC_APB2ENR_IOPBEN>>;
using PB12 = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 12, RCC_APB2ENR_IOPBEN>>;
using PB13 = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 13, RCC_APB2ENR_IOPBEN>>;
using PB14 = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 14, RCC_APB2ENR_IOPBEN>>;
using PB15 = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOB_BASE, 15, RCC_APB2ENR_IOPBEN>>;

using PC0  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOC_BASE, 0, RCC_APB2ENR_IOPCEN>>;
using PC1  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOC_BASE, 1, RCC_APB2ENR_IOPCEN>>;
using PC2  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOC_BASE, 2, RCC_APB2ENR_IOPCEN>>;
using PC3  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOC_BASE, 3, RCC_APB2ENR_IOPCEN>>;
using PC4  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOC_BASE, 4, RCC_APB2ENR_IOPCEN>>;
using PC5  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOC_BASE, 5, RCC_APB2ENR_IOPCEN>>;
using PC6  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOC_BASE, 6, RCC_APB2ENR_IOPCEN>>;
using PC7  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOC_BASE, 7, RCC_APB2ENR_IOPCEN>>;
using PC8  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOC_BASE, 8, RCC_APB2ENR_IOPCEN>>;
using PC9  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOC_BASE, 9, RCC_APB2ENR_IOPCEN>>;
using PC10 = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOC_BASE, 10, RCC_APB2ENR_IOPCEN>>;
using PC11 = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOC_BASE, 11, RCC_APB2ENR_IOPCEN>>;
using PC12 = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOC_BASE, 12, RCC_APB2ENR_IOPCEN>>;
using PC13 = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOC_BASE, 13, RCC_APB2ENR_IOPCEN>>;
using PC14 = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOC_BASE, 14, RCC_APB2ENR_IOPCEN>>;
using PC15 = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOC_BASE, 15, RCC_APB2ENR_IOPCEN>>;

using PD0  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOD_BASE, 0, RCC_APB2ENR_IOPDEN>>;
using PD1  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOD_BASE, 1, RCC_APB2ENR_IOPDEN>>;
using PD2  = hal::gpio::DigitalInputOutputPin<hal::stm32f1xx::gpio::StmGpio<GPIOD_BASE, 2, RCC_APB2ENR_IOPDEN>>;

} // namespace gpio


} // namespace devices
} // namespace hal
