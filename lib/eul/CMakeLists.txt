include (ExternalProject)

message (STATUS "Adding library: EmbeddedUtilityLibrary")

ExternalProject_Add(
    embedded_utility_libraries
    GIT_REPOSITORY https://github.com/matgla/EmbeddedUtilityLibraries.git
    GIT_TAG master
    SOURCE_DIR        "${CMAKE_BINARY_DIR}/eul-src"
    BINARY_DIR        "${CMAKE_BINARY_DIR}/eul-build"
    CMAKE_ARGS        "-DLOG_LEVEL=${LOG_LEVEL}"
    INSTALL_COMMAND   ""
)

add_library(eul OBJECT IMPORTED GLOBAL)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/eul-src/include)
set_target_properties(eul
    PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_BINARY_DIR}/eul-src/include"
        IMPORTED_LOCATION             "${CMAKE_BINARY_DIR}/eul-build/libeul.a")

add_dependencies(eul embedded_utility_libraries)
