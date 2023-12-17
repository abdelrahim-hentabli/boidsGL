
add_library(base_boidslib STATIC
    base/boids.cpp
)
add_library(openMP_boidslib STATIC
    openMP/boids.cpp
)
ADD_EXECUTABLE(boids
    main.cpp 
)

target_link_libraries(boids PRIVATE
    openMP_boidslib
)