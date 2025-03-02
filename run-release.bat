@echo off

call build-release.bat
pushd build\Release\

AntKingdom.exe
popd
