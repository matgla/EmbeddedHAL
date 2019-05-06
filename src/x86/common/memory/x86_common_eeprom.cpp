#include "hal/memory/eeprom.hpp"

#include <optional>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

namespace hal
{
namespace memory
{

namespace
{

static std::map<std::size_t, uint32_t> memory;
static bool was_initialized = false;

void store_to_file()
{
    std::ofstream file("eeprom.cache");
    for (auto& data : memory)
    {
        file << "0x" << std::hex << data.first << ": 0x" << std::hex << data.second << std::endl;
    }
    file.close();
}

uint32_t get_hex(const std::string& hexstr) {
    return (uint32_t)strtol(hexstr.c_str(), 0, 16);
}

void initialize_from_file()
{
    std::ifstream file("eeprom.cache");
    while (file.good())
    {
        std::string line;
        std::getline(file, line);

        auto delimiter = line.find(":");
        auto address_str = line.substr(0, delimiter);
        auto value_str = line.substr(delimiter + 1, line.size());
        memory[get_hex(address_str)] = get_hex(value_str);
    }

    file.close();
    was_initialized = true;
}

}

void Eeprom::write_u32(std::size_t address, uint32_t value)
{
    if (!was_initialized)
    {
        initialize_from_file();
    }
    memory[address] = value;
    store_to_file();
}

void Eeprom::write_u16(std::size_t address, uint16_t value)
{
    write_u32(address, value);
}

void Eeprom::write_u8(std::size_t address, uint8_t value)
{
    write_u32(address, value);
}

std::optional<uint32_t> Eeprom::read(std::size_t address)
{
    if (!was_initialized)
    {
        initialize_from_file();
    }

    if (memory.count(address))
    {
        return memory[address];
    }

    return std::optional<uint32_t>{};
}

} // namespace memory
} // namespace hal
