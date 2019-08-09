set(sources_path ${PROJECT_SOURCE_DIR}/src/x86/simulator)
set(library_name "hal_x86_simulator")

add_library(${library_name})

if (NOT BUILD_SHARED)
    message (STATUS "Using static version of boost libraries")
    set(Boost_USE_STATIC_LIBS ON)
endif ()

find_package(Boost REQUIRED COMPONENTS system exception thread)

target_sources(${library_name}
    PUBLIC
        # HPP
        # ${sources_path}/clock/x86_simulator_clock.hpp
        # ${sources_path}/gpio/x86_simulator_gpio.hpp
        ${sources_path}/usart/x86_simulator_usart.hpp
    PRIVATE
        # CPP
        # ${sources_path}/clock/x86_simulator_clock.cpp
        ${sources_path}/time/x86_sleep.cpp
)

target_include_directories(${library_name}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/interface
        ${PROJECT_BINARY_DIR}/include
    PRIVATE
        ${Boost_INCLUDE_DIRS}
)
link_directories(${Boost_LIBRARY_DIRS})

target_link_libraries(hal_x86_simulator
    PRIVATE
        Boost::exception
        Boost::thread
        Boost::system

)


