cmake_minimum_required(VERSION 3.20)
project(tests_lab1 LANGUAGES CXX)

# Указываем путь к vcpkg
set(CMAKE_TOOLCHAIN_FILE "C:/Program Files/vcpkg/scripts/buildsystems/vcpkg.cmake" 
    CACHE STRING "Vcpkg toolchain file")

set(CMAKE_CXX_STANDARD 17)

include_directories("${PROJECT_SOURCE_DIR}/include")

# Подключаем GTest через vcpkg
find_package(GTest CONFIG REQUIRED)
message(STATUS "GTest found: ${GTEST_FOUND}")  # Для отладки

enable_testing()
add_subdirectory(test)