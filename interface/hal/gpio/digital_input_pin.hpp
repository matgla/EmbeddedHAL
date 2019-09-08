#pragma once

#include "hal/gpio/gpio_parameters.hpp"

namespace hal
{
namespace gpio
{

template <typename GpioImplType>
class DigitalInputPin
{
public:
    constexpr static void init(Input mode)
    {
        GpioImplType::init(mode);
    }

    constexpr static bool read()
    {
        return GpioImplType::read();
    }

    using Implementation = GpioImplType;
};

} // namespace gpio
} // namespace hal
