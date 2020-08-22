#include <mstest/mstest.hpp>

#include "hal/interrupt/pendsv.hpp"

class PendSvShould : public mstest::Test
{
public:
    void setup() override
    {

    }

    void teardown() override
    {
        hal::interrupt::set_pendsv_handler([]{});
    }
};

MSTEST_F(PendSvShould, RegisterAndCallHandler)
{
    static int was_called = 0;
    hal::interrupt::set_pendsv_handler([]{
        was_called = 23123;
    });

    hal::interrupt::trigger_pendsv();
    mstest::expect_eq(was_called, 23123);

}
