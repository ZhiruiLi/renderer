add_definitions(-DGL_SILENCE_DEPRECATION)
file(GLOB SOURCES LIST_DIRECTORIES TRUE
  "${PROJECT_SOURCE_DIR}/src/*.cc"
  "${PROJECT_SOURCE_DIR}/src/*.h")
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

