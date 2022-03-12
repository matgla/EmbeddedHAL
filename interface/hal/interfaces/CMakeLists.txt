add_library(hal_interfaces_interfaces INTERFACE)

target_sources(hal_interfaces_interfaces
    INTERFACE 
        ${CMAKE_CURRENT_SOURCE_DIR}/i2c.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/usart.hpp
)

target_link_libraries(hal_interfaces_interfaces 
    INTERFACE 
        eul_functional
)
