cmake_minimum_required(VERSION 3.14)
project(renderer C CXX)
set(CMAKE_CXX_STANDARD 17)

#if (MSVC)
#  # warning level 4 and all warnings as errors
#  add_compile_options(/W4 /WX)
#else()
#  # lots of warnings and all warnings as errors
#  add_compile_options(-Wall -Wextra -pedantic -Werror)
#endif()

add_subdirectory(thirdparty/glfw-3.3.2)

add_definitions(-DGL_SILENCE_DEPRECATION)

file(GLOB SOURCES src/*.cc src/*.h)

add_executable(renderer MACOSX_BUNDLE WIN32 ${SOURCES})

if(APPLE)
  list(APPEND EXTRA_LIBS "-framework OpenGL")
elseif(WIN32)
  list(APPEND EXTRA_LIBS "-lglu32 -lopengl32")
  set(CMAKE_EXE_LINKER_FLAGS "-std=gnu99 -static -static-libgcc -static-libstdc++ -mwindows")
else()
  list(APPEND EXTRA_LIBS "-lGL -lGLU -lX11")
endif()

target_link_libraries(renderer glfw ${EXTRA_LIBS})
