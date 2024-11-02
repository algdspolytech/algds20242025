cmake_minimum_required(VERSION 3.10)
project(dfs)

add_library(${PROJECT_NAME} STATIC src/dfs.c)
target_include_directories(${PROJECT_NAME} PRIVATE include)