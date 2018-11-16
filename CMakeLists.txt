
cmake_minimum_required(VERSION 3.9)

if (DEFINED STANDALONE)
    project(EmbeddedHal CXX C ASM)
    include(cmake/ConfigureProject.cmake)
endif ()

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

set(includes_dir "${CMAKE_CURRENT_SOURCE_DIR}/interface/hal")

set(hal_interface
    ${CMAKE_CURRENT_SOURCE_DIR}/src/details/utils.hpp
    ${includes_dir}/core/backupRegisters.hpp
    ${includes_dir}/core/core.hpp
    ${includes_dir}/core/criticalSection.hpp
    ${includes_dir}/core/mutex.hpp
    ${includes_dir}/memory/eeprom.hpp
    ${includes_dir}/time/rtc.hpp
    ${includes_dir}/time/sleep.hpp
    ${includes_dir}/time/time.hpp
    ${includes_dir}/time/watchdog.hpp
    ${includes_dir}/utils/assert.hpp

    CACHE STRING "Hal interface sources"
)

if (${mcu_family} STREQUAL "STM32F10x")
    add_subdirectory(./src/arm/stm32/stm32f10x)
elseif (${mcu_family} STREQUAL "X86")
    add_subdirectory(./src/x86)
else ()
    message(FATAL_ERROR "Not supported MCU family: ${MCU_FAMILY}")
endif ()


