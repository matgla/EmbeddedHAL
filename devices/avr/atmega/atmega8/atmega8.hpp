#pragma once

#include "hal/gpio/digital_input_output_pin.hpp"
#include "hal/interfaces/i2c.hpp"
#include "hal/interfaces/usart.hpp"

#include "avr/common/gpio/avr_gpio.hpp"
#include "avr/common/gpio/ports/avr_port_b.hpp"
#include "avr/common/gpio/ports/avr_port_c.hpp"
#include "avr/common/gpio/ports/avr_port_d.hpp"

#include "avr/common/interfaces/avr_i2c.hpp"
#include "avr/common/interfaces/avr_usart.hpp"

namespace hal
{
namespace devices
{

/* --------------------- GPIO -------------------------- */
namespace gpio
{

// ICP1
using PB0 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortB, 0>>;
// OC1A
using PB1 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortB, 1>>;
// SS/OC1B
using PB2 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortB, 2>>;
// MOSI/OC2
using PB3 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortB, 3>>;
// MISO
using PB4 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortB, 4>>;
// SCK
using PB5 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortB, 5>>;
// XTAL1/TOSC1
using PB6 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortB, 6>>;
// XTAL2/TOSC2
using PB7 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortB, 7>>;

// ADC0
using PC0 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortC, 0>>;
// ADC1
using PC1 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortC, 1>>;
// ADC2
using PC2 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortC, 2>>;
// ADC3
using PC3 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortC, 3>>;
// ADC4/SDA
using PC4 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortC, 4>>;
// ADC5/SCL
using PC5 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortC, 5>>;
// Reset
using PC6 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortC, 6>>;

// RDX
using PD0 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortD, 0>>;
// TXD
using PD1 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortD, 1>>;
// INT0
using PD2 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortD, 2>>;
// INT1
using PD3 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortD, 3>>;
// XCK/T0
using PD4 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortD, 4>>;
// T1
using PD5 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortD, 5>>;
// AIN0
using PD6 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortD, 6>>;
// AIN1
using PD7 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortD, 7>>;

} // namespace gpio

namespace interfaces
{

using I2C_1 = hal::interfaces::I2C<hal::avr::common::interfaces::AvrI2C>;
using USART_1_RX = gpio::PD0;
using USART_1_TX = gpio::PD1;
using USART = hal::interfaces::Usart<hal::avr::common::interfaces::AvrUsart>;

} // namespace interfaces


} // namespace devices
} // namespace hal
