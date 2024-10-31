file(GLOB sources "${PROJECT_SOURCE_DIR}/src/*.c")
list(REMOVE_ITEM sources "${PROJECT_SOURCE_DIR}/src/main.c")

file(GLOB tests "${PROJECT_SOURCE_DIR}/test/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/test/main.cpp")


foreach(file ${tests})
  set(name)
  get_filename_component(name ${file} NAME_WE)
  add_executable("${name}_tests"
    ${sources}
    ${file}
    "${PROJECT_SOURCE_DIR}/test/main.cpp")
  target_link_libraries("${name}_tests" PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

  add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()