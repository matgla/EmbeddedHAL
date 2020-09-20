// This file is part of Embedded HAL project.
// Copyright (C) 2020 Mateusz Stadnik
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <type_traits>
#include <limits>

#include <experimental/type_traits>

#include <stm32f10x.h>

namespace hal
{
namespace interfaces
{
namespace detail
{

template <typename T>
using has_usart1_irq = decltype(T::USART1_IRQn);

template <typename T>
using has_usart2_irq = decltype(T::USART2_IRQn);

template <typename T>
using has_usart3_irq = decltype(T::USART3_IRQn);

template <typename T>
using has_usart4_irq = decltype(T::UART4_IRQn);

template <typename T>
using has_usart5_irq = decltype(T::UART5_IRQn);

template<typename T, int usart_number, typename = void>
struct get_irq {
    static constexpr T value = static_cast<T>(std::numeric_limits<
        std::underlying_type_t<T>>::min());
};

template<typename T, int usart_number>
struct get_irq<T, usart_number, typename std::enable_if_t<
    std::experimental::is_detected_v<has_usart1_irq, T>
    && (1 == usart_number)
>>
{
    static constexpr T value = T::USART1_IRQn;
};

template<typename T, int usart_number>
struct get_irq<T, usart_number, typename std::enable_if_t<
    std::experimental::is_detected_v<has_usart2_irq, T>
    && (2 == usart_number)
>>
{
    static constexpr T value = T::USART2_IRQn;
};

template<typename T, int usart_number>
struct get_irq<T, usart_number, typename std::enable_if_t<
    std::experimental::is_detected_v<has_usart3_irq, T>
    && (3 == usart_number)
>>
{
    static constexpr T value = T::USART3_IRQn;
};

template<typename T, int usart_number>
struct get_irq<T, usart_number, typename std::enable_if_t<
    std::experimental::is_detected_v<has_usart4_irq, T>
    && (4 == usart_number)
>>
{
    static constexpr T value = T::UART4_IRQn;
};

template<typename T, int usart_number>
struct get_irq<T, usart_number, typename std::enable_if_t<
    std::experimental::is_detected_v<has_usart5_irq, T>
    && (5 == usart_number)
>>
{
    static constexpr T value = T::UART5_IRQn;
};

template <typename T, int usart_number>
constexpr static T get_irq_v = get_irq<T, usart_number>::value;

template <uint32_t usart_number>
constexpr uint32_t get_rcc_flag()
{
    if constexpr (usart_number == 1)
    {
        #if defined(RCC_APB2ENR_USART1EN)
        return RCC_APB2ENR_USART1EN;
        #endif
    }

    if constexpr (usart_number == 2)
    {
        #if defined(RCC_APB1ENR_USART2EN)
        return RCC_APB1ENR_USART2EN;
        #endif
    }

    if constexpr (usart_number == 3)
    {
        #if defined(RCC_APB1ENR_USART3EN)
        return RCC_APB1ENR_USART3EN;
        #endif
    }

    if constexpr (usart_number == 4)
    {
        #if defined(RCC_APB1ENR_UART4EN)
        return RCC_APB1ENR_UART4EN;
        #endif
    }

    if constexpr (usart_number == 5)
    {
        #if defined(RCC_APB1ENR_UART5EN)
        return RCC_APB1ENR_UART5EN;
        #endif
    }

    return 0;
};

} // namespace detail
} // namespace interfaces
} // namespace hal
