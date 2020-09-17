#pragma once

#include "hal/gpio/gpio_parameters.hpp"

namespace hal
{
namespace gpio
{

// template <class T>
// concept Semiregular = DefaultConstructible<T> &&
//     CopyConstructible<T> && Destructible<T> && CopyAssignable<T> &&
// requires(T a, size_t n) {
//     requires Same<T*, decltype(&a)>;  // nested: "Same<...> evaluates to true"
//     { a.~T() } noexcept;  // compound: "a.~T()" is a valid expression that doesn't throw
//     requires Same<T*, decltype(new T)>; // nested: "Same<...> evaluates to true"
//     requires Same<T*, decltype(new T[n])>; // nested
//     { delete new T };  // compound
//     { delete new T[n] }; // compound
// };

class DigitalOutputPin
{
public:
    virtual ~DigitalOutputPin() = default;
    virtual void init(Output mode, Speed speed) = 0;
    virtual void set_high() = 0;
    virtual void set_low() = 0;
};

} // namespace gpio
} // namespace hal
