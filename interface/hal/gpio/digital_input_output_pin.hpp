#pragma once

#include "hal/gpio/gpio_parameters.hpp"
#include "hal/gpio/digital_input_pin.hpp"
#include "hal/gpio/digital_output_pin.hpp"

namespace hal
{
namespace gpio
{

template <class GpioImplType>
class DigitalInputOutputPin : public DigitalInputPin<GpioImplType>, public DigitalOutputPin<GpioImplType>
{
public:
    using Implementation = GpioImplType;
    using OutputType = DigitalOutputPin<GpioImplType>;
    using InputType = DigitalInputPin<GpioImplType>;
};

} // namespace gpio
} // namespace hal
