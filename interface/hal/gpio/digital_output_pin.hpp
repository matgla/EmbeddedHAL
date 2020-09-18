#pragma once

#include "hal/gpio/gpio_parameters.hpp"

namespace hal
{
namespace gpio
{

class DigitalOutputPin
{
public:
    virtual ~DigitalOutputPin() = default;
    virtual void init(Output mode, Speed speed) = 0;
    virtual void set_high() = 0;
    virtual void set_low() = 0;
};

} // namespace gpio
} // namespace hal
