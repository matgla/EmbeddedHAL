set(sources_path ${PROJECT_SOURCE_DIR}/src/arm/stm32/stm32f1xx)

set(sources
    ${sources_path}/interfaces/stm32f1xx_usart.cpp
)

add_library(hal_stm32f1xx ${sources})

target_include_directories(hal_stm32f1xx
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/interface
        ${PROJECT_BINARY_DIR}/include
)

target_link_libraries(hal_stm32f1xx PUBLIC hal_stm32_common stm32 gsl eul)
