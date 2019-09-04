project (avr_libstdcpp CXX)

file(GLOB_RECURSE avr_libstdcpp_headers
    "avr_libstdcpp/include/*"
)

file(GLOB_RECURSE avr_libstdcpp_sources
    "avr_libstdcpp/src/*.cc"
)

add_library(avr_libstdcpp)

target_sources(avr_libstdcpp
    PUBLIC
        ${avr_libstdcpp_headers}
    PRIVATE
        ${avr_libstdcpp_sources}
)

target_include_directories(avr_libstdcpp PUBLIC avr_libstdcpp/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/avr_libstdcpp/include)

message ("${CMAKE_STANDARD_LIBRARIES} -l:${CMAKE_CURRENT_SOURCE_DIR}/avr_libstdcpp/include")
set(CMAKE_STANDARD_LIBRARIES "${CMAKE_STANDARD_LIBRARIES} -l:${CMAKE_CURRENT_SOURCE_DIR}/avr_libstdcpp/include")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}/avr_libstdcpp/include")