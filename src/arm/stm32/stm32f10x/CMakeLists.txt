set(sources_path ${PROJECT_SOURCE_DIR}/src/arm/stm32/stm32f10x)

set(sources
    ${sources_path}/time/rtc_stm32.cpp
)

add_library(hal_stm32f1xx ${sources})

target_include_directories(hal_stm32f1xx
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/interface
        ${PROJECT_BINARY_DIR}/include
)

target_link_libraries(hal_stm32f1xx PUBLIC hal_stm32_common gsl)
