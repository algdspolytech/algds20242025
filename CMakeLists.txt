cmake_minimum_required(VERSION 3.10)
project(alg1)

set(CMAKE_C_STANDARD 99)

find_package(GTest REQUIRED)
add_subdirectory(libs/hash)

add_executable(lab6test src/tests.cpp)

target_include_directories(lab6test PRIVATE libs/hash/include)
target_link_libraries(lab6test PRIVATE hash GTest::gtest)