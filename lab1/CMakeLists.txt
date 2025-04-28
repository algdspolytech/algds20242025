cmake_minimum_required(VERSION 3.30)
project(HashTable)

set(CMAKE_C_STANDARD 11)

# Включение всех предупреждений для GCC/Clang
if(CMAKE_C_COMPILER_ID MATCHES "Clang" OR CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID MATCHES "Intel")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Werror")
endif()

# Загрузка Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/6b63c98ac43efc992122f1da12aaf0a0e0658206.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Основная библиотека хэш-таблицы
add_library(hash_table STATIC hash_table.c)
target_include_directories(hash_table PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Исполняемый файл с тестами
add_executable(hash_table_tests hash_table_test.cpp)
target_link_libraries(hash_table_tests
        PRIVATE
        hash_table
        GTest::gtest_main
        GTest::gmock_main)

# Добавляем цель для запуска тестов
enable_testing()
add_test(NAME hash_table_tests COMMAND hash_table_tests)