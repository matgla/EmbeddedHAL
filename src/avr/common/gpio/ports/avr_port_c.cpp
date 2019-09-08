#include "avr/common/gpio/ports/avr_port_c.hpp"

#include <avr/io.h>

namespace hal
{
namespace avr
{
namespace gpio
{

volatile uint8_t& AvrPortC::writeRegister()
{
    return PORTC;
}

volatile uint8_t& AvrPortC::readRegister()
{
    return PINC;
}

volatile uint8_t& AvrPortC::directionRegister()
{
    return DDRC;
}

} // namespace gpio
} // namespace avr
} // namespace hal
