cmake_minimum_required(VERSION 3.10)
project(alg2)

set(CMAKE_C_STANDARD 99)

find_package(GTest REQUIRED)
add_subdirectory(libs/graphs)

add_executable(lab1test src/tests.cpp)

target_include_directories(lab1test PRIVATE libs/graphs/include)
target_link_libraries(lab1test PRIVATE graphs GTest::gtest)