set (library_name "hal_avr_common_gpio_ports")

add_library(${library_name})

set (includes "")
set (sources "")
if (HAS_PORT_A)
    set (includes "${includes}" ${CMAKE_CURRENT_SOURCE_DIR}/avr_port_a.hpp)
    set (sources "${sources}" ${CMAKE_CURRENT_SOURCE_DIR}/avr_port_a.cpp)
endif ()

if (HAS_PORT_B)
    set (includes "${includes}" ${CMAKE_CURRENT_SOURCE_DIR}/avr_port_b.hpp)
    set (sources "${sources}" ${CMAKE_CURRENT_SOURCE_DIR}/avr_port_b.cpp)
endif ()

if (HAS_PORT_C)
    set (includes "${includes}" ${CMAKE_CURRENT_SOURCE_DIR}/avr_port_c.hpp)
    set (sources "${sources}" ${CMAKE_CURRENT_SOURCE_DIR}/avr_port_c.cpp)
endif ()

if (HAS_PORT_D)
    set (includes "${includes}" ${CMAKE_CURRENT_SOURCE_DIR}/avr_port_d.hpp)
    set (sources "${sources}" ${CMAKE_CURRENT_SOURCE_DIR}/avr_port_d.cpp)
endif ()

target_sources(${library_name}
    PUBLIC
        ${includes}
    PRIVATE
        ${sources}
)

target_include_directories(${library_name}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
)
