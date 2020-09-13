
add_library(hal_stm32f4xx INTERFACE)

# target_sources(hal_stm32f4xx
#     PUBLIC
#         ${CMAKE_CURRENT_SOURCE_DIR}/gpio/stm32f1xx_gpio.hpp
#         ${CMAKE_CURRENT_SOURCE_DIR}/clock/stm32f1xx_clock.hpp
#         ${CMAKE_CURRENT_SOURCE_DIR}/interfaces/stm32f1xx_usart.hpp
#         ${CMAKE_CURRENT_SOURCE_DIR}/interfaces/stm32f1xx_i2c.hpp

#         ${CMAKE_CURRENT_SOURCE_DIR}/clock/stm32f1xx_clock.cpp
#         ${CMAKE_CURRENT_SOURCE_DIR}/interfaces/stm32f1xx_usart.cpp
#         ${CMAKE_CURRENT_SOURCE_DIR}/core/core_stm32.cpp
#         ${CMAKE_CURRENT_SOURCE_DIR}/core/backupRegisters_stm32.cpp
#         ${CMAKE_CURRENT_SOURCE_DIR}/core/criticalSection_stm32.cpp
#         ${CMAKE_CURRENT_SOURCE_DIR}/utils/assert_stm32.cpp
#         ${CMAKE_CURRENT_SOURCE_DIR}/interfaces/stm32f1xx_i2c.cpp

# )

add_subdirectory(core)
add_subdirectory(time)
add_subdirectory(interrupts)

target_include_directories(hal_stm32f4xx
    INTERFACE
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/interface
        ${PROJECT_BINARY_DIR}/include
)

target_link_libraries(hal_stm32f4xx
    INTERFACE
        stm32
        GSL
        eul
        hal_stm32f4xx_core
        hal_stm32f4xx_time
        hal_stm32f4xx_interrupts
)
