cmake_minimum_required(VERSION 3.10)
project(renderer C CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++14")
endif(MSVC)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
  message(ERROR "OPENGL not found!")
endif(NOT OPENGL_FOUND)

set(glew-cmake_BUILD_SHARED OFF CACHE BOOL "Do not build the shared glew library")
set(glew-cmake_BUILD_STATIC ON CACHE BOOL "Build the static glew library")
set(ONLY_LIBS ON CACHE BOOL "Do not build executables")
include_directories(thirdparty/glew-cmake/include)
add_subdirectory(thirdparty/glew-cmake)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Do not build GLFW shared libraries")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Do not build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Do not build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Do not build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE BOOL "Do not generate installation target")
include_directories(thirdparty/glfw/include)
add_subdirectory(thirdparty/glfw)

include_directories(thirdparty/imgui)
include_directories(thirdparty/imgui/backends)
add_library(
  imgui STATIC
  thirdparty/imgui/imconfig.h
  thirdparty/imgui/imgui.h
  thirdparty/imgui/imgui.cpp
  thirdparty/imgui/imgui_tables.cpp
  thirdparty/imgui/imgui_demo.cpp
  thirdparty/imgui/imgui_widgets.cpp
  thirdparty/imgui/imgui_draw.cpp
  thirdparty/imgui/backends/imgui_impl_opengl3.h
  thirdparty/imgui/backends/imgui_impl_opengl3.cpp
  thirdparty/imgui/backends/imgui_impl_glfw.h
  thirdparty/imgui/backends/imgui_impl_glfw.cpp
  # thirdparty/imgui/imgui_internal.h
 )

include_directories(thirdparty/stb)
include_directories(src)
add_subdirectory(src/lib)
add_subdirectory(src)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
  enable_testing()
  include(GoogleTest)
  add_subdirectory(tests)
endif()
