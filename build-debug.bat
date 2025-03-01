@echo off

if not exist build/ (
    call setup.bat
)


cmake --build build --config Debug
