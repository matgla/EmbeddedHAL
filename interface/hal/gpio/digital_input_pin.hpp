#pragma once

#include "hal/gpio/gpio_parameters.hpp"

namespace hal
{
namespace gpio
{

class DigitalInputPin
{
public:
    virtual ~DigitalInputPin() = default;
    virtual void init(Input mode) = 0;
    virtual bool read() = 0;
};

} // namespace gpio
} // namespace hal
