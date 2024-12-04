cmake_minimum_required(VERSION 3.28)
project(LabF)

set(CMAKE_C_STANDARD 11)

add_library(LabF main.c
        labF.h
        labF.h)

add_subdirectory(./googletest GTEST)
include_directories(googletest/googletest/include)

enable_testing()

add_executable(labFTEST tests.cxx)
target_link_libraries(labFTEST GTest::gtest_main LabF)
include(GoogleTest)
gtest_discover_tests(labFTEST)