
cmake_minimum_required(VERSION 3.20)
project(labJ LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(labJ
        hash_table.c
        tests.cpp
)
target_include_directories(labJ PRIVATE "D:\\Programs\\googletest\\googletest\\include")
add_subdirectory("D:\\Programs\\googletest" GTEST)
target_link_libraries(labJ PRIVATE gtest_main)
