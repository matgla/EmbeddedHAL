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
        case GpioSpeed::Medium:
            return "Medium";
        case GpioSpeed::Low:
            return "Low";
    }
    return "Unknown";
}

constexpr const char* to_string(const GpioMode& mode)
{
    switch (mode)
    {
        case GpioMode::Analog:
            return "Analog";
        case GpioMode::InputFloating:
            return "InputFloating";
        case GpioMode::InputPullDown:
            return "InputPullDown";
        case GpioMode::InputPullUp:
            return "InputPullUp";
        case GpioMode::OutputOpenDrain:
            return "OutputOpenDrain";
        case GpioMode::OutputPushPull:
            return "OutputPushPull";
    }

    return "Unknown";
}

} // namespace gpio
} // namespace hal