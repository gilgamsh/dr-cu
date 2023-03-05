cmake_minimum_required(VERSION 3.1)

project(drc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GLOB_RECURSE
    DRC_SOURCES ${PROJECT_SOURCE_DIR}/drc/*.cpp ${PROJECT_SOURCE_DIR}/drc/*.cc
    ${PROJECT_SOURCE_DIR}/drc/*.hpp ${PROJECT_SOURCE_DIR}/drc/*.h)

add_library(libdrc INTERFACE)

target_include_directories(libdrc INTERFACE ${CMAKE_SOURCE_DIR})