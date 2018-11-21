#pragma once

#include <cstdint>
#include <string_view>

#include <gsl/span>

#include <stm32f1xx.h>

#include "hal/gpio.hpp"

namespace hal
{
namespace stm32f10x
{
namespace interfaces
{

struct UsartConfig
{
    const uint32_t tx_pin;
    const uint32_t rx_pin;
    const uint32_t cts_pin;
    const uint32_t rts_pin;
    const uint32_t ct_pin;
};

enum class Usart1Mapping
{
    /* Tx - PA9, Rx - PA10 */
    Standard,
    /* Tx - PB6, Rx - PB7 */
    Alternate
};

using Usart2Mapping = Usart1Mapping;

enum class Usart3Mapping
{
    Standard,
    PartialAlternate,
    Alternate
};

template <typename Rx, typename Tx, typename Cts = void, typename Rts = void, typename Ct = void>
struct Pinout
{
    using RxPin  = Rx;
    using TxPin  = Tx;
    using CtsPin = Cts;
    using RtsPin = Rts;
    using CtPin  = Ct;
};

template <Usart1Mapping mapping>
constexpr auto get_pinout()
{
    if constexpr (mapping == Usart1Mapping::Standard)
    {
        return Pinout<hal::gpio::PA10, hal::gpio::PA9>{};
    }
    else if (mapping == Usart1Mapping::Alternate)
    {
        return Pinout<hal::gpio::PB7, hal::gpio::PB6>{};
    }
}

template <Usart1Mapping usartMapping>
class Usart1
{
public:
    using RxPin = typename decltype(get_pinout<usartMapping>())::RxPin;
    using TxPin = typename decltype(get_pinout<usartMapping>())::TxPin;

    /*
1.     Enable the USART by writing the UE bit in USART_CR1 register to 1.
2.     Program the M bit in USART_CR1 to define the word length.
3.     Program the number of stop bits in USART_CR2.
4.     Select DMA enable (DMAT) in USART_CR3 if Multi buffer Communication is to take place. Configure the DMA register as explained in multibuffer communication.
5.     Select the desired baud rate using the USART_BRR register.
6.     Set the TE bit in USART_CR1 to send an idle frame as first transmission.
7.     Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this for each data to be transmitted in case of single buffer.
8.     After writing the last data into the USART_DR register, wait until TC=1. This indicates that the transmission of the last frame is
       complete. This is required for instance when the USART is disabled or enters the Halt mode to avoid corrupting the last transmission
*/
    static void init(uint32_t baudrate)
    {
        /* enable clock */
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_AFIOEN;

        /* configure gpio */
        TxPin::Implementation::init(hal::gpio::Output::OutputPushPull,
                                    hal::gpio::Speed::Medium,
                                    hal::stm32f10x::gpio::Function::Alternate);
        RxPin::init(hal::gpio::Input::InputFloating);

        /* configure usart */
        USART1->BRR = SystemCoreClock / baudrate;

        /* enable tx */
        USART1->CR1 |= USART_CR1_TE;
        /* enable rx */
        USART1->CR1 |= USART_CR1_RE;

        /* enable USART */
        USART1->CR1 |= USART_CR1_UE;
    }

    static void write(const char byte)
    {
        while (!(USART1->SR & USART_SR_TXE))
            ;

        USART1->DR = byte;
    }

    static void write(const gsl::span<const uint8_t>& data)
    {
        for (const auto byte : data)
        {
            write(byte);
        }
    }

    static void write(const std::string_view& data)
    {
        for (const auto byte : data)
        {
            write(byte);
        }
    }

    template <typename CallbackType>
    static void onData(const CallbackType& onDataCallback)
    {
        // UsartImplType::onData(onDataCallba)
    }
};


} // namespace interfaces
} // namespace stm32f10x
} // namespace hal