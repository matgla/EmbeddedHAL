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

extern "C" void DMA1_Channel6_IRQHandler()
{
    DMA_ClearITPendingBit(DMA1_IT_TC6);
    DMA_Cmd(DMA1_Channel6, DISABLE);
    DMA_ITConfig(DMA1_Channel6, DMA_IT_TC, DISABLE);
    hal::stm32f1xx::interfaces::on_dma_finished();
}
