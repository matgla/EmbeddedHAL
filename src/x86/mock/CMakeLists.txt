set(sources_path ${PROJECT_SOURCE_DIR}/src/x86/mock)
set(library_name "hal_x86_mock")

message (STATUS "Adding x86 mock library")
add_library(${library_name})

target_sources(${library_name}
    PUBLIC
        # HPP
        ${CMAKE_CURRENT_SOURCE_DIR}/clock/x86_mock_clock.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gpio/x86_mock_gpio.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/interfaces/x86_mock_usart.hpp
    PRIVATE
        # CPP
        ${CMAKE_CURRENT_SOURCE_DIR}/clock/x86_mock_clock.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/time/x86_mock_time.cpp
)

target_include_directories(${library_name}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/interface
        ${PROJECT_BINARY_DIR}/include
)

target_link_libraries(${library_name}
    PUBLIC
        eul
        hal_common
        hal_common_utils
)
