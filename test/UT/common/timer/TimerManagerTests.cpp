#include <chrono>

#include <gtest/gtest.h>

#include "hal/common/timer/timeout_timer.hpp"
#include "hal/common/timer/timer_manager.hpp"

#include "test/stubs/time/TimeStub.hpp"

namespace hal
{
namespace common
{
namespace timer
{

class TimerManagerShould : public ::testing::Test
{
};

TEST_F(TimerManagerShould, RegisterTimers)
{
    stubs::time::TimeStub time;
    time.setTime(std::chrono::seconds(0));

    int counter = 0;
    bool called = false;
    TimerManager sut;
    TimeoutTimer timer(time);
    TimeoutTimer timer2(time);

    timer.start(
        [&counter]() {
            counter++;
        },
        std::chrono::milliseconds(10));

    timer2.start(
        [&called] { called = true; },
        std::chrono::seconds(2));

    sut.register_timer(timer);
    sut.register_timer(timer2);

    EXPECT_EQ(counter, 0);
    sut.run();
    EXPECT_EQ(counter, 0);
    time.setTime(std::chrono::seconds(1));
    sut.run();
    EXPECT_EQ(counter, 1);
    EXPECT_FALSE(called);
    time.setTime(std::chrono::seconds(3));

    sut.run();
    EXPECT_EQ(counter, 1);
    EXPECT_TRUE(called);
}

TEST_F(TimerManagerShould, AutomaticallyDeregisterDeadTimers)
{
    stubs::time::TimeStub time;
    time.setTime(std::chrono::seconds(0));

    int counter = 0;
    bool called = false;
    TimerManager sut;
    TimeoutTimer timer(time);


    timer.start(
        [&counter]() {
            counter++;
        },
        std::chrono::milliseconds(10));

    sut.register_timer(timer);

    {
        TimeoutTimer timer2(time);
        timer2.start(
            [&called] { called = true; },
            std::chrono::seconds(2));

        sut.register_timer(timer2);
    }
    time.setTime(std::chrono::seconds(3));

    sut.run();
    EXPECT_EQ(counter, 1);
    EXPECT_FALSE(called);
}

TEST_F(TimerManagerShould, DeregisterTimer)
{
    stubs::time::TimeStub time;
    time.setTime(std::chrono::seconds(0));

    int counter = 0;
    bool called = false;
    TimerManager sut;
    TimeoutTimer timer(time);


    timer.start(
        [&counter]() {
            counter++;
        },
        std::chrono::milliseconds(10));

    sut.register_timer(timer);

    TimeoutTimer timer2(time);
    timer2.start(
        [&called] { called = true; },
        std::chrono::seconds(2));

    sut.register_timer(timer2);

    time.setTime(std::chrono::seconds(3));

    sut.deregister_timer(timer);
    sut.run();
    EXPECT_EQ(counter, 0);
    EXPECT_TRUE(called);
}

} // namespace timer
} // namespace common
} // namespace hal
