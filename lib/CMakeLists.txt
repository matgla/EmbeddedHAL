message(STATUS "Adding libraries")

if (NOT TARGET embedded_utility_libraries)
    add_subdirectory(eul)
endif ()

if (NOT TARGET gsl)
    add_subdirectory(gsl)
endif ()