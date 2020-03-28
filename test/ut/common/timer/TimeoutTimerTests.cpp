#include <gtest/gtest.h>

#include "hal/common/timer/timeout_timer.hpp"
#include "test/stubs/time/TimeStub.hpp"

namespace hal
{
namespace common
{
namespace timer
{

class TimeoutTimerShould : public ::testing::Test
{
};

TEST_F(TimeoutTimerShould, FireAfterTimeout)
{
    stubs::time::TimeStub time;
    time.setTime(std::chrono::milliseconds(10));

    TimeoutTimer timer(time);

    int counter = 0;
    EXPECT_TRUE(timer.start([&counter] { counter += 15; }, std::chrono::milliseconds(161)));

    EXPECT_EQ(counter, 0);
    time.setTime(std::chrono::milliseconds(170));
    timer.run();
    EXPECT_EQ(counter, 0);

    time.setTime(std::chrono::milliseconds(171));
    timer.run();
    EXPECT_EQ(counter, 15);

    time.setTime(std::chrono::milliseconds(3 * 161));
    timer.run();
    EXPECT_EQ(counter, 15);

    EXPECT_TRUE(timer.start(std::chrono::milliseconds(10)));
    EXPECT_FALSE(timer.start(std::chrono::milliseconds(10)));
    time.setTime(std::chrono::milliseconds(4 * 161));
    timer.run();
    EXPECT_EQ(counter, 30);
}

} // namespace timer
} // namespace common
} // namespace hal
