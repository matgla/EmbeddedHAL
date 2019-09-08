#pragma once

#include "hal/gpio/gpio_parameters.hpp"

namespace hal
{
namespace gpio
{

template <typename GpioImplType>
class DigitalOutputPin
{
public:
    constexpr static void init(Output mode, Speed speed)
    {
        GpioImplType::init(mode, speed);
    }

    constexpr static void setHigh()
    {
        GpioImplType::setHigh();
    }

    constexpr static void setLow()
    {
        GpioImplType::setLow();
    }

    using Implementation = GpioImplType;
};

} // namespace gpio
} // namespace hal
