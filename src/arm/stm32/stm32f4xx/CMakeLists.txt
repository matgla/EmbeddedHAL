
add_library(hal_stm32f4xx STATIC)

target_sources(hal_stm32f4xx
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/clock/stm32f4xx_clock.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gpio/stm32f4xx_gpio.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/interfaces/stm32f4xx_usart.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/interfaces/detail/stm32f4xx_usart_traits.hpp

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/clock/stm32f4xx_clock.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gpio/stm32f4xx_gpio.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/interfaces/stm32f4xx_usart.cpp
)

add_subdirectory(core)
add_subdirectory(time)
add_subdirectory(interrupts)

target_include_directories(hal_stm32f4xx
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/interface
        ${PROJECT_BINARY_DIR}/include
)

target_link_libraries(hal_stm32f4xx
    PUBLIC
        stm32
        GSL
        eul
        hal_stm32f4xx_core
        hal_stm32f4xx_time
        hal_stm32f4xx_interrupts
)
