 #include "hal/time/time.hpp"

 #include <cstdint>

 #include <stm32f10x.h>

 namespace hal
 {
 namespace time
 {

 static std::chrono::milliseconds ticks_{0};

 void Time::init()
 {
     /* set SysTick to 1ms */
     SysTick_Config(SystemCoreClock / 1000);
 }

 void Time::increment_time(const std::chrono::milliseconds& time) 
 {
    ticks_ += time;
 }
 
 std::chrono::milliseconds Time::milliseconds()
 {
     return ticks_;
 }

 } // namespace time
 } // namespace hal


 extern "C"
 {
     void SysTick_Handler(void);
 }

 void SysTick_Handler(void)
 {
     hal::time::Time::increment_time(std::chrono::milliseconds(1));
 }
