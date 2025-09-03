cmake_minimum_required(VERSION 3.31)
project(PasswordSave)

set(CMAKE_CXX_STANDARD 23)

# Output directories
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Include headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create the shared library
add_library(PasswordSave SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/src/PasswordSave.cpp)

add_library(PasswordSave::Lib ALIAS PasswordSave)
target_include_directories(PasswordSave PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Internal variable to allow parent projects to enable the executable
set(_PASSWORDSAVE_BUILD_EXECUTABLE FALSE)

# If this is the top-level project, build executable by default
if (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(_PASSWORDSAVE_BUILD_EXECUTABLE TRUE)
endif()

# Allow parent project to override this before including
if (DEFINED PasswordSave_ENABLE_EXECUTABLE)
    set(_PASSWORDSAVE_BUILD_EXECUTABLE ${PasswordSave_ENABLE_EXECUTABLE})
endif()

# Only build executable if requested
if (_PASSWORDSAVE_BUILD_EXECUTABLE)
    add_executable(PasswordSaveExec
            ${CMAKE_CURRENT_SOURCE_DIR}/test/GameSaveTest.cpp
    )
    target_link_libraries(PasswordSaveExec PRIVATE PasswordSave)
    add_executable(PasswordSave::Exec ALIAS PasswordSaveExec)
endif()