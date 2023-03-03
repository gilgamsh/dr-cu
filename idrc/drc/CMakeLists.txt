project(drc)

set (GLOB_RECURSE DRC_SOURCES
    ${PROJECT_SOURCE_DIR}/drc/*.cpp
    ${PROJECT_SOURCE_DIR}/drc/*.cc
    ${PROJECT_SOURCE_DIR}/drc/*.hpp
    ${PROJECT_SOURCE_DIR}/drc/*.h
)

add_library( libdrc
  ${DRC_SOURCES}
)

target_include_directories(libdrc
  INTERFACE
    ${PROJECT_SOURCE_DIR}/drc
)