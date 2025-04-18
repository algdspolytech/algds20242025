cmake_minimum_required(VERSION 3.25)
project(algds20242025)


enable_testing()


find_package(GTest REQUIRED)


add_executable(hash_map labJ/hash_map.c)


add_executable(test_hash_map labJ/test_hash_map.cpp)
target_link_libraries(test_hash_map GTest::GTest GTest::Main)