
#pragma once

#include <cstdint>
#include <string_view>

#include <gsl/span>

#include <stm32f10x.h>

#include <eul/function.hpp>
#include <eul/memory_ptr.hpp>

#include "hal/interfaces/usart.hpp"
#include "hal/clock/clock.hpp"
#include "hal/gpio/digital_input_output_pin.hpp"
#include "arm/stm32/stm32f1xx/gpio/stm32f1xx_gpio.hpp"
#include "arm/stm32/stm32f1xx/clock/stm32f1xx_clock.hpp"

void set_rx(const eul::function<void(uint8_t), sizeof(void*)>& callback);

namespace hal
{
namespace interfaces
{

// TODO: check if correct mapping used with static assert
enum class UsartMapping
{
    /* Tx - PA9, Rx - PA10 */
    Standard,
    /* Tx - PB6, Rx - PB7 */
    Alternate,
    PartialAlternate
};

} // namespace interfaces

namespace stm32f1xx
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




template <typename Rx, typename Tx, typename Cts = void, typename Rts = void, typename Ct = void>
struct Pinout
{
    using RxPin  = Rx;
    using TxPin  = Tx;
    using CtsPin = Cts;
    using RtsPin = Rts;
    using CtPin  = Ct;
};

template <uint32_t base>
constexpr void init_rcc()
{
    if constexpr (base == USART1_BASE)
    {
        RCC->APB2ENR = RCC->APB2ENR | RCC_APB2ENR_USART1EN;
    }
}

template <typename rx, typename tx, hal::interfaces::UsartMapping mapping, uint32_t base>
class UsartCommon
{
public:
    using OnDataCallback = eul::function<void(const uint8_t), sizeof(void*)>;
    using StreamType = gsl::span<const uint8_t>;

    constexpr static void init(uint32_t baudrate)
    {
        init(hal::stm32f1xx::clock::Clock::get_core_clock(), baudrate);
    }

    constexpr static void init(uint32_t bus_frequency, uint32_t baudrate)
    {
        init_rcc<base>();
        tx::init(hal::gpio::Output::OutputPushPull,
                                    hal::gpio::Speed::Medium,
                                    hal::stm32f1xx::gpio::Function::Alternate);
        rx::init(hal::gpio::Input::InputFloating);

        set_baudrate(bus_frequency, baudrate);
        /* enable tx */
        usart_->CR1 = usart_->CR1 | USART_CR1_TE;
        /* enable rx */
        usart_->CR1 = usart_->CR1 | USART_CR1_RE;

        /* enable USART */
        usart_->CR1 = usart_->CR1 | USART_CR1_UE;

        /* enable Rx intterupt */
        usart_->CR1 = usart_->CR1 | USART_CR1_RXNEIE;
        NVIC_EnableIRQ(USART1_IRQn);
    }

    constexpr static void set_baudrate(uint32_t bus_frequency, uint32_t baudrate)
    {
        usart_->BRR = bus_frequency / baudrate;
    }

    constexpr static void write(const char byte)
    {
        wait_for_tx();

        usart_->DR = byte;
        wait_for_tx();
    }

    constexpr static void write(const gsl::span<const uint8_t>& data)
    {
        for (const auto byte : data)
        {
            write(byte);
        }
    }

    constexpr static void write(const std::string_view& data)
    {
        for (const auto byte : data)
        {
            write(byte);
        }
    }

    constexpr static void on_data(const OnDataCallback& callback)
    {
        set_rx(callback);
    }

protected:
    constexpr static void wait_for_tx()
    {
        while (!(usart_->SR & USART_SR_TXE))
        {
        }
    }

    static inline eul::memory_ptr<USART_TypeDef> usart_{base};
};


} // namespace interfaces
} // namespace stm32f1xx
} // namespace hal
