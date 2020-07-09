#pragma once

#include <cstdint>

#include <gsl/span>

#include <eul/function.hpp>

#include <misc.h>
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_dma.h"
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

void set_dma_callback(const eul::function<void(), sizeof(void*)>& callback);

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
    I2CCommon() : waiting_for_dma_write_(false)
    {

    }

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

        RCC->APB1RSTR = RCC->APB1RSTR | RCC_APB1RSTR_I2C1RST;
        RCC->APB1RSTR = RCC->APB1RSTR & (~RCC_APB1RSTR_I2C1RST);

        I2C_InitTypeDef  I2C_InitStructure;
        I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
        I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
        I2C_InitStructure.I2C_OwnAddress1 = 0x0;
        I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
        I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

        I2C_InitStructure.I2C_ClockSpeed = 1000000;
        I2C1->CR1 = I2C1->CR1 & (~I2C_CR1_PE);
        I2C_Init(I2C1, &I2C_InitStructure);
        I2C1->CR1 = I2C1->CR1 | I2C_CR1_PE;
        I2C_Cmd(I2C1, ENABLE);
    }

    void initialize_dma(void* buffer)
    {
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
        DMA_DeInit(DMA1_Channel6);
        DMA_InitTypeDef dma_config_;
        dma_config_.DMA_PeripheralBaseAddr = (uint32_t)&(I2C1->DR);
        dma_config_.DMA_DIR = DMA_DIR_PeripheralDST;
        dma_config_.DMA_MemoryBaseAddr = (uint32_t)buffer;
        dma_config_.DMA_BufferSize = 1024;
        dma_config_.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
        dma_config_.DMA_MemoryInc = DMA_MemoryInc_Enable;
        dma_config_.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
        dma_config_.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
        dma_config_.DMA_Mode = DMA_Mode_Normal;
        dma_config_.DMA_Priority = DMA_Priority_High;
        dma_config_.DMA_M2M = DMA_M2M_Disable;
        DMA_Init(DMA1_Channel6, &dma_config_);
        NVIC_InitTypeDef nvicStructure;
        nvicStructure.NVIC_IRQChannel = DMA1_Channel6_IRQn;
        nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
        nvicStructure.NVIC_IRQChannelSubPriority = 1;
        nvicStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&nvicStructure);
        set_dma_callback([this]()
        {
            stop();
            waiting_for_dma_write_ = false;
        });
    }

    bool start(uint8_t address)
    {
        while (waiting_for_dma_write_);

        I2C_GenerateSTART(I2C1, ENABLE);
        while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_SB));
        I2C_Send7bitAddress(I2C1, address << 1, I2C_Direction_Transmitter);
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

        return true;
    }

    void stop()
    {
        I2C_GenerateSTOP(I2C1, ENABLE);
        while(I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF));
    }

    bool write(uint8_t byte)
    {
        while (waiting_for_dma_write_);

        I2C_SendData(I2C1, byte);
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

        return true;
    }

    void write(gsl::span<uint8_t>& data)
    {
        while (waiting_for_dma_write_);

        for(auto byte : data)
        {
            write(byte);
        }
    }

    void dma_write(uint32_t size)
    {
        while (waiting_for_dma_write_);
        waiting_for_dma_write_ = true;
        DMA1_Channel6->CNDTR = size;
        I2C_DMACmd(I2C1, ENABLE);
        DMA_Cmd(DMA1_Channel6, ENABLE);
        DMA_ClearITPendingBit(DMA1_IT_TC6);
        DMA_ITConfig(DMA1_Channel6, DMA_IT_TC, ENABLE);
    }

    uint8_t read()
    {
        return 0;
    }

    bool busy()
    {
        return waiting_for_dma_write_;
    }

private:
    volatile bool waiting_for_dma_write_;
};

template <typename SCL, typename SDA, I2C1Mapping>
class I2C_1 : public I2CCommon
{
public:
    void init() override
    {
        RCC->APB1ENR = RCC->APB1ENR | RCC_APB1ENR_I2C1EN;
        I2CCommon::init<SCL, SDA>();
    }
};

} // namespace interfaces
} // namespace stm32f1xx
} // namespace hal

