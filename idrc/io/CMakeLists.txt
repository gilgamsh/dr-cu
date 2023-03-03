project(io)

set(GLOB_RECURSE IO_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

add_library(libio ${IO_SRCS})

target_include_directories(libio INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})