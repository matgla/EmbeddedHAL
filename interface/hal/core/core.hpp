#pragma once

namespace hal
{
namespace core
{

class Core
{
public:
    static void initialize_clocks();
    static void initialize_oscillator();
};

} // namespace core
} // namespace hal
