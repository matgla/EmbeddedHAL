#pragma once

namespace hal
{
namespace gpio
{

enum class GpioSpeed
{
    High,
    Medium,
    Low
};

enum class GpioMode
{
    Analog,
    InputFloating,
    InputPullDown,
    InputPullUp,
    OutputOpenDrain,
    OutputPushPull
};

constexpr const char* to_string(const GpioSpeed& speed)
{
    switch (speed)
    {
        case GpioSpeed::High:
            return "High";
    }
}

constexpr const char* to_string(const GpioMode& mode)
{
    switch (mode)
    {
        case GpioMode::Analog:
            return "Analog";
    }
}

} // namespace gpio
} // namespace hal