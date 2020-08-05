if (${BOARD} STREQUAL "Simulator")
    set(path_to_specific_gpio_config "boards/x86/simulator/gpio_config.hpp")
    set(path_to_specific_usart_config "boards/x86/simulator/usart_config.hpp")

    set(sources_path ${CMAKE_CURRENT_SOURCE_DIR}/../../src/x86/simulator)

    set(sources
        ###              HPP               ##
        ${sources_path}/detail/tcp_server.hpp
        ${sources_path}/gpio/x86_gpio.hpp
        ${sources_path}/usart/x86_usart.hpp

        ###              CPP               ##
        ${sources_path}/time/x86_sleep.cpp
    )

    find_package(Boost COMPONENTS system REQUIRED)
endif ()

if (${BOARD} STREQUAL "x86_linux")
    add_subdirectory(common)
    add_subdirectory(time)
endif ()

message(STATUS "Generate config file: ${path_to_specific_gpio_config}")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../../config/gpio_config.hpp.in ${PROJECT_BINARY_DIR}/include/hal/gpio.hpp @ONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../../config/usart_config.hpp.in ${PROJECT_BINARY_DIR}/include/hal/usart.hpp @ONLY)

add_library(hal ${hal_interface} ${sources})

target_include_directories(hal
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/..
        ${CMAKE_CURRENT_SOURCE_DIR}/../../interface
        ${CMAKE_BINARY_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

target_link_libraries(hal
    PUBLIC
        hal_common_utils
    PRIVATE
        GSL
        ${Boost_LIBRARIES}
        pthread)
