CMAKE_MINIMUM_REQUIRED(VERSION 3.18)

SET(CMAKE_CXX_STANDARD 11)

project(boids)

include(CheckLanguage)
check_language(CUDA)

find_package(OpenMP REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ./include)

ADD_SUBDIRECTORY(./src ../bin)

if(OpenMP_CXX_FOUND AND OPENGL_FOUND)
    target_link_libraries(boids PUBLIC OpenMP::OpenMP_CXX ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
endif()

