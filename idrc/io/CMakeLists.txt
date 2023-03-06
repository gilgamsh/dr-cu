cmake_minimum_required(VERSION 3.1)

message(STATUS "project io for r/w lef/def files")
project(io LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# ##############################################################################
# Src Files
# ##############################################################################

set(PATH_RSYN ${CMAKE_CURRENT_SOURCE_DIR}/../../rsyn)

file(GLOB_RECURSE SRC_FILES_RSYN ${PATH_RSYN}/src/*.cpp ${PATH_RSYN}/src/*.cc
     ${PATH_RSYN}/src/*.c)

file(GLOB_RECURSE SRC_FILES_IO ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/*.cc ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

set(SRC_FILES ${SRC_FILES_IO} ${SRC_FILES_RSYN})

# ##############################################################################
# Library Paths #
# ##############################################################################
# Need to come before target is created.

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  link_directories(${PATH_RSYN}/lib/linux)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  link_directories(${PATH_RSYN}/lib/macosx)
endif()

# ##############################################################################
# Include Directories #
# ##############################################################################


add_library(io ${SRC_FILES})

target_include_directories(io PRIVATE ${PATH_RSYN}/src)
target_include_directories(io PRIVATE ${PATH_RSYN}/src/rsyn/io/reader)
target_include_directories(io PRIVATE ${PATH_RSYN}/src/rsyn/export)
target_include_directories(io PRIVATE ${PATH_RSYN}/include)

target_include_directories(io PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(io lef def)
target_compile_options(
  io
  PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/W4>
          $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall
          -Wextra
          -Wpedantic
          -O3>
          $<$<COMPILE_LANGUAGE:CUDA>:--extended-lambda
          --expt-relaxed-constexpr>)

add_executable(io_test ${CMAKE_CURRENT_SOURCE_DIR}/io_test.cpp)

target_link_libraries(io_test io)
target_compile_options(
  io_test
  PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/W4>
          $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall
          -Wextra
          -Wpedantic
          -O3>
          $<$<COMPILE_LANGUAGE:CUDA>:--extended-lambda
          --expt-relaxed-constexpr>)