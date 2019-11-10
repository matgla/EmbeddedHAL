#pragma once

#include <cstdint>

namespace hal
{
namespace core
{

class BackupRegisters
{
public:
    static void init();
    constexpr static bool isFirstStartup();
    constexpr static void write(uint16_t registerNumber, uint16_t value);
    constexpr static void startupDone();
    constexpr static uint32_t read(uint16_t registerNumber);

};

} // namespace core
} // namespace hal

#include <stm32f10x.h>


#define STARTUP_REGISTER 1 
#define STARTUP_MAGIC_COOKIE 0xBEEF

#define PWR_OFFSET (PWR_BASE - PERIPH_BASE)

#define CR_OFFSET (PWR_OFFSET + 0x00)
#define DBP_BitNumber 0x08
#define CR_DBP_BB  (PERIPH_BB_BASE + (CR_OFFSET * 32) + (DBP_BitNumber * 4))

#define RCC_OFFSET (RCC_BASE - PERIPH_BASE)
#define BDCR_OFFSET (RCC_OFFSET + 0x20)
#define BDRST_BitNumber 0x10
#define BDCR_BDRST_BB (PERIPH_BB_BASE + (BDCR_OFFSET * 32) + (BDRST_BitNumber * 4))

namespace 
{
    constexpr uint16_t numberToRegister(const uint16_t reg)
    {
        switch (reg)
        {
            case 1: return 0x0008;
            case 2: return 0x000c;
            case 3: return 0x0010;
        }
        return 0x0004; 
    }
}

namespace hal
{
namespace core
{

constexpr bool BackupRegisters::isFirstStartup()
{
    return read(STARTUP_REGISTER) != STARTUP_MAGIC_COOKIE;
}

constexpr void BackupRegisters::write(u16 registerNumber, u16 value)
{
    /* enable backup register power */
    *reinterpret_cast<uint32_t*>(CR_DBP_BB) = 1;
    const uint32_t address = 0x40006c00 + numberToRegister(registerNumber);
    *reinterpret_cast<uint32_t*>(address) = value;
    *reinterpret_cast<uint32_t*>(CR_DBP_BB) = 0;
}

constexpr uint32_t BackupRegisters::read(uint16_t registerNumber)
{
    const uint32_t address = 0x40006c00 + numberToRegister(registerNumber);
    return *reinterpret_cast<uint16_t*>(address);
}

constexpr void BackupRegisters::startupDone()
{
    if (isFirstStartup())
    {
        write(STARTUP_REGISTER, STARTUP_MAGIC_COOKIE);
    }
}

void BackupRegisters::init()
{
    RCC->APB1ENR |= 0x08000000; // bkp 
    RCC->APB1ENR |= 0x10000000; // pwr
    if (isFirstStartup())
    {
       *(uint32_t*) BDCR_BDRST_BB = 1;
       *(uint32_t*) BDCR_BDRST_BB = 0;
    }
}


} // namespace hal
}
