#pragma once

#include "hal/gpio/digital_input_output_pin.hpp"

#include <eul/utils/unused.hpp>

#include <atomic>

namespace hal
{
namespace gpio
{

class X86CommonGpio
{
public:
    void init(hal::gpio::Input input)
    {
        UNUSED1(input);
    }

    void setHigh()
    {
        is_high_ = true;
    }

    void setLow()
    {
        is_high_ = false;
    }

    bool read()
    {
        return is_high_;
    }

    std::atomic<bool> is_high_ = true;
};

template <int id>
class X86ButtonFactory : public X86CommonGpio
{
public:
    static X86CommonGpio& get()
    {
        static X86ButtonFactory<id> a;
        return a;
    }
private:
    X86ButtonFactory() = default;
};


} // namespace gpio
} // namespace hal
