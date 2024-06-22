# # Minimum required version of CMake
# cmake_minimum_required(VERSION 3.10)

# # Project name and language
# project(MyProject CXX)

# # Add all source files in the 'src' directory to the variable 'SOURCES'
# file(GLOB SOURCES "src/*.cpp")
# file(GLOB HEADERS "include/*.h" "src/*.hpp")  # Include header files

# # Define the executable target
# add_executable(metronal ${SOURCES})



# cmake_minimum_required(VERSION 3.10)

# # Project name
# project(Metronome)

# # # Specify the C++ standard
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# # Find and include libao
# find_path(LIBAO_INCLUDE_DIRS NAMES ao
#   PATHS /opt/homebrew/opt/libao/include 
# )

# find_path(LIBAO_INCLUDE_DIRS NAMES sndfile
#   PATHS /opt/homebrew/opt/libsndfile/include
# )

# # Include directories for libao and libsndfile
# include_directories(${LIBAO_INCLUDE_DIRS})
# include_directories(${LIBSNDFILE_INCLUDE_DIRS})

# # Include directory for project headers (if any)
# include_directories(${PROJECT_SOURCE_DIR}/include)

# # Add all source files in the 'src' directory to the variable 'SOURCES'
# file(GLOB SOURCES "src/*.cpp")
# file(GLOB HEADERS "include/*.h" "src/*.hpp")  # Include header files

# # Add the executable
# add_executable(Metronome ${SOURCES} ${HEADERS})

# # Link libraries
# target_link_libraries(Metronome ${LIBAO_LIBRARIES} ${LIBSNDFILE_LIBRARIES})


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

# Find and include libsndfile
find_path(LIBSNDFILE_INCLUDE_DIR sndfile.h
    PATH_SUFFIXES include
    HINTS /opt/homebrew/opt/libsndfile
)

# Include directories for libao and libsndfile
include_directories(${LIBAO_INCLUDE_DIR})
include_directories(${LIBSNDFILE_INCLUDE_DIR})

# Add all source files in the 'src' directory to the variable 'SOURCES'
file(GLOB SOURCES "src/*.cpp")

# Add the executable
add_executable(Metronome ${SOURCES})

# Link libraries
find_library(LIBAO_LIBRARIES NAMES ao
    HINTS /opt/homebrew/opt/libao/lib
)

find_library(LIBSNDFILE_LIBRARIES NAMES sndfile
    HINTS /opt/homebrew/opt/libsndfile/lib
)

target_link_libraries(Metronome ${LIBAO_LIBRARIES} ${LIBSNDFILE_LIBRARIES})
