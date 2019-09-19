#pragma once

#include <cstdint>

#include <gsl/span>

namespace hal
{
namespace interfaces
{

template <typename I2CImpl>
class I2C
{
public:
    static void init()
    {
        I2CImpl::init();
    }

    static bool start(uint8_t address)
    {
        return I2CImpl::start(address);
    }

    static bool write(uint8_t byte)
    {
        return I2CImpl::write(byte);
    }

    static void write(const gsl::span<uint8_t>& data)
    {
        I2CImpl::write(data);
    }

    static void stop()
    {
        I2CImpl::stop();
    }

    static uint8_t read()
    {
        return I2CImpl::read();
    }
};

} // namespace interfaces
} // namespace hal
