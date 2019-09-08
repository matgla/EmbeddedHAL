#include "avr/common/gpio/ports/avr_port_b.hpp"

#include <avr/io.h>

namespace hal
{
namespace avr
{
namespace gpio
{

volatile uint8_t& AvrPortB::writeRegister()
{
    return PORTB;
}

volatile uint8_t& AvrPortB::readRegister()
{
    return PINB;
}

volatile uint8_t& AvrPortB::directionRegister()
{
    return DDRB;
}

} // namespace gpio
} // namespace avr
} // namespace hal
