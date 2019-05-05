message(STATUS "Adding libraries")

if (NOT TARGET eul)
    add_subdirectory(eul/eul)
endif ()

if (NOT TARGET gsl)
    add_subdirectory(gsl)
endif ()