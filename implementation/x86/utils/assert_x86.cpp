#include "hal/utils/assert.hpp"

#include <cstdlib>

namespace hal
{
namespace utils
{

void assertFailed(const char* expr, const char* file, int line, const char* function, const char* msg)
{
#ifndef NDEBUG
    std::abort();
#endif
}

} // namespace utils
} // namespace hal