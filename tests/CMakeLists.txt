# Create the executable
add_executable(PasswordSaveExec Savedata.cpp)
target_link_libraries(PasswordSaveExec PRIVATE PasswordSave)

set_target_properties(PasswordSaveExec PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
)

# Create alias for the executable
add_executable(PasswordSave::Exec ALIAS PasswordSaveExec)