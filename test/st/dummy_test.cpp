#include <mstest/mstest.hpp>
#include <mstest/expectations.hpp>

#include <cstring>

MSTEST(Embedded, ARMv7HelloWorld)
{
    mstest::expect_eq(11, strlen("Hello World"));
}

