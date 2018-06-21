#pragma once

#include <cstdint>

// TODO: change to function from eul library
#include <functional>


#include "details/utils.hpp"

namespace hal
{
namespace time
{

class Rtc
{
public:
    static Rtc& get();
    static bool wasInitialized();

    void setTime(uint32_t hours, uint32_t minutes, uint32_t seconds);
    void setDate(uint32_t day, uint32_t month, uint32_t year);
    uint32_t getTime();
    uint32_t alarmTime();
    void setAlarm(uint32_t time);
    void fire();
    void setHandler(std::function<void()> handler);
    void setSecondsHandler(std::function<void()> handler);
    std::function<void()>& getSecondsHandler();
    void stop();

private:
    Rtc();
    ~Rtc();
    void init();
    void initNvic();
    void initSecondsInterrupt();
    std::function<void()> timerCallback_;
    std::function<void()> secondsHandler_;
    uint32_t alarmTime_;
    bool alarmEnabled_;
};

} // namespace time
} // namespace hal
