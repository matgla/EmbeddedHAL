add_library(boards_containers INTERFACE)

target_sources(boards_containers
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/driver_container.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/driver_holder.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/drivers_pack.hpp
)

message("Including: ${PROJECT_SOURCE_DIR}")
target_include_directories(boards_containers
    INTERFACE ${PROJECT_SOURCE_DIR})