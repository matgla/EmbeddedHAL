set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

if (NOT DEFINED linker_script)
    message(FATAL_ERROR "linker_script variable must be defined!")
endif ()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if (${mcu_family} STREQUAL "STM32F10x")
    add_subdirectory(./implementation/arm/common)
    add_subdirectory(./implementation/arm/stm32/common)
    add_subdirectory(./implementation/arm/stm32/stm32f10x)
elseif (${MCU_FAMILY} STREQUAL "X86")
    add_subdirectory(./implementation/x86)
else ()
    message(FATAL_ERROR "Not supported MCU family: ${MCU_FAMILY}")
endif ()