# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(Metronerm)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find libao
find_path(LIBAO_INCLUDE_DIR NAMES ao/ao.h
    PATH_SUFFIXES include
    HINTS /opt/homebrew/opt/libao
)

find_library(LIBAO_LIBRARIES NAMES ao
    HINTS /opt/homebrew/opt/libao/lib
)

# Check if libao was found
if (NOT LIBAO_INCLUDE_DIR OR NOT LIBAO_LIBRARIES)
    message(FATAL_ERROR "libao not found. Please install libao.")
endif()

# Include directories for libao
include_directories(${LIBAO_INCLUDE_DIR})

# Add all source files in the 'src' directory to the variable 'SOURCES'
file(GLOB SOURCES "src/*.cpp")

# Add the executable
add_executable(Metronerm ${SOURCES})

# Link libraries
target_link_libraries(Metronerm ${LIBAO_LIBRARIES})

# Optional: Print the paths to the libraries and includes found
message(STATUS "Using libao include dir: ${LIBAO_INCLUDE_DIR}")
message(STATUS "Using libao library: ${LIBAO_LIBRARIES}")
