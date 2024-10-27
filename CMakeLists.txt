cmake_minimum_required(VERSION 3.10)
project(AlgA)

find_package(GTest REQUIRED)
add_subdirectory(libs/stack_lib)

add_executable(${PROJECT_NAME} tests/tests.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE libs/stack_lib/include)
target_link_libraries(${PROJECT_NAME} PRIVATE stacks GTest::gtest)