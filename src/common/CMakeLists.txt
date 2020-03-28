add_library(hal_common)

add_subdirectory(timer)
add_subdirectory(utils)

set (sources "${PROJECT_SOURCE_DIR}/src/common")

target_sources(hal_common
    PRIVATE
        ${sources}/empty.cpp
)

target_link_libraries(hal_common
    PUBLIC
        hal_common_utils
    PRIVATE
        hal_common_time
)

target_include_directories(hal_common
    PRIVATE
        ${PROJECT_SOURCE_DIR}/interface
)
