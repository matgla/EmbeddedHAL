set(sources_path ${PROJECT_SOURCE_DIR}/src/x86/mock)
set(library_name "hal_x86_mock")

add_library(${library_name})

target_sources(${library_name}
    PUBLIC
        # HPP
        ${sources_path}/clock/x86_mock_clock.hpp
        ${sources_path}/gpio/x86_mock_gpio.hpp
        ${sources_path}/interfaces/x86_mock_usart.hpp
    PRIVATE
        # CPP
        ${sources_path}/clock/x86_mock_clock.cpp
        ${sources_path}/time/x86_mock_time.cpp
)

target_include_directories(${library_name}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/interface
        ${PROJECT_BINARY_DIR}/include
)
