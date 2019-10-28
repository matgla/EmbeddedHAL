set(sources_path ${PROJECT_SOURCE_DIR}/src/arm/stm32/stm32f1xx)

add_library(hal_stm32f1xx OBJECT)

target_sources(hal_stm32f1xx PRIVATE 
## CPP
#    ${sources_path}/clock/stm32f1xx_clock.cpp
    ${sources_path}/interfaces/stm32f1xx_usart.cpp
    ${sources_path}/core/core_stm32.cpp
## HPP
    PUBLIC
#    ${sources_path}/clock/stm32f1xx_clock.hpp
    ${sources_path}/gpio/stm32f1xx_gpio.hpp
    ${sources_path}/interfaces/stm32f1xx_usart.hpp

    )

target_include_directories(hal_stm32f1xx
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/interface
        ${PROJECT_BINARY_DIR}/include
)

target_link_libraries(hal_stm32f1xx
    PUBLIC
        hal_stm32_common
        gsl
        eul
)
