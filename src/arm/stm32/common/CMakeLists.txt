set (sources_path ${PROJECT_SOURCE_DIR}/src/arm/stm32/common)

set(sources
    ${sources_path}/stm32_assert.c
    ${sources_path}/stm32_sleep.cpp
    ${sources_path}/stm32_time.cpp
)

add_library(hal_stm32_common ${sources})

target_include_directories(hal_stm32_common
    PUBLIC
        ${PROJECT_SOURCE_DIR}/interface
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(hal_stm32_common PUBLIC
    $<$<COMPILE_LANGUAGE:CXX>:-fconcepts>
)

target_link_libraries(hal_stm32_common PUBLIC stm32)