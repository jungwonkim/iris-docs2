include_directories(${IRIS_INC_DIR})
include_directories(00_common)

macro(iris_test arg)
    add_executable(${arg} ${arg}.c)
    target_link_libraries(${arg} iris pthread)
    add_test(${arg} ./${arg})
    set_tests_properties(${arg} PROPERTIES FAIL_REGULAR_EXPRESSION "error")
endmacro(iris_test)

add_subdirectory(01_init_finalize)
add_subdirectory(02_task_depend)
