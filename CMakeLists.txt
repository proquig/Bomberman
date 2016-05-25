cmake_minimum_required(VERSION 2.6)
PROJECT(cpp_indie_studio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Llib")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(Irrlicht)
find_package(IrrKlang)

include_directories(${IRRLICHT_INCLUDE_DIR})
include_directories(${IRRKLANG_INCLUDE_DIR})

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

add_executable(Bomberman ${SOURCES} ${HEADERS})

target_include_directories(Bomberman PRIVATE includes)
target_link_libraries(Bomberman ${IRRLICHT_LIBRARY})
target_link_libraries(Bomberman ${IRRKLANG_LIBRARY})
