cmake_minimum_required(VERSION 3.28)

project(graph LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)

if(CMAKE_C_COMPILER_ID MATCHES "Clang" OR CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID MATCHES "Intel")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wconversion -Wextra -Wpedantic")
endif()

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/6b63c98ac43efc992122f1da12aaf0a0e0658206.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(graph SHARED "include/graph.c")
target_include_directories(graph PUBLIC "include")

add_executable(graph_tests "tests/graph_tests.cpp")
target_link_libraries(graph_tests graph GTest::gtest_main)

add_executable(graph_task "task/graph_task.c")
target_link_libraries(graph_task graph)
