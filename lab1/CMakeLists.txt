cmake_minimum_required(VERSION 3.28)
project(LabA)

set(CMAKE_C_STANDARD 11)

add_library(LabA main.c
        labA.h)

add_subdirectory(./googletest GTEST)
include_directories(googletest/googletest/include)

enable_testing()

add_executable(labATEST tests.cxx)
target_link_libraries(labATEST GTest::gtest_main LabA)
include(GoogleTest)
gtest_discover_tests(labATEST)