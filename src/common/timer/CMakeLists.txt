add_library(hal_common_time)

set(sources "${PROJECT_SOURCE_DIR}/src/common/timer")

target_sources(hal_common_time
    PRIVATE
        ${sources}/timer_manager.cpp
)

target_include_directories(hal_common_time
    PRIVATE
        ${PROJECT_SOURCE_DIR}/interface
)

target_link_libraries(hal_common_time
    PRIVATE
        eul_container
        hal_flags
)
