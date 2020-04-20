#pragma once

#include <cstdint>

#include <gsl/span>

#include "stm32f10x.h"
#include "hal/time/sleep.hpp"
#include <stm32f10x_i2c.h>

#include "hal/gpio/digital_input_output_pin.hpp"
#include "arm/stm32/stm32f1xx/gpio/stm32f1xx_gpio.hpp"

namespace hal
{
namespace stm32f1xx
{
namespace interfaces
{

enum class I2C1Mapping
{
    /* SCL - PB6, SDA - PB7 */
    Standard,
    /* SCL -PB8, SDA - PB9 */
    Alternate
};

enum class I2C2Mapping
{
    /* SCL - PB10, SDA - PB11 */
    Standard
};

template <typename SCL, typename SDA>
struct I2CPinout
{
    using SCLPin = SCL;
    using SDAPin = SDA;
};

class I2CCommon
{
public:
    virtual void init() = 0;
    template <typename SCL, typename SDA>
    constexpr static void init()
    {
        SCL::get().init(
            hal::gpio::Output::OutputOpenDrain,
            hal::gpio::Speed::High,
            hal::stm32f1xx::gpio::Function::Alternate);

        SDA::get().init(
            hal::gpio::Output::OutputOpenDrain,
            hal::gpio::Speed::High,
            hal::stm32f1xx::gpio::Function::Alternate);

        RCC->APB1RSTR |= RCC_APB1RSTR_I2C1RST;
        RCC->APB1RSTR &=~RCC_APB1RSTR_I2C1RST;

        I2C_InitTypeDef  I2C_InitStructure;
        I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
        I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
        I2C_InitStructure.I2C_OwnAddress1 = 0x0;
        I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
        I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

        I2C_InitStructure.I2C_ClockSpeed = 400000;
        I2C1->CR1 &= ~I2C_CR1_PE;
        I2C_Init(I2C1, &I2C_InitStructure);
        I2C1->CR1 |= I2C_CR1_PE;
        I2C_Cmd(I2C1, ENABLE);

    }

    bool start(uint8_t address)
    {
        I2C_GenerateSTART(I2C1, ENABLE);
        while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_SB));
        I2C_Send7bitAddress(I2C1, address << 1, I2C_Direction_Transmitter);
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

        // I2C1->CR1 |= I2C_CR1_START;
        // while (!(I2C1->SR1 & I2C_SR1_SB));
        // I2C1->DR = (address) & ~I2C_OAR1_ADD0;

        // while (!(I2C1->SR1 & I2C_SR1_ADDR));
        // I2C1->SR2;

        return true;
    }

    void stop()
    {
        I2C_GenerateSTOP(I2C1, ENABLE);
        while(I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF));
    }

    bool write(uint8_t byte)
    {
        I2C_SendData(I2C1, byte);
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

        return true;
    }

    void write(gsl::span<uint8_t>& data)
    {
        for(auto byte : data)
        {
            write(byte);
        }
    }

    uint8_t read()
    {
        return 0;
    }
};

template <typename SCL, typename SDA, I2C1Mapping>
class I2C_1 : public I2CCommon
{
public:
    void init() override
    {
        RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
        I2CCommon::init<SCL, SDA>();
    }
};

} // namespace interfaces
} // namespace stm32f1xx
} // namespace hal
