# # Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(Metronome)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find and include libao
find_path(LIBAO_INCLUDE_DIR ao/ao.h
    PATH_SUFFIXES include
    HINTS /opt/homebrew/opt/libao
)

find_path(PORTAUDIO_INCLUDE_DIR portaudio.h
    PATH_SUFFIXES include
    HINTS /opt/homebrew/opt/portaudio
)

# Include directories for libao and portaudio
include_directories(${LIBAO_INCLUDE_DIR})
include_directories(${PORTAUDIO_INCLUDE_DIR})

# Add all source files in the 'src' directory to the variable 'SOURCES'
file(GLOB SOURCES "src/*.cpp")

# Add the executable
add_executable(Metronome ${SOURCES})

# Link libraries
find_library(LIBAO_LIBRARIES NAMES ao
    HINTS /opt/homebrew/opt/libao/lib
)

find_library(PORTAUDIO_LIBRARIES NAMES portaudio
    HINTS /opt/homebrew/opt/portaudio/lib
)

target_link_libraries(Metronome ${LIBAO_LIBRARIES} ${PORTAUDIO_LIBRARIES})
