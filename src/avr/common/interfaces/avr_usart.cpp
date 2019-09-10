#include "avr/common/interfaces/avr_usart.hpp"

#include <avr/io.h>
#include <avr/interrupt.h>

namespace hal
{
namespace avr
{
namespace common
{
namespace interfaces
{

void AvrUsart::initUsart(uint32_t baudrate)
{
    setBaudrate(baudrate);
    UCSRB = (1<<RXEN)|(1<<TXEN);
    UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
}

void AvrUsart::setBaudrate(uint32_t baudrate)
{
    uint32_t baudrate_prescale = (((F_CPU / (baudrate * 16UL))) - 1);
    UBRRH = (baudrate_prescale >> 8);
    UBRRL = baudrate_prescale;
}

void __attribute__((optimize("O0"))) AvrUsart::write(uint8_t byte)
{
    while (!( UCSRA & (1<<UDRE)));
    UDR = byte;
}


void AvrUsart::write(const gsl::span<uint8_t>& data)
{
    for (const auto byte : data)
    {
        write(byte);
    }
}

void AvrUsart::write(const std::string_view& str)
{
    for (const auto byte : str)
    {
        write(static_cast<uint8_t>(byte));
    }
}


} // namespace interfaces
} // namespace common
} // namespace avr
} // namespace hal
