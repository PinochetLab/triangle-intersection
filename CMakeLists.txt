cmake_minimum_required(VERSION 3.10)

project(TriangleIntersection)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB SOURCES
    "src/*.cpp"
    "main.cpp"
)

add_executable(TriangleIntersection ${SOURCES})