#pragma once

namespace hal
{
namespace gpio
{

enum class Speed
{
    High,
    Medium,
    Low,
    Default
};

enum class Input
{
    Analog,
    InputFloating,
    InputPullUpDown
};


enum class Output
{
    OutputOpenDrain,
    OutputPushPull
};

constexpr const char* to_string(const Speed& speed)
{
    switch (speed)
    {
        case Speed::High:
            return "High";
        case Speed::Medium:
            return "Medium";
        case Speed::Low:
            return "Low";
    }
    return "Unknown";
}

constexpr const char* to_string(const Input& mode)
{
    switch (mode)
    {
        case Input::Analog:
            return "Analog";
        case Input::InputFloating:
            return "InputFloating";
        case Input::InputPullUpDown:
            return "InputPullUpDown";
    }

    return "Unknown";
}

constexpr const char* to_string(const Output& mode)
{
    switch (mode)
    {
        case Output::OutputOpenDrain:
            return "OutputOpenDrain";
        case Output::OutputPushPull:
            return "OutputPushPull";
    }

    return "Unknown";
}

} // namespace gpio
} // namespace hal