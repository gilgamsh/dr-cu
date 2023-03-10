#########
# Setup #
#########

# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Message
message(STATUS "Incremental Design Rule Checking for ISPD 2018/19")
message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Project's name
project(idrc)

# Set the output folder where your program will be created
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PATH_RSYN ${CMAKE_CURRENT_SOURCE_DIR}/../rsyn)
set(PATH_IDRC ${CMAKE_CURRENT_SOURCE_DIR})

###################
# Warnings/Errors #
###################

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Werror=return-type")

######################
# Check Dependencies #
######################
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS filesystem program_options REQUIRED)

###############
# Source Code #
###############
file(GLOB_RECURSE SRC_FILES_RSYN
    ${PATH_RSYN}/src/*.cpp
    ${PATH_RSYN}/src/*.cc
    ${PATH_RSYN}/src/*.c)

file(GLOB_RECURSE SRC_FILES_IDRC ${PATH_IDRC}/*.cpp)

set(SRC_FILES ${SRC_FILES_RSYN} ${SRC_FILES_IDRC})

#################
# Library Paths #
#################
# Need to come before target is created.

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
link_directories(${PATH_RSYN}/lib/linux)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
link_directories(${PATH_RSYN}/lib/macosx)
endif()

###########
# Targets #
###########

add_executable(idrc ${SRC_FILES})

#######################
# Include Directories #
#######################

include_directories(${PATH_RSYN}/src)
include_directories(${PATH_RSYN}/src/rsyn/export)
include_directories(${PATH_RSYN}/include)
include_directories(${PATH_IDRC})

#################
# Linker Flags  #
#################

# TODO: set static under release mode only
set_target_properties(idrc PROPERTIES LINK_FLAGS "-static -Wl,--whole-archive -rdynamic -lpthread -Wl,--no-whole-archive")

# Threads
# target_link_libraries(idrc ${CMAKE_THREAD_LIBS_INIT})

# LEF/DEF
target_link_libraries(idrc lef)
target_link_libraries(idrc def)

# Boost
target_include_directories(idrc PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(idrc ${Boost_LIBRARIES})
