cmake_minimum_required(VERSION 2.6)
PROJECT(cpp_indie_studio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lz")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")

find_package(Irrlicht REQUIRED)
find_package(IrrKlang)
find_package(Lua)
find_package(Threads)

include_directories(${IRRLICHT_INCLUDE_DIR})
include_directories(${IRRKLANG_INCLUDE_DIR})
include_directories(${LUA_INCLUDE_DIR})

link_directories(${CMAKE_HOME_DIRECTORY}/lib)

file(
        GLOB_RECURSE
        SOURCES
        src/*.cpp
)
file(
        GLOB_RECURSE
        HEADERS
        includes/*.h
        includes/*.hpp
)

set(
        GLOB_RECURSE
        SELENE_INCLUDE
        includes/Selene/
        includes/Selene/selene
)

add_executable(Bomberman ${SOURCES} ${HEADERS})

target_include_directories(Bomberman PRIVATE includes PRIVATE includes/sound PRIATE includes/xml)
target_include_directories(Bomberman PUBLIC includes/Selene PUBLIC includes/Selene/selene)
target_link_libraries(Bomberman ${IRRLICHT_LIBRARY})
target_link_libraries(Bomberman ${IRRKLANG_LIBRARY})
target_link_libraries(Bomberman ${LUA_LIBRARIES})
target_link_libraries(Bomberman ${CMAKE_THREAD_LIBS_INIT})

add_custom_command(
        TARGET Bomberman POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_HOME_DIRECTORY}/assets
            $<TARGET_FILE_DIR:Bomberman>/assets
)

add_custom_command(
        TARGET Bomberman POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_HOME_DIRECTORY}/lua
        $<TARGET_FILE_DIR:Bomberman>/lua
)

add_custom_command(
        TARGET Bomberman POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_HOME_DIRECTORY}/lib/ikpFlac.so
        ${CMAKE_HOME_DIRECTORY}/lib/ikpMP3.so
        ${CMAKE_HOME_DIRECTORY}/lib/libIrrKlang.so
        $<TARGET_FILE_DIR:Bomberman>
)
