#include "hal/time/time.hpp"

#include <util/delay.h>

namespace hal
{
namespace time
{

void sleep(std::chrono::milliseconds time)
{
    for (int current = 0; current < time.count(); ++current)
    {
        _delay_ms(1);
    }
}

void sleep(std::chrono::seconds time)
{
    sleep(std::chrono::duration_cast<std::chrono::milliseconds>(time));
}

} // namespace time
} // namespace hal
