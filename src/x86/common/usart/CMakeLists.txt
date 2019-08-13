set(library_name "hal_x86_common_usart")

add_library(${library_name})

find_package(Boost REQUIRED COMPONENTS system exception thread)

target_sources(${library_name}
    PUBLIC
        # HPP
        ${CMAKE_CURRENT_SOURCE_DIR}/x86_common_usart.hpp
    PRIVATE
        # CPP
        ${CMAKE_CURRENT_SOURCE_DIR}/x86_common_usart.cpp
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

target_link_libraries(hal_x86_common_usart
    PRIVATE
        Boost::exception
        Boost::thread
        Boost::system

)