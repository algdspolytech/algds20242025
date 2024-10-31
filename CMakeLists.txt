cmake_minimum_required(VERSION 3.8)
project(tests_lab1)

set(CMAKE_CXX_STANDARD 11)



include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("C:/Users/Egor/Documents/desktop/algos/algds20242025/build/vcpkg_installed/x64-windows/include")

find_package(GTest CONFIG REQUIRED)

find_library(
    LIBGTESTMAIN_LIBRARY
    NAMES gtest_main
    HINTS ${CMAKE_SOURCE_DIR}/../../../../tests_lab1/googletest/build/lib/)
    
set(GTEST_LOCATION "C:/Users/Egor/Documents/desktop/algos/algds20242025/build/vcpkg_installed/x64-windows/lib")


set(CMAKE_PREFIX_PATH "C:/Program Files/vcpkg/installed/x64-windows/share")

enable_testing()


add_subdirectory(test)

