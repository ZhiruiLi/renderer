cmake_minimum_required(VERSION 3.14)
project(renderer C CXX)
set(CMAKE_CXX_STANDARD 17)

include_directories(".")

add_subdirectory(thirdparty/glfw-3.3.2)
add_subdirectory(src)
option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
  enable_testing()
  include(GoogleTest)
  add_subdirectory(tests)
endif()
