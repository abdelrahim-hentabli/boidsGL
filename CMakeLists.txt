CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

SET(CMAKE_CXX_STANDARD 11)

project(boids)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

ADD_SUBDIRECTORY(./src ../bin)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(boids PUBLIC ${SDL2_LIBRARIES}  OpenMP::OpenMP_CXX)
endif()

