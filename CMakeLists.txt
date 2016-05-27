cmake_minimum_required(VERSION 2.6)
PROJECT(cpp_indie_studio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Llib -g")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(Irrlicht)
find_package(IrrKlang)

include_directories(${IRRLICHT_INCLUDE_DIR})
include_directories(${IRRKLANG_INCLUDE_DIR})

link_directories(${CMAKE_HOME_DIRECTORY}/lib)

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

add_custom_command(
        TARGET Bomberman POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_HOME_DIRECTORY}/assets
            $<TARGET_FILE_DIR:Bomberman>/assets
)

add_custom_command(
        TARGET Bomberman POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_HOME_DIRECTORY}/lib
        $<TARGET_FILE_DIR:Bomberman>/lib
)

target_include_directories(Bomberman PRIVATE includes)
target_link_libraries(Bomberman ${IRRLICHT_LIBRARY})
target_link_libraries(Bomberman ikpFlac)
target_link_libraries(Bomberman ikpMP3)
target_link_libraries(Bomberman IrrKlang)
