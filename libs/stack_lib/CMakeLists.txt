cmake_minimum_required(VERSION 3.10)
project(stacks)

add_library(${PROJECT_NAME} STATIC src/LLStack.c src/ArrStack.c)
target_include_directories(${PROJECT_NAME} PRIVATE include)