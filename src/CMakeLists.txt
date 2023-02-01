add_subdirectory("logging") # Needs to be first
add_subdirectory("utility")

add_executable(model_app "main.cpp")
target_link_libraries(model_app PRIVATE app_args server_logger)
set_target_properties(model_app PROPERTIES LINKER_LANGUAGE CXX CXX_STANDARD 20 CXX_STANDARD_REQUIRED TRUE)
# target_include_directories(model_app PUBLIC ${CMAKE_SOURCE_DIR}/include)

if(RUN_TIDY)
  setup_clang_tidy(model_app)
  setup_clang_format(model_app)
  setup_cmake_format(src ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt)
endif()
