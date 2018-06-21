set(sources_dir ${CMAKE_CURRENT_SOURCE_DIR})

set(sources 
    ${sources_dir}/core/backupRegisters_stm32.cpp
    ${sources_dir}/core/core_stm32.cpp
    ${sources_dir}/core/criticalSection_stm32.cpp
    ${sources_dir}/memory/eeprom_stm32.cpp
    ${sources_dir}/time/rtc_stm32.cpp
    ${sources_dir}/time/sleep_stm32.cpp
    ${sources_dir}/time/time_stm32.cpp
    ${sources_dir}/time/watchdog_stm32.cpp
    ${sources_dir}/utils/assert_stm32.cpp
)

set(sources ${sources} PARENT_SCOPE)