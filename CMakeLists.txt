# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (Renderer)

find_package(OpenGL REQUIRED)

if(CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)")
endif()
if(CMAKE_SOURCE_DIR MATCHES " ")
  message("Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause.")
endif()
if(CMAKE_BINARY_DIR MATCHES " ")
  message("Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause.")
endif()

# Compile external dependencies
add_subdirectory (external)

include_directories(
  external/glfw-3.0.3/include/GLFW/
  external/glew-1.9.0/include/
  external/glad/include/
  src/
)

set(ALL_LIBS
  ${OPENGL_LIBRARY}
  GLFW_303
  GLEW_190
)

add_definitions(
  -DTW_STATIC
  -DTW_NO_LIB_PRAGMA
  -DTW_NO_DIRECT3D
  -DGLEW_STATIC
  -D_CRT_SECURE_NO_WARNINGS
)

add_executable(main src/main.cpp)
target_link_libraries(main ${ALL_LIBS})
