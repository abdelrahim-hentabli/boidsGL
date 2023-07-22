CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

SET(CMAKE_CXX_STANDARD 11)

project(boids)

find_package(OpenMP REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})


ADD_SUBDIRECTORY(./src ../bin)

if(OpenMP_CXX_FOUND)
    target_link_libraries(timingMP PUBLIC OpenMP::OpenMP_CXX)
endif()

if(OPENGL_FOUND)
    target_link_libraries(boids PUBLIC ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
endif()

if(OpenMP_CXX_FOUND AND OPENGL_FOUND)
    target_link_libraries(boidsMP PUBLIC OpenMP::OpenMP_CXX ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
endif()

