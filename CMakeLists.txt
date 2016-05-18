cmake_minimum_required(VERSION 2.6)
PROJECT(MyGauntlet)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
  "/usr/local/include/"
  ${PROJECT_SOURCE_DIR}/includes)

FILE(GLOB SRCS	src/*.cpp)

FILE (GLOB HDRS includes/*.h)


add_executable(MyGauntlet ${SRCS} ${HDRS})

target_link_libraries(MyGauntlet "/usr/local/lib/libIrrlicht.so")
