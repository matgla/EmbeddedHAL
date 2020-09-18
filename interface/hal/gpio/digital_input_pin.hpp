#pragma once

#include "hal/gpio/gpio_parameters.hpp"

namespace hal
{
namespace gpio
{

class DigitalInputPin
{
public:
    void init(Input mode);
    bool read();
};

} // namespace gpio
} // namespace hal
