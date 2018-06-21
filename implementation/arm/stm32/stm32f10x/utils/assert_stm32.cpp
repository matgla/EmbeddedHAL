#include "hal/utils/assert.hpp"


namespace hal
{
namespace utils
{

void assertFailed(const char* expr, const char* file, int line, const char* function, const char* msg)
{
#ifndef NDEBUG
    while (true)
    {
    }
#endif
}

} // namespace utils
} // namespace hal