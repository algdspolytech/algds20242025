cmake_minimum_required(VERSION 3.10)
project(alg1)

add_library(hash STATIC src/lin_htable.c)
target_include_directories(hash PRIVATE ./include/)