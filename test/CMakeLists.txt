find_package(Catch2 2.13.0 REQUIRED)

include("unit-test-helper")
add_executable(user_tests "main.cpp" "model.cpp" "user_database.cpp")
target_link_libraries(user_tests PRIVATE unit_test_helper Catch2::Catch2)

if(COVERAGE)
  include("code-coverage")
  setup_coverage(user_tests)
  setup_coverage(response_builder)
  setup_coverage(submodule1)

  set(COVERAGE_EXCLUDES "/usr/**" "/home/*/.conan/**" "*test*" "*build*")
  setup_target_for_coverage_lcov(NAME coverage EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/user_tests)
endif()

if(RUN_TIDY)
  # setup_clang_tidy(tester) # Very annoying warnings because of catch2
  setup_clang_format(user_tests)
  setup_cmake_format(tests ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt)
endif()
