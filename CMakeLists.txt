cmake_minimum_required(VERSION 3.31)
project(PasswordSave)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)

add_library(PasswordSave SHARED src/PasswordSave.cpp)

set_target_properties(PasswordSave PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
)

#install(DIRECTORY include/ DESTINATION include)

add_executable(PasswordSaveExec tests/Savedata.cpp)
target_link_libraries(PasswordSaveExec PRIVATE PasswordSave)
set_target_properties(PasswordSaveExec PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
)
