#include <nanotest.h>

#include <cstring>

NANOTEST(Embedded, ARMv7HelloWorld)
{
    EXPECT_EQ(11, strlen("Hello World"));
}

