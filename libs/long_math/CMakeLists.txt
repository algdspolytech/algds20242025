cmake_minimum_required(VERSION 3.10)
project(alg1)

add_library(lnumbers STATIC ./src/long_numbers.c)
target_include_directories(lnumbers PRIVATE ./include/)