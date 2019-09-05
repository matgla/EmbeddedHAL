message(STATUS "Adding libraries")

include (../cmake/GitModules.cmake)

set (DISABLE_TESTS ON)

if (NO_STDCXX)
    fetch_module_via_branch(lib/avr_libstdcpp/avr_libstdcpp ${CMAKE_CURRENT_SOURCE_DIR}/avr_libstdcpp ${PROJECT_SOURCE_DIR} "master")
endif ()

fetch_module_via_branch(lib/eul ${CMAKE_CURRENT_SOURCE_DIR}/eul ${PROJECT_SOURCE_DIR} "master")
fetch_module_via_tag(lib/gsl/gsl ${CMAKE_CURRENT_SOURCE_DIR}/gsl/gsl ${PROJECT_SOURCE_DIR} "v2.0.0")

