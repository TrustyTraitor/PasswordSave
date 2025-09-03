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

target_include_directories(PasswordSave
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>  # Optional, if you support installation
)

add_library(PasswordSaveFull INTERFACE)
target_link_libraries(PasswordSaveFull INTERFACE PasswordSave::Lib)

if(TARGET PasswordSave::Exec)
    target_link_libraries(PasswordSaveFull INTERFACE PasswordSave::Exec)
endif()

add_library(PasswordSave::Full ALIAS PasswordSaveFull)