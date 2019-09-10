add_library(hal_avr_interfaces)

target_sources(hal_avr_interfaces
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/avr_i2c.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/avr_usart.hpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/avr_i2c.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/avr_usart.cpp
)

target_include_directories(hal_avr_interfaces
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/interface
)

target_link_libraries(hal_avr_interfaces PUBLIC avr gsl)