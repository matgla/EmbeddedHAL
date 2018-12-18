add_library(hal_common)

add_subdirectory(timer)

set (sources "${PROJECT_SOURCE_DIR}/src/common")

target_sources(hal_common
    PRIVATE
        ${sources}/empty.cpp
)

target_link_libraries(hal_common PRIVATE hal_common_time)

target_include_directories(hal_common
    PRIVATE
        ${PROJECT_SOURCE_DIR}/interface
)