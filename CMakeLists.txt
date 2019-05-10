cmake_minimum_required(VERSION 3.9)

message (STATUS "Configuring HAL")

if (BUILD_UT)
    message (STATUS "Configuring HAL for UT")
    set (BOARD "x86_mock" CACHE STRING "Board name" FORCE)
endif ()

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
    ${interface_sources_path}/common/timer/interval_timer.hpp
    ${interface_sources_path}/common/timer/ITimer.hpp
    ${interface_sources_path}/common/timer/observed_timer.hpp
    ${interface_sources_path}/common/timer/timeout_timer.hpp
    ${interface_sources_path}/common/timer/timer_manager.hpp
    ${interface_sources_path}/common/timer/timer.hpp
)

target_include_directories(hal INTERFACE
    ${PROJECT_SOURCE_DIR}/interface
)

add_subdirectory(src/common)
add_subdirectory(lib)
add_subdirectory(interface/hal/memory)

add_device_hal_library(hal_device_library)

message(STATUS "Link hal with: ${hal_device_library}")

target_link_libraries(hal
    INTERFACE
        ${hal_device_library}
        hal_memory
        hal_common
        eul
)

if (BUILD_UT)
    add_subdirectory(test)
endif ()
