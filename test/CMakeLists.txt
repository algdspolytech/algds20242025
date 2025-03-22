cmake_minimum_required(VERSION 3.10)

set(This TreeTests)

set(Sources
    TreeTests.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    TreeLib
)


add_test(
    NAME ${This}
    COMMAND ${This}
)
