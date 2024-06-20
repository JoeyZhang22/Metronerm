# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(MyProject CXX)

# Add all source files in the 'src' directory to the variable 'SOURCES'
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h" "src/*.hpp")  # Include header files

# Define the executable target
add_executable(metronal ${SOURCES})
