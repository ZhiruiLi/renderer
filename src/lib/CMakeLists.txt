file(GLOB SOURCES LIST_DIRECTORIES TRUE
  "${PROJECT_SOURCE_DIR}/src/lib/*.cc"
  "${PROJECT_SOURCE_DIR}/src/lib/*.h")

add_library(lib ${SOURCES})

