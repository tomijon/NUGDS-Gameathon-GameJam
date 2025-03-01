@echo off

if not exist build/Release (
    @echo Relaese build not found.
    @echo Building in Release Mode...
    call build-release.bat
)
pushd build\Release\

OpenGLApplication.exe
popd
