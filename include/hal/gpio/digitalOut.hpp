#pragma once

namespace hal
{
namespace gpio
{

enum class Port
{
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H
};

using Pin = int;

class DigitalOut
{
public:
    constexpr DigitalOut(const Port port, const Pin pin);

    constexpr void high() const;
    constexpr void low() const;

private:
    const Pin pin_;
    const Port port_;
};

} // namespace gpio
} // namespace hal
