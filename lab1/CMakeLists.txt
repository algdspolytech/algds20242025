cmake_minimum_required(VERSION 3.28)
project(LabD)

set(CMAKE_C_STANDARD 11)

add_library(LabD main.c
        labD.h
        labD.h)

add_subdirectory(./googletest GTEST)
include_directories(googletest/googletest/include)

enable_testing()

add_executable(labDTEST tests.cxx)
target_link_libraries(labDTEST GTest::gtest_main LabD)
include(GoogleTest)
gtest_discover_tests(labDTEST)