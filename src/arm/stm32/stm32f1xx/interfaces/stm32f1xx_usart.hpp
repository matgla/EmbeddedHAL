
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

template <std::size_t usart_address>
class UsartCommon : public hal::interfaces::Usart
{
public:
    using OnDataCallback = hal::interfaces::Usart::OnDataCallback;
    using StreamType = gsl::span<const uint8_t>;

    template <typename RxPin, typename TxPin>
    constexpr void init(uint32_t bus_frequency, uint32_t baudrate)
    {
        TxPin::Implementation::init(hal::gpio::Output::OutputPushPull,
                                    hal::gpio::Speed::Medium,
                                    hal::stm32f1xx::gpio::Function::Alternate);
        RxPin::init(hal::gpio::Input::InputFloating);

        set_baudrate(bus_frequency, baudrate);
        /* enable tx */
        usart_->CR1 |= USART_CR1_TE;
        /* enable rx */
        usart_->CR1 |= USART_CR1_RE;

        /* enable USART */
        usart_->CR1 |= USART_CR1_UE;

        /* enable Rx intterupt */
        usart_->CR1 |= USART_CR1_RXNEIE;
        NVIC_EnableIRQ(USART1_IRQn);
        was_initialized = true;
    }


    void set_baudrate(uint32_t bus_frequency, uint32_t baudrate)
    {
        usart_->BRR = bus_frequency / baudrate;
    }

    void write(const char byte)
    {
        wait_for_tx();

        if (!was_initialized)
        {
            return;
        }
        usart_->DR = byte;
        wait_for_tx();
    }

    void write(const gsl::span<const uint8_t>& data) override
    {
        for (const auto byte : data)
        {
            write(byte);
        }
    }

    void write(const std::string_view& data) override
    {
        for (const auto byte : data)
        {
            write(byte);
        }
    }

    void on_data(const OnDataCallback& callback) override
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

    inline static bool was_initialized = false;
    constexpr static eul::memory_ptr<USART_TypeDef> usart_ = eul::memory_ptr<USART_TypeDef>(usart_address);
};

template <typename Rx, typename Tx, Usart1Mapping mapping>
class Usart1 : public UsartCommon<USART1_BASE>
{
public:
    using TxPin = Tx;
    using RxPin = Rx;
    void init(uint32_t baudrate) override
    {
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

        UsartCommon<USART1_BASE>::init<RxPin, TxPin>(hal::stm32f1xx::clock::Clock::get_core_clock(), baudrate);
    }

    void set_baudrate(uint32_t baudrate) override
    {
        UsartCommon<USART1_BASE>::set_baudrate(hal::stm32f1xx::clock::Clock::get_core_clock(), baudrate);
    }
};


} // namespace interfaces
} // namespace stm32f1xx
} // namespace hal
