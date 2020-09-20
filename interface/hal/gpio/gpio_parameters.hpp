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

namespace hal
{
namespace gpio
{

enum class Speed
{
    High,
    Medium,
    Low,
    Fast,
    Default
};

enum class Input
{
    Analog,
    Floating,
    PullUpDown
};


enum class Output
{
    OpenDrain,
    PushPull
};

enum class PullUpPullDown
{
    None,
    Up,
    Down
};

enum class Alternate
{
    OpenDrain,
    PushPull
};

constexpr const char* to_string(const Speed& speed)
{
    switch (speed)
    {
        case Speed::High:
            return "High";
        case Speed::Fast:
            return "Fast";
        case Speed::Medium:
            return "Medium";
        case Speed::Low:
            return "Low";
        case Speed::Default:
            return "Default";
    }
    return "Unknown";
}

constexpr const char* to_string(const Input& mode)
{
    switch (mode)
    {
        case Input::Analog:
            return "Analog";
        case Input::Floating:
            return "InputFloating";
        case Input::PullUpDown:
            return "InputPullUpDown";
    }

    return "Unknown";
}

constexpr const char* to_string(const Output& mode)
{
    switch (mode)
    {
        case Output::OpenDrain:
            return "OutputOpenDrain";
        case Output::PushPull:
            return "OutputPushPull";
    }

    return "Unknown";
}

} // namespace gpio
} // namespace hal
