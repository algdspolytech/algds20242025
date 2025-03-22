cmake_minimum_required(VERSION 3.28)
project(LabH)

set(CMAKE_C_STANDARD 11)

add_library(LabH main.c
        labH.h
        labH.h)

add_subdirectory(./googletest GTEST)
include_directories(googletest/googletest/include)

enable_testing()

add_executable(labHTEST tests.cxx)
target_link_libraries(labHTEST GTest::gtest_main LabH)
include(GoogleTest)
gtest_discover_tests(labHTEST)