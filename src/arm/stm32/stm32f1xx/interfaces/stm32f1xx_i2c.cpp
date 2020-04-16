#include "arm/stm32/stm32f1xx/interfaces/stm32f1xx_i2c.hpp"

#include <stm32f10x.h>

#include "hal/gpio/digital_input_output_pin.hpp"
#include "arm/stm32/stm32f1xx/gpio/stm32f1xx_gpio.hpp"

extern "C"
{
void assert_param(bool test)
{
    static_cast<void>(test);
}
}
