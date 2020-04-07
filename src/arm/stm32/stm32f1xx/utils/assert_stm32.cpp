#include "hal/utils/assert.hpp"

#include <eul/utils/unused.hpp>

namespace hal
{
namespace utils
{

void assertFailed(const char* expr, const char* file, int line, const char* function, const char* msg)
{
    UNUSED5(expr, file, line, function, msg);
#ifndef NDEBUG
    while (true)
    {
    }
#endif
}

} // namespace utils
} // namespace hal
