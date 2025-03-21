file(GLOB sources "${PROJECT_SOURCE_DIR}/src/*.c")
list(REMOVE_ITEM sources "${PROJECT_SOURCE_DIR}/src/main.c")

file(GLOB tests "${PROJECT_SOURCE_DIR}/test/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/test/main.cpp")


foreach(file ${tests})
  get_filename_component(name ${file} NAME_WE)
  
  add_executable("${name}_tests" ...)
  
  target_link_libraries("${name}_tests" ...)
  
  add_test(
    NAME ${name}
    COMMAND ${name}_tests
    CONFIGURATIONS Debug  
  )
endforeach()