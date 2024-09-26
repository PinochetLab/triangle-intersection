cmake_minimum_required(VERSION 3.10)

project(TriangleIntersection)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB SOURCES
    "src/*.cpp"
)

add_library(TriangleLib STATIC ${SOURCES})

add_executable(TriangleIntersection ${SOURCES})

enable_testing()

file(GLOB TEST_SOURCES
    "tests/*.cpp"
)

add_executable(TriangleIntersectionTests ${TEST_SOURCES})

target_link_libraries(TriangleIntersectionTests TriangleLib)

enable_testing()
add_test(NAME TriangleTests COMMAND TriangleIntersectionTests)