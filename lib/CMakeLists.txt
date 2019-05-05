message(STATUS "Adding libraries")
if (NOT TARGET eul)
    add_subdirectory(eul/eul)
endif ()

add_subdirectory(gsl)