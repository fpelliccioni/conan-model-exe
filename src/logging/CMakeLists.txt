find_package(spdlog 1.8.1 REQUIRED)

# add_library(logger "logger.hpp" "logger.cpp")
add_library(logger "logger.cpp")
# target_include_directories(logger PUBLIC "..")
target_include_directories(logger PUBLIC ${CMAKE_SOURCE_DIR}/include)

if(${LOGGING} MATCHES ${CONSOLE})
  target_compile_definitions(logger PRIVATE CONSOLE_LOGGING)
endif()

if(${LOGGING} MATCHES ${SYSLOG})
  target_compile_definitions(logger PRIVATE SYSLOG_LOGGING)
endif()
set_target_properties(logger PROPERTIES LINKER_LANGUAGE CXX CXX_STANDARD 20 CXX_STANDARD_REQUIRED TRUE)
target_link_libraries(logger PUBLIC spdlog::spdlog)


if(RUN_TIDY)
  setup_clang_tidy(logger)
  setup_clang_format(logger)
  setup_cmake_format(logger ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt)
endif()
