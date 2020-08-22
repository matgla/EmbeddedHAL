#include <mstest/mstest.hpp>

#include "hal/time/time.hpp"
#include "hal/time/sleep.hpp"
#include "hal/interrupt/systick.hpp"
#include "hal/common/timer/timer_manager.hpp"
#include "hal/common/timer/timeout_timer.hpp"

MSTEST(TimerShould, RegisterTimeoutTimer)
{
    int call_counter = 0;
    hal::time::Time time;

    static hal::common::timer::TimerManager timer_manager;
    hal::interrupt::set_systick_handler([](std::chrono::milliseconds){
        timer_manager.run();
    });
    hal::interrupt::set_systick_period(std::chrono::milliseconds(1));

    hal::common::timer::TimeoutTimer<hal::time::Time> timeout(time);
    timeout.setCallback([&call_counter]{
        ++call_counter;
    });
    timer_manager.register_timer(timeout);

    mstest::expect_eq(call_counter, 0);
    hal::time::sleep(std::chrono::milliseconds(20));
    mstest::expect_eq(call_counter, 0);
    timeout.start(std::chrono::milliseconds(10));
    hal::time::sleep(std::chrono::milliseconds(5));
    mstest::expect_eq(call_counter, 0);
    hal::time::sleep(std::chrono::milliseconds(10));
    mstest::expect_eq(call_counter, 1);
    hal::time::sleep(std::chrono::milliseconds(15));
    mstest::expect_eq(call_counter, 1);

}
