set (sources_path ${PROJECT_SOURCE_DIR}/src/arm/stm32/common)

set(sources
    ${sources_path}/stm32_assert.c
    ${sources_path}/stm32_sleep.cpp
    ${sources_path}/stm32_time.cpp
)

add_library(stm32_hal_common ${sources})

target_include_directories(stm32_hal_common
    PUBLIC
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/../../..
        ${PROJECT_SOURCE_DIR}/../../../../interface
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(stm32 PUBLIC
    $<$<COMPILE_LANGUAGE:CXX>:-fconcepts>
)

target_link_libraries(stm32_hal_common PUBLIC hal_interface stm32)