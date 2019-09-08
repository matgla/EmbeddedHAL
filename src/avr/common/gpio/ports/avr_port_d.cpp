#include "avr/common/gpio/ports/avr_port_d.hpp"

#include <avr/io.h>

namespace hal
{
namespace avr
{
namespace gpio
{

volatile uint8_t& AvrPortD::writeRegister()
{
    return PORTD;
}

volatile uint8_t& AvrPortD::readRegister()
{
    return PIND;
}

volatile uint8_t& AvrPortD::directionRegister()
{
    return DDRD;
}

} // namespace gpio
} // namespace avr
} // namespace hal
