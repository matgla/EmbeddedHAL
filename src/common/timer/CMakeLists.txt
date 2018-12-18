add_library(hal_common_time)

set(sources "${PROJECT_SOURCE_DIR}/src/common/timer")

target_sources(hal_common_time
    PRIVATE
        ${sources}/interval_timer.cpp
        ${sources}/timeout_timer.cpp
        ${sources}/timer_manager.cpp
        ${sources}/timer.cpp
)

target_include_directories(hal_common_time
    PRIVATE
        ${PROJECT_SOURCE_DIR}/interface
)