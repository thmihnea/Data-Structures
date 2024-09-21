# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(DataStructures VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Base source directory
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

# Include directories
include_directories(${SRC_DIR})
include_directories(${SRC_DIR}/collection)
include_directories(${SRC_DIR}/connectivity)
include_directories(${SRC_DIR}/sort)
include_directories(${SRC_DIR}/table)

# Collect all source files
set(SOURCES
    ${SRC_DIR}/collection/Heap.cpp
    ${SRC_DIR}/collection/Stack.cpp
    ${SRC_DIR}/connectivity/UnionFind.cpp
    ${SRC_DIR}/sort/Sort.cpp
    ${SRC_DIR}/table/HashTable.cpp
)

# Add executable
add_executable(data-structures ${SOURCES})
