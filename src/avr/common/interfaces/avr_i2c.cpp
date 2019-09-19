#include "avr/common/interfaces/avr_i2c.hpp"

#include <avr/io.h>
#include <util/twi.h>

#include "avr_usart.hpp"

namespace hal
{
namespace avr
{
namespace common
{
namespace interfaces
{

constexpr uint32_t SCL_CLOCK = 800000;
void AvrI2C::init()
{
    TWSR = 0;
    TWBR = ((F_CPU/SCL_CLOCK)-16)/2;
}

bool __attribute__((optimize("O0"))) AvrI2C::start(uint8_t address)
{
    TWCR = 0;
    TWCR = (1<<TWINT) | (1<<TWEN) |( 1<<TWSTA);
    while (! (TWCR & (1<<TWINT)));

    char data[40];
    twi_register_status = TW_STATUS & 0xF8;
    itoa(twi_register_status, data, 16);
    if ((twi_register_status != TW_START) && (twi_register_status != TW_REP_START)) {
        return false;
    }


    TWDR = (address << 1);
    TWCR = (1<<TWINT) | (1<<TWEN);
    while( !(TWCR & (1<<TWINT)) );
    twi_register_status = TW_STATUS & 0xF8;
    if ((twi_register_status != TW_MT_SLA_ACK) && (twi_register_status != TW_MR_SLA_ACK)) {
        return false;
    }
    return true;
}

void __attribute__((optimize("O0"))) AvrI2C::stop()
{
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

bool __attribute__((optimize("O0"))) AvrI2C::write(uint8_t byte)
{
    TWDR = byte;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (! (TWCR & (1<<TWINT)));

    twi_register_status = TW_STATUS & 0xF8;
    if (twi_register_status != TW_MT_DATA_ACK) {
        return false;
    } else {
        return true;
    }
}

uint8_t __attribute__((optimize("O0"))) AvrI2C::read()
{
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
    // wait for end of transmission
    while( !(TWCR & (1<<TWINT)) );
    // return received data from TWDR
    return TWDR;
}

void AvrI2C::write(gsl::span<uint8_t>& data)
{
    for (const auto byte : data)
    {
        write(data);
    }
}

} // namespace interfaces
} // namespace common
} // namespace avr
} // namespace hal
