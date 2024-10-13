cmake_minimum_required(VERSION 3.27)
project(laba1 C)

set(CMAKE_C_STANDARD 11)

add_executable(laba1 ./tests/UnitTests.c
        includes/Arr_queue.h
        src/Arr_queue.c
        includes/List_queue.h
        src/List_queue.c)
