#include "arm/stm32/stm32f1xx/interfaces/stm32f1xx_usart.hpp"

#include <eul/utils/unused.hpp>

#include <stm32f10x.h>

#include <unistd.h>

extern "C"
{
     void USART1_IRQHandler(void);
}

static eul::function<void(uint8_t), sizeof(void*)> usart1_rx = [](uint8_t data) {
    UNUSED1(data);
};

void USART1_IRQHandler(void)
{
    if (USART1->SR & USART_SR_RXNE)
    {
        usart1_rx(USART1->DR);
    }

    if (USART1->SR & USART_SR_TXE)
    {

    }
}

void set_rx(const eul::function<void(uint8_t), sizeof(void*)>& callback)
{
    usart1_rx = callback;
}
