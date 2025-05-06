add_executable(TreeTests TreeTests.cpp)
target_link_libraries(TreeTests PRIVATE gtest gtest_main HashTableLib)
target_include_directories(TreeTests PRIVATE ${PROJECT_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(TreeTests)