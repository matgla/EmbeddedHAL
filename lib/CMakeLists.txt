message(STATUS "Adding libraries")

include (../cmake/GitModules.cmake)

fetch_module_with_path(lib/eul ${CMAKE_CURRENT_SOURCE_DIR}/eul ${PROJECT_SOURCE_DIR})
fetch_module_with_path(lib/gsl/gsl ${CMAKE_CURRENT_SOURCE_DIR}/gsl/gsl ${PROJECT_SOURCE_DIR})
