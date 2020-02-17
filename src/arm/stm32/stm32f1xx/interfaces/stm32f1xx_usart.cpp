#include "arm/stm32/stm32f1xx/interfaces/stm32f1xx_usart.hpp"

#include <stm32f10x.h>

extern "C"
{
     void USART1_IRQHandler(void);
}

void USART1_IRQHandler(void)
{
    if (USART1->SR & USART_SR_RXNE)
    {
        hal::stm32f1xx::interfaces::usart1_rx(USART1->DR);
        // USART1->SR &= ~USART_SR_RXNE;
    }

    if (USART1->SR & USART_SR_TXE)
    {

    }
}
