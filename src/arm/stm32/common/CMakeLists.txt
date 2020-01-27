set (sources_path ${PROJECT_SOURCE_DIR}/src/arm/stm32/common)

add_library(hal_stm32_common STATIC)

target_sources(hal_stm32_common
    PUBLIC
        ${PROJECT_SOURCE_DIR}/interface/hal/core/core.hpp

        ${CMAKE_CURRENT_SOURCE_DIR}/stm32_assert.c
        ${CMAKE_CURRENT_SOURCE_DIR}/stm32_sleep.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/stm32_time.cpp
)

target_include_directories(hal_stm32_common
    PUBLIC
        ${PROJECT_SOURCE_DIR}/interface
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(hal_stm32_common PUBLIC
    $<$<COMPILE_LANGUAGE:CXX>:-fconcepts>
)

target_link_libraries(hal_stm32_common PUBLIC hal_common_utils stm32 eul)
