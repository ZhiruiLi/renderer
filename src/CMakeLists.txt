find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
  message(ERROR "OPENGL not found!")
endif(NOT OPENGL_FOUND)

add_definitions(-DGL_SILENCE_DEPRECATION)

file(GLOB SOURCES LIST_DIRECTORIES TRUE
  "${PROJECT_SOURCE_DIR}/src/*.cc"
  "${PROJECT_SOURCE_DIR}/src/*.h")

add_executable(renderer MACOSX_BUNDLE WIN32 ${SOURCES})

list(APPEND EXTRA_LIBS ${OPENGL_LIBRARIES})
target_link_libraries(renderer glfw ${EXTRA_LIBS})

