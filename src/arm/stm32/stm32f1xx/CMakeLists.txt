
add_library(hal_stm32f1xx STATIC)

target_sources(hal_stm32f1xx
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/gpio/stm32f1xx_gpio.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/clock/stm32f1xx_clock.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/interfaces/stm32f1xx_usart.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/interfaces/stm32f1xx_i2c.hpp

        ${CMAKE_CURRENT_SOURCE_DIR}/clock/stm32f1xx_clock.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/interfaces/stm32f1xx_usart.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/core_stm32.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/backupRegisters_stm32.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/core/criticalSection_stm32.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/assert_stm32.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/interfaces/stm32f1xx_i2c.cpp

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
        stm32
        GSL
        eul
)
