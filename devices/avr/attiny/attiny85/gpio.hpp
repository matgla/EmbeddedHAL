#pragma once

#include "hal/gpio/digital_input_output_pin.hpp"
#include "avr/common/gpio/avr_gpio.hpp"
#include "avr/common/gpio/ports/avr_port_b.hpp"

namespace hal
{
namespace devices
{

/* --------------------- GPIO -------------------------- */
namespace gpio
{

// MOSI/SI/SDA/AIN0/OC0A/OC1A/AREF/PCINT0
using PB0 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortB, 0>>;
// MISO/DO/AIN1/OCOB/OC1A/PCINT1
using PB1 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortB, 1>>;
// SCK/USCK/SCL/ADC1/T0/INT0/PCINT2
using PB2 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortB, 2>>;
// PCINT3/XTAL1/CLKI/OC1B/ADC3
using PB3 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortB, 3>>;
// PCINT4/XTAL2/CLKO/OC1B/ADC2
using PB4 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortB, 4>>;
// PCINT5/RESET/ADC0/dW
using PB5 = hal::gpio::DigitalInputOutputPin<hal::avr::gpio::AvrGpio<hal::avr::gpio::AvrPortB, 5>>;

} // namespace gpio


} // namespace devices
} // namespace hal
