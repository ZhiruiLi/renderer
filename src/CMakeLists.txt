file(GLOB SOURCES LIST_DIRECTORIES TRUE
  "${PROJECT_SOURCE_DIR}/src/*.cc"
  "${PROJECT_SOURCE_DIR}/src/*.h")

add_executable(renderer MACOSX_BUNDLE WIN32 ${SOURCES})

list(APPEND EXTRA_LIBS ${OPENGL_LIBRARIES} glfw)
target_link_libraries(renderer lib ${EXTRA_LIBS})

