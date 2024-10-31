cmake_minimum_required(VERSION 3.28)
project(LabC)

set(CMAKE_C_STANDARD 11)

add_library(LabC main.c
        labC.h)

add_subdirectory(./googletest GTEST)
include_directories(googletest/googletest/include)

enable_testing()

add_executable(labCTEST tests.cxx)
target_link_libraries(labCTEST GTest::gtest_main LabC)
include(GoogleTest)
gtest_discover_tests(labCTEST)