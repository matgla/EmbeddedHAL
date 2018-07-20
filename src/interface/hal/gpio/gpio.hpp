#pragma once 

namespace hal
{
namespace gpio
{
    
template <typename T>
concept bool GpioImpl = requires(T a) 
{
    { a.setHigh() } -> void;
    { a.setLow() } -> void;
    { a.setAsInput() } -> void;
    { a.setAsOutput() } -> void;
}
    
template <GpioImpl GpioImplType>
class Gpio
{
public:
    constexpr static void setHigh()
    {
        GpioImplType::setHigh();
    }
    
    constexpr static void setLow()
    {
        GpioImplType::setLow();
    }
    
    constexpr static void setAsInput()
    {
        GpioImplType::setAsInput();
    }
    
    constexpr static void setAsOutput()
    {
        GpioImplType::setAsOutput();    
    }
};
    
} // namespace gpio
} // namespace hal
