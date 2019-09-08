#include "avr/common/gpio/ports/avr_port_a.hpp"

#include <avr/io.h>

namespace hal
{
namespace avr
{
namespace gpio
{

volatile uint8_t& AvrPortA::writeRegister()
{
    return PORTA;
}

volatile uint8_t& AvrPortA::readRegister()
{
    return PINA;
}

volatile uint8_t& AvrPortA::directionRegister()
{
    return DDRA;
}

} // namespace gpio
} // namespace avr
} // namespace hal
