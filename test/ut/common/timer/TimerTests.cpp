#include <gtest/gtest.h>

#include "hal/common/timer/timer.hpp"
#include "test/stubs/time/TimeStub.hpp"

namespace hal
{
namespace common
{
namespace timer
{

template <typename TimeProviderType>
class TimerStub : public Timer<TimeProviderType>
{
public:
    using CallbackType = typename Timer<TimeProviderType>::CallbackType;
    TimerStub(const CallbackType& callback, const TimeProviderType& time)
        : Timer<TimeProviderType>::Timer(callback, time)
    {
    }

    const std::chrono::milliseconds& getStartTime() const
    {
        return this->start_time_;
    }

    const std::chrono::milliseconds& getEndTime() const
    {
        return this->end_time_;
    }

    const TimeProviderType& getTimeProvider() const
    {
        return this->time_provider_;
    }

    const CallbackType& getCallback() const
    {
        return this->callback_;
    }

    void run() override
    {
        this->fire();
    }
};

class TimerShould : public ::testing::Test
{
};

TEST_F(TimerShould, InitializeTimerCorrectly)
{
    int counter = 0;
    stubs::time::TimeStub time;

    const TimerStub timer([&counter]() { counter++; }, time);

    EXPECT_EQ(counter, 0);
    timer.getCallback()();
    EXPECT_EQ(counter, 1);

    EXPECT_EQ(timer.getStartTime(), std::chrono::milliseconds(0));
    EXPECT_EQ(timer.getEndTime(), std::chrono::milliseconds(0));
    EXPECT_EQ(&timer.getTimeProvider(), &time);
}

TEST_F(TimerShould, SetParametersOnStart)
{
    int counter = 0;
    stubs::time::TimeStub time;
    time.setTime(std::chrono::milliseconds(10));

    TimerStub timer([&counter]() { counter++; }, time);

    EXPECT_EQ(counter, 0);
    timer.getCallback()();
    EXPECT_EQ(counter, 1);

    EXPECT_TRUE(timer.start(std::chrono::milliseconds(5)));
    EXPECT_EQ(timer.getStartTime(), std::chrono::milliseconds(10));
    EXPECT_EQ(timer.getEndTime(), std::chrono::milliseconds(15));
    EXPECT_EQ(&timer.getTimeProvider(), &time);
}

TEST_F(TimerShould, SetParametersWithCallbackOnStart)
{
    int counter = 0;
    stubs::time::TimeStub time;
    time.setTime(std::chrono::milliseconds(10));

    TimerStub timer([&counter]() { counter++; }, time);

    EXPECT_EQ(counter, 0);
    timer.getCallback()();
    EXPECT_EQ(counter, 1);

    int counter2 = 0;
    EXPECT_TRUE(timer.start([&counter2]() { counter2 += 10; }, std::chrono::milliseconds(5)));

    timer.getCallback()();
    EXPECT_EQ(counter2, 10);
    EXPECT_EQ(counter, 1);

    EXPECT_EQ(timer.getStartTime(), std::chrono::milliseconds(10));
    EXPECT_EQ(timer.getEndTime(), std::chrono::milliseconds(15));
    EXPECT_EQ(&timer.getTimeProvider(), &time);
}

TEST_F(TimerShould, NotSetParametersOnStartWhenStateIsRunning)
{
    int counter = 0;
    stubs::time::TimeStub time;
    time.setTime(std::chrono::milliseconds(10));

    TimerStub timer([&counter]() { counter++; }, time);

    EXPECT_EQ(counter, 0);
    timer.getCallback()();
    EXPECT_EQ(counter, 1);

    EXPECT_TRUE(timer.start(std::chrono::milliseconds(5)));
    ++time;
    EXPECT_FALSE(timer.start(std::chrono::milliseconds(17)));

    EXPECT_EQ(timer.getStartTime(), std::chrono::milliseconds(10));
    EXPECT_EQ(timer.getEndTime(), std::chrono::milliseconds(15));
    EXPECT_EQ(&timer.getTimeProvider(), &time);
}

TEST_F(TimerShould, NotSetParametersWithCallbackOnStartWhenStateIsRunning)
{
    int counter = 0;
    stubs::time::TimeStub time;
    time.setTime(std::chrono::milliseconds(10));

    TimerStub timer([&counter]() { counter++; }, time);

    EXPECT_EQ(counter, 0);
    timer.getCallback()();
    EXPECT_EQ(counter, 1);

    int counter2 = 0;
    EXPECT_TRUE(timer.start([&counter2]() { counter2 += 10; }, std::chrono::milliseconds(5)));
    ++time;
    EXPECT_FALSE(timer.start(std::chrono::milliseconds(17)));

    timer.getCallback()();
    EXPECT_EQ(counter2, 10);
    EXPECT_EQ(counter, 1);

    EXPECT_EQ(timer.getStartTime(), std::chrono::milliseconds(10));
    EXPECT_EQ(timer.getEndTime(), std::chrono::milliseconds(15));
    EXPECT_EQ(&timer.getTimeProvider(), &time);
}

TEST_F(TimerShould, InvokeCallbackInRunningState)
{
    int counter = 0;
    stubs::time::TimeStub time;
    time.setTime(std::chrono::milliseconds(10));

    TimerStub timer([&counter]() { counter++; }, time);

    EXPECT_EQ(counter, 0);
    timer.run();
    EXPECT_EQ(counter, 1);
}

TEST_F(TimerShould, NotInvokeCallbackInIdleState)
{
    int counter = 0;
    stubs::time::TimeStub time;
    time.setTime(std::chrono::milliseconds(10));

    TimerStub timer([&counter]() { counter++; }, time);
    timer.start(std::chrono::seconds(1));
    EXPECT_EQ(timer.getEndTime(), std::chrono::milliseconds(1010));
    EXPECT_EQ(counter, 0);
    timer.run();
    EXPECT_EQ(counter, 1);
}

} // namespace timer
} // namespace common
} // namespace hal
