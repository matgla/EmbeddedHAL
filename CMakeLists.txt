cmake_minimum_required(VERSION 3.9)
project(EmbeddedHal NONE)

if (HAL_ENABLE_ST)
    set (ENABLE_SEMIHOSTING ON)
endif()

add_subdirectory(socs)
add_subdirectory(src)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} PARENT_SCOPE)

string (TOLOWER "${arch}" arch_l)
string (TOLOWER "${mcu}" mcu_l)
string (TOLOWER "${vendor}" vendor_l)
string (TOLOWER "${family}" family_l)
#target_include_directories(stm32 PUBLIC ${PROJECT_SOURCE_DIR}/socs/${arch_l}/${vendor_l}/${family_l}/${mcu_l})
enable_language(C CXX ASM)
add_subdirectory(interface/hal)
add_subdirectory(interface/hal/memory)

if (BUILD_UT OR HAL_ENABLE_ST)
    add_subdirectory(test)
endif ()
