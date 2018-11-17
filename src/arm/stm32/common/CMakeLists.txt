
set (sources_path ${CMAKE_CURRENT_SOURCE_DIR})

set(sources
    ${sources_path}/stm32_assert.c
    ${sources_path}/stm32_sleep.cpp
    ${sources_path}/stm32_time.cpp
)

add_library(stm32_hal_common ${sources})

target_include_directories(stm32_hal_common
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../../..
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../../interface
        ${CMAKE_BINARY_DIR}/include
)

target_compile_options(stm32_hal_common PUBLIC
    -fno-builtin
    -fdata-sections
    -fdata-sections
    -ffunction-sections
    $<$<CONFIG:DEBUG>:-Og -g>
    $<$<CONFIG:RELEASE>:-Os>
    $<$<COMPILE_LANGUAGE:C>:-std=gnu99 -Wno-implicit-function-declaration>
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++1z -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-threadsafe-statics>
)

target_link_libraries(stm32_hal_common PUBLIC stm32)