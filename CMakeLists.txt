cmake_minimum_required(VERSION 3.23) # using interface libraries with sources https://cmake.org/cmake/help/latest/command/add_library.html#interface-libraries

project(model-exe)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include("options")

set(CONSOLE "console")
set(SYSLOG "syslog")
set(LOGGING_OPTIONS ${CONSOLE} ${SYSLOG})

options(LOGGING ${SYSLOG} "the desired logging mechanism to use" "${LOGGING_OPTIONS}")
option(CONAN_SETUP "use conan to setup all the dependencies" ON)
option(BUILD_MAIN "build the main funciton for this application" ON)
option(BUILD_TESTS "build the tests for this application" OFF)
option(RUN_TIDY "run clang-tidy" OFF)
option(COVERAGE "Enable code coverage testing" OFF)

if(COVERAGE)
  cmake_policy(SET CMP0079 NEW)
endif()

add_library(model INTERFACE "include/model/model.hpp")
add_library(model::model ALIAS model)
set_target_properties(model PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(model INTERFACE cxx_std_20)
# target_include_directories(model INTERFACE ${CMAKE_SOURCE_DIR}/include)

if(RUN_TIDY)
  include("clang-tidy")
  setup_clang_tidy(model)

  include("clang-format")
  setup_clang_format(model)

  include("cmake-format")
  setup_cmake_format(main "${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt")
endif()

if(BUILD_MAIN)
  add_subdirectory(src)
endif()

if(BUILD_TESTS)
  add_subdirectory(test)
endif()


# cmake_minimum_required(VERSION 3.15)
# project(usage CXX)

# find_package(eve REQUIRED CONFIG)

# add_executable(${CMAKE_PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
# set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)
# target_link_libraries(${CMAKE_PROJECT_NAME} eve::eve)

# install(TARGETS ${CMAKE_PROJECT_NAME})