cmake_minimum_required(VERSION 3.9)

set(boards_path "${CMAKE_CURRENT_SOURCE_DIR}/boards")

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ConfigureProject.cmake)

project(EmbeddedHal CXX C ASM)

set(interface_sources_path "${PROJECT_SOURCE_DIR}/interface/hal")

add_library(hal INTERFACE)
target_sources(hal INTERFACE
    ${interface_sources_path}/core/backupRegisters.hpp
    ${interface_sources_path}/core/core.hpp
    ${interface_sources_path}/core/criticalSection.hpp
    ${interface_sources_path}/core/mutex.hpp
    ${interface_sources_path}/memory/eeprom.hpp
    ${interface_sources_path}/time/rtc.hpp
    ${interface_sources_path}/time/sleep.hpp
    ${interface_sources_path}/time/time.hpp
    ${interface_sources_path}/time/watchdog.hpp
    ${interface_sources_path}/utils/assert.hpp
)

target_include_directories(hal INTERFACE
    ${PROJECT_SOURCE_DIR}/interface
)

add_device_hal_library(hal_device_library)

message(STATUS "Link hal with: ${hal_device_library}")
target_link_libraries(hal INTERFACE ${hal_device_library})
