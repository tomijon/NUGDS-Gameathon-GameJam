@echo off

if not exist build/Debug (
    @echo Relaese build not found.
    @echo Building in Debug Mode...
    call build-Debug.bat
)
pushd build\Debug\

AntKingdom.exe
popd
