set(library_name "hal_x86_common_core")

add_library(${library_name})

target_sources(${library_name}
    PUBLIC
        # HPP
    PRIVATE
        # CPP
        ${CMAKE_CURRENT_SOURCE_DIR}/x86_common_clock.cpp
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
)
