cmake_minimum_required(VERSION 2.6)
PROJECT(cpp_indie_studio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${IRRLICHT_INCLUDE_DIR})

file(
        GLOB_RECURSE
        SOURCES
        src/*.cpp
)
file(
        GLOB_RECURSE
        HEADERS
        includes/*.hpp
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(Irrlicht)

add_executable(MyGauntlet ${SOURCES} ${HEADERS})

target_include_directories(MyGauntlet PRIVATE includes)
target_link_libraries(MyGauntlet ${IRRLICHT_LIBRARY})
