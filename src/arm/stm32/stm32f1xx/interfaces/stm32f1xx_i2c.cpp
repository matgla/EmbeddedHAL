#include "arm/stm32/stm32f1xx/interfaces/stm32f1xx_i2c.hpp"

#include <stm32f10x.h>

#include "hal/gpio/digital_input_output_pin.hpp"
#include "arm/stm32/stm32f1xx/gpio/stm32f1xx_gpio.hpp"

namespace hal
{
namespace stm32f1xx
{
namespace interfaces
{
eul::function<void(), sizeof(void*)> on_dma_finished = []{};

void set_dma_callback(const eul::function<void(), sizeof(void*)>& callback)
{
    on_dma_finished = callback;
}
} // namespace interfaces

} // namespace stm32f1xx

} // namespace hak


extern "C"
{
void assert_param(bool test)
{
    static_cast<void>(test);
}
}

extern "C" void DMA1_Channel6_IRQHandler()
{
    hal::stm32f1xx::interfaces::on_dma_finished();
    DMA_ClearITPendingBit(DMA1_IT_TC6);
    DMA_Cmd(DMA1_Channel6, DISABLE);
    DMA_ITConfig(DMA1_Channel6, DMA_IT_TC, DISABLE);
}
