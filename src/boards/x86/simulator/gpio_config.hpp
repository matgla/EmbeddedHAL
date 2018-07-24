#include "hal/gpio/gpio.hpp"
#include "x86/simulator/gpio/x86_gpio.hpp"

using PA0 = hal::gpio::Gpio<hal::x86::simulator::gpio::X86Gpio<0, 0>>;
using PA1 = hal::gpio::Gpio<hal::x86::simulator::gpio::X86Gpio<0, 1>>;