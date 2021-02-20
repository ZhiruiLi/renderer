file(GLOB SOURCES LIST_DIRECTORIES TRUE
  "${PROJECT_SOURCE_DIR}/src/*.cc"
  "${PROJECT_SOURCE_DIR}/src/*.h")

if (APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OpenGL_LIBRARY OpenGL)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    SET(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif (APPLE)

if (WIN32)
# nothing now
endif (WIN32)

add_executable(renderer MACOSX_BUNDLE WIN32 ${SOURCES})

target_link_libraries(renderer lib imgui libglew_static glfw ${OPENGL_LIBRARIES} ${EXTRA_LIBS})

