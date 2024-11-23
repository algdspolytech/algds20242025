cmake_minimum_required(VERSION 3.10)
project(rucksack)

add_library(${PROJECT_NAME} STATIC ./src/rucksack.c)
target_include_directories(${PROJECT_NAME} PRIVATE ./include/)