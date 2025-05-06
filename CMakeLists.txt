cmake_minimum_required(VERSION 3.10)

project(HashTableProject C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers
    hash_table.h
)

set(Sources
    hash_table.c
)

add_library(HashTableLib STATIC ${Sources} ${Headers})

add_subdirectory(test)
