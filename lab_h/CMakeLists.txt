cmake_minimum_required(VERSION 3.30)
project(CartesianTree)

set(CMAKE_CXX_STANDARD 20)

if(CMAKE_C_COMPILER_ID MATCHES "Clang" OR CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID MATCHES "Intel")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wconversion -Wextra -Wpedantic")
endif()

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/6b63c98ac43efc992122f1da12aaf0a0e0658206.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(CartesianTree SHARED "CartesianTree.c")
target_include_directories(CartesianTree PUBLIC "include")

add_executable(CartesianTree_tests "CartesianTree_tests.cpp")
target_link_libraries(CartesianTree_tests CartesianTree GTest::gtest_main)
