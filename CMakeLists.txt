cmake_minimum_required(VERSION 3.9)
project(EmbeddedHal NONE)

if (HAL_ENABLE_ST)
    set (ENABLE_SEMIHOSTING ON)
endif()

add_subdirectory(src)
add_subdirectory(socs)

enable_language(C CXX ASM)
add_subdirectory(interface/hal/memory)

if (BUILD_UT OR HAL_ENABLE_ST)
    add_subdirectory(test)
endif ()
