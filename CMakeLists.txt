cmake_minimum_required(VERSION 3.10)
PROJECT(QUIC)


option(DEBUG "Produce debugging information" ON)

add_definitions(-std=c++11)
add_definitions(-DLINUX)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-maybe-uninitialized -Werror ")
SET(CMAKE_PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR})
INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/
)

add_subdirectory(quic)