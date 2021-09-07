CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

SET(CMAKE_CXX_STANDARD 11)

project(boids)

find_package(SDL2 REQUIRED)
find_package(OpenMP)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})

if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
endif()

ADD_SUBDIRECTORY(./src ../bin)

if(OpenMP_CXX_FOUND AND GLEW_FOUND AND OPENGL_FOUND)
    target_link_libraries(boids PUBLIC ${SDL2_LIBRARIES}  OpenMP::OpenMP_CXX ${OPENGL_LIBRARIES})
endif()

