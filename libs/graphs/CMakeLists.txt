cmake_minimum_required(VERSION 3.10)
project(alg1)

add_library(graphs STATIC ./src/graph.c)
target_include_directories(graphs PRIVATE ./include/)