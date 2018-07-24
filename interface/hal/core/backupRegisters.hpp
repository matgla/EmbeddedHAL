#pragma once

#include <cstdint>

#include <stm32f10x.h>

namespace hal
{
namespace core
{

class BackupRegisters
{
public:
    static BackupRegisters& get();

    bool isFirstStartup();
    void write(uint16_t registerNumber, uint16_t value);
    void startupDone();

private:
    BackupRegisters();
};

} // namespace core
} // namespace hal