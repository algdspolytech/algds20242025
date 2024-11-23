cmake_minimum_required(VERSION 3.10)
project(alg2)

set(CMAKE_C_STANDARD 99)

find_package(GTest REQUIRED)
add_subdirectory(libs/rucksack)

add_executable(lab3test src/tests.cpp)

target_include_directories(lab3test PRIVATE libs/rucksack/include)
target_link_libraries(lab3test PRIVATE rucksack GTest::gtest)