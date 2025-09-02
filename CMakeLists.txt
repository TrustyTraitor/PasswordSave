cmake_minimum_required(VERSION 3.31)
project(PasswordSave)

set(CMAKE_CXX_STANDARD 23)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Include headers
include_directories(include)

# Create the shared library
add_library(PasswordSave SHARED src/PasswordSave.cpp)
add_library(PasswordSave::Lib ALIAS PasswordSave)

# Optionally add the executable if requested via subdirectory
if(TARGET PasswordSaveExec)
    # Create a meta-target "Full" that includes both
    add_library(PasswordSave::Full INTERFACE)
    target_link_libraries(PasswordSave::Full INTERFACE PasswordSave::Lib PasswordSave::Exec)
endif()