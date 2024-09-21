cmake_minimum_required(VERSION 3.10)
project(DataStructures)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(src)

# Collect all non-template source files recursively
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Exclude template implementation files (now `.tpp` or included in headers)
list(REMOVE_ITEM SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/collection/Heap.tpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/collection/Stack.tpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/sort/Sort.tpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/table/HashTable.tpp"
)

# Add library target
add_library(DataStructures STATIC ${SOURCES})

# Optionally, add an executable for testing
# add_executable(TestApp src/main.cpp)
# target_link_libraries(TestApp PRIVATE DataStructures)
