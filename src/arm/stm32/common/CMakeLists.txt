
set (sources_path ${CMAKE_CURRENT_SOURCE_DIR})

set(sources 
    ${sources_path}/stm32_assert.c
)

add_library(stm32_hal_common ${sources})

target_compile_options(stm32_hal_common PUBLIC
    -fno-builtin
    -fdata-sections
    -fdata-sections 
    -ffunction-sections
    $<$<COMPILE_LANGUAGE:C>:-std=gnu99 -Wno-implicit-function-declaration>
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++1z -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-threadsafe-statics>
)