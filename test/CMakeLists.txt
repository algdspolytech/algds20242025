project(HashMap_tests LANGUAGES C CXX)

file(GLOB TEST_SOURCES "*.cpp")

file(GLOB HASHMAP_SOURCES 
    "${PROJECT_SOURCE_DIR}/../src/hashmap.c"  # Путь к вашему C-файлу
)

add_executable(HashMap_tests 
  ${TEST_SOURCES}
  ${HASHMAP_SOURCES}
)

# Линкуемся с GTest
target_link_libraries(HashMap_tests
    PRIVATE 
    GTest::gtest 
    GTest::gtest_main
)

add_test(
    NAME HashMap_tests
    COMMAND HashMap_tests
)