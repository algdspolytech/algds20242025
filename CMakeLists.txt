cmake_minimum_required(VERSION 3.10)
project(alg1)

set(CMAKE_C_STANDARD 99)

add_executable(lab7 src/btree.cc)

target_include_directories(lab7 PRIVATE ./include/)