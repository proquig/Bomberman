cmake_minimum_required(VERSION 3.5)
project(cpp_indie_studio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(includes/
        /home/cloquet/Bureau/irrlicht-1.8.3/include/)

link_directories(/lib64/libIrrlich.a)

set(SOURCE_FILES
    src/main.cpp)

add_executable(cpp_indie_studio ${SOURCE_FILES})