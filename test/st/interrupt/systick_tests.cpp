#include <mstest/mstest.hpp>

#include <cstdio>

#include "hal/interrupt/systick.hpp"
#include "hal/time/sleep.hpp"

class SystickShould : public mstest::Test
{
    void setup() override
    {
        hal::interrupt::reset_ticks_counter();
    }

    void teardown() override
    {
        hal::interrupt::reset_systick_handler();
    }
};

MSTEST_F(SystickShould, CallHandler)
{
    static int counter = 0;
    hal::interrupt::set_systick_handler([](std::chrono::milliseconds ms) {
        ++counter;
    });
    hal::interrupt::set_systick_period(std::chrono::milliseconds(1));
    hal::interrupt::reset_ticks_counter();
    hal::time::sleep(std::chrono::milliseconds(5));
    mstest::expect_gt(counter, 0);
    mstest::expect_lt(counter, 6);
}

MSTEST_F(SystickShould, ChangePeriod)
{
    static int counter = 0;

    hal::interrupt::set_systick_period(std::chrono::milliseconds(2));
    hal::interrupt::set_systick_handler([](std::chrono::milliseconds ms) {
        ++counter;
    });
    hal::interrupt::reset_ticks_counter();
    hal::time::sleep(std::chrono::milliseconds(6));
    mstest::expect_gt(counter, 0);
    mstest::expect_lt(counter, 5);
}

MSTEST_F(SystickShould, ResetHandler)
{
    static int counter = 0;

    hal::interrupt::set_systick_period(std::chrono::milliseconds(2));
    hal::interrupt::set_systick_handler([](std::chrono::milliseconds ms) {
        ++counter;
    });
    hal::interrupt::reset_ticks_counter();
    hal::interrupt::reset_systick_handler();
    counter = 0;
    hal::time::sleep(std::chrono::milliseconds(6));
    mstest::expect_eq(counter, 0);
}

MSTEST_F(SystickShould, CallHandlerWithCorrectTime)
{
    static int counter = 0;
    static int old = 0;

    hal::interrupt::set_systick_period(std::chrono::milliseconds(10));
    hal::interrupt::set_systick_handler([](std::chrono::milliseconds ms) {
        mstest::expect_ge(ms.count() - old, 8);
        mstest::expect_le(ms.count() - old, 12);
        old = ms.count();
    });
    hal::interrupt::reset_ticks_counter();
    counter = 0;
    hal::time::sleep(std::chrono::milliseconds(6));
    mstest::expect_eq(counter, 0);
}
