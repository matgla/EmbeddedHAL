#include <mstest/mstest.hpp>

#include <cstdio>

#include "hal/interrupt/systick.hpp"
#include "hal/time/sleep.hpp"


MSTEST(SystickShould, CallHandler)
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
    // TODO: Add support for SetUp and TearDown
    hal::interrupt::reset_systick_handler();
}

MSTEST(SystickShould, ChangePeriod)
{
    mstest::expect_eq(1, 2); mstest::expect_eq(2, 3);
//     static int counter = 0;

//     hal::interrupt::set_systick_period(std::chrono::milliseconds(2));
//     hal::interrupt::set_systick_handler([](std::chrono::milliseconds ms) {
//         ++counter;
//     });
//     hal::interrupt::reset_ticks_counter();
//     hal::time::sleep(std::chrono::milliseconds(6));
//     EXPECT_GT(counter, 0);
//     EXPECT_LT(counter, 5);
//     hal::interrupt::reset_systick_handler();
// }

// NANOTEST(SystickShould, ResetHandler)
// {
//     static int counter = 0;

//     hal::interrupt::set_systick_period(std::chrono::milliseconds(2));
//     hal::interrupt::set_systick_handler([](std::chrono::milliseconds ms) {
//         ++counter;
//     });
//     hal::interrupt::reset_ticks_counter();
//     hal::interrupt::reset_systick_handler();
//     counter = 0;
//     hal::time::sleep(std::chrono::milliseconds(6));
//     EXPECT_EQ(counter, 0);
}

// NANOTEST(SystickShould, CallHandlerWithCorrectTime)
// {
//     static int counter = 0;
//     static int old = 0;

//     hal::interrupt::set_systick_period(std::chrono::milliseconds(10));
//     hal::interrupt::set_systick_handler([](std::chrono::milliseconds ms) {
//         EXPECT_GE(ms.count() - old, 8);
//         EXPECT_LE(ms.count() - old, 12);
//         old = ms.count();
//     });
//     hal::interrupt::reset_ticks_counter();
//     counter = 0;
//     hal::time::sleep(std::chrono::milliseconds(6));
//     EXPECT_EQ(counter, 0);
//     hal::interrupt::reset_systick_handler();
// }
