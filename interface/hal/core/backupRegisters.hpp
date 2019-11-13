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
    static void write(uint16_t registerNumber, uint16_t value);
    static uint32_t read(uint16_t registerNumber);
    static void reset();
};

} // namespace core
} // namespace hal

