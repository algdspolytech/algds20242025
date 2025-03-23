cmake_minimum_required(VERSION 3.10)
project(alg1)

add_library(tree STATIC src/tree.c)
target_include_directories(tree PRIVATE ./include/)