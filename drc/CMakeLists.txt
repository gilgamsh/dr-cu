cmake_minimum_required(VERSION 3.1)

project(drc
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



add_subdirectory(io)


############################################################
# Create a library
############################################################

set (GLOB_RECURSE DRC_SOURCES
    ${PROJECT_SOURCE_DIR}/drc/*.cpp
    ${PROJECT_SOURCE_DIR}/drc/*.cc
    ${PROJECT_SOURCE_DIR}/drc/*.hpp
    ${PROJECT_SOURCE_DIR}/drc/*.h
)

add_library( libdrc
  ${DRC_SOURCES}
)

set_target_properties(libdrc PROPERTIES OUTPUT_NAME "drc")

target_include_directories(libdrc
  PUBLIC
    ${PROJECT_SOURCE_DIR}/drc
)

target_link_libraries(libdrc
  libio
)

############################################################
# Create an executable
############################################################

add_executable(drc
  ${PROJECT_SOURCE_DIR}/main.cpp
)

target_link_libraries(drc
  libdrc
)

