cmake_minimum_required(VERSION 3.31)
project(PasswordSave)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)

add_library(PasswordSave SHARED src/PasswordSave.cpp)

#set_target_properties(PasswordSave PROPERTIES
#        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin
#        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib
#        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib
#)

#install(DIRECTORY include/ DESTINATION include)

add_executable(PasswordSaveTest tests/Savedata.cpp)
