add_executable(PasswordSaveExec Savedata.cpp)
target_link_libraries(PasswordSaveExec PRIVATE PasswordSave)

add_executable(PasswordSave::Exec ALIAS PasswordSaveExec)