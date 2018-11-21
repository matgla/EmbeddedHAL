
cmake_minimum_required(VERSION 3.9)

set(boards_path "${CMAKE_CURRENT_SOURCE_DIR}/boards")

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ConfigureProject.cmake)

project(EmbeddedHal CXX C ASM)

set(includes_dir "${PROJECT_SOURCE_DIR}/interface/hal")

add_library(hal_interface INTERFACE)
target_sources(hal_interface INTERFACE
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
)

target_include_directories(hal_interface INTERFACE 
    ${PROJECT_SOURCE_DIR}/interface
)

if (${mcu_family} STREQUAL "STM32F1xx")
    add_subdirectory(./src/arm/stm32/common)
    add_subdirectory(./src/arm/stm32/stm32f10x)
elseif (${mcu_family} STREQUAL "X86")
    add_subdirectory(./src/x86)
else ()
    message(FATAL_ERROR "Not supported MCU family: ${MCU_FAMILY}")
endif ()


