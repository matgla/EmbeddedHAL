#include "hal/core/backupRegisters.hpp"

#include <eul/memory_ptr.hpp>

#include <stm32f10x.h>

namespace
{
    constexpr uint16_t register_number_to_address(const uint16_t register_number)
    {
        return (register_number + 1) * 4;
    }

    volatile uint32_t& memory(std::size_t address)
    {
        return *reinterpret_cast<uint32_t*>(address);
    }
}

namespace hal
{
namespace core
{

constexpr uint16_t startup_register = 0;
constexpr uint16_t startup_magic_cookie = 0xbeef;

constexpr uint32_t pwr_offset = (PWR_BASE - PERIPH_BASE);
constexpr uint32_t cr_offset = pwr_offset + 0x00;
constexpr uint32_t dbp_bit_number = 0x08;
constexpr uint32_t cr_dbp_bb = PERIPH_BB_BASE + cr_offset * 32 + dbp_bit_number * 4;
constexpr uint32_t backup_register_base_address = 0x40006c00;

constexpr uint32_t rcc_offset = (RCC_BASE - PERIPH_BASE);
constexpr uint32_t bdcr_offset = (rcc_offset + 0x20);
constexpr uint32_t bdrst_bit_number = 0x10;
constexpr uint32_t bdcr_bdrst_bb = (PERIPH_BB_BASE + (bdcr_offset * 32) + (bdrst_bit_number * 4));

constexpr uint32_t enable_bkp_rcc = 0x08000000;
constexpr uint32_t enable_pwr_rcc = 0x10000000;

uint32_t BackupRegisters::read(uint16_t register_number)
{
    uint32_t address = backup_register_base_address + register_number_to_address(register_number);
    return memory(address);
}

void BackupRegisters::write(const uint16_t register_number, uint16_t value)
{
    /* enable backup register power */
    static constexpr eul::memory_ptr<uint32_t> power_backup_access_register(cr_dbp_bb);
    *power_backup_access_register = 1;
    const uint32_t address = backup_register_base_address + register_number_to_address(register_number);
    const eul::memory_ptr<uint32_t> backup_register(address);
    *backup_register = value;
    *power_backup_access_register = 0;
}

void BackupRegisters::init()
{
    RCC->APB1ENR = RCC->APB1ENR | enable_bkp_rcc;
    RCC->APB1ENR = RCC->APB1ENR | enable_pwr_rcc;
    if (read(startup_register) == startup_magic_cookie)
    {
        reset();
        write(startup_register, startup_magic_cookie);
    }
}

void BackupRegisters::reset()
{
     memory(bdcr_bdrst_bb) = 1;
     memory(bdcr_bdrst_bb) = 0;
}

} // namespace core
} // namespace hal

