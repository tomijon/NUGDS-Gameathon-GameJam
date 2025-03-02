@echo off

call build-Debug.bat
pushd build\Debug\

AntKingdom.exe
popd
