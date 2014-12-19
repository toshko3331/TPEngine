@echo off
cd ..
REM removing and rebuilding the path to our project
rmdir build /s /q
mkdir build
cd build
mkdir Debug
mkdir Release
REM This is just to set the variables of the path since we need to copy
cd Debug
set "Debug=%cd%"
cd ..
cd Release
set "Release=%cd%"
cd ..
cd ..
cd Software-Rendering
cd lib
cd SDL2
cd x86
COPY /B SDL2.dll %Debug%
COPY /B SDL2.dll %Release%