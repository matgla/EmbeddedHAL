#pragma once

#include <avr/io.h>

namespace hal
{
namespace avr
{
namespace gpio
{

struct AvrPortB
{
    static volatile uint8_t& writeRegister() { return PORTB; }
    static volatile uint8_t& readRegister() { return PINB; }
    static volatile uint8_t& directionRegister() { return DDRB; }
};

} // namespace gpio
} // namespace avr
} // namespae hal
