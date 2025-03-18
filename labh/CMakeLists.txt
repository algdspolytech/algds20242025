cmake_minimum_required(VERSION 3.20)
project(labh C)

set(CMAKE_BUILD_TYPE Debug)

include_directories(deps/criterion-2.4.2/include)

link_directories(deps/criterion-2.4.2/lib)

file(GLOB SOURCES "src/*.c")

file(GLOB TEST_SOURCES "tests/*.c")

add_executable(tests ${SOURCES} ${TEST_SOURCES})

target_link_libraries(tests criterion)

enable_testing()
add_test(NAME Tests COMMAND tests)

