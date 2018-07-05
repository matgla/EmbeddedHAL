#include <stm32f10x.h>

namespace hal
{
namespace config
{

struct Port
{
    enum
    {
        A = GPIOA,
        B = GPIOB
    };

    struct A
    {
    };

    struct B
    {
    }
};

} // namespace config
} // namespace hal

// using LedPin = Pin<Port::A, PinNumber::0>;


template <typename Port, typename Pin>
struct Gpio
{
};

using LedPin = Gpio<Port::A, Port::A::Pin0>;