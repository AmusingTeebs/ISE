@echo off

REM The build path to configure
set buildPath=%1 
REM The architecture type (32 or 64 bit)
set arch=%2
REM Performs a clean up (deletes build)
set clean=%3
REM Performs a Visual Studio compile in debug
set debug=%4
REM Performs a Visual Studio compile in release
set release=%5
REM Performs a Doxygen 
set doxy=%6

REM Move to the give build directory
cd %buildPath%

REM Clean the build directory if necessary
if %clean% == 1 ( IF EXIST build rmdir /s /q build )
IF NOT EXIST build mkdir build

REM Move into the build directory
cd build

REM CMake Visual Studio with 32bit Configuration
if %arch% == 32 cmake .. -G "Visual Studio 10"
REM CMake Visual Studio with 64bit Configuration
if %arch% == 64 cmake .. -G "Visual Studio 10 Win64"

REM Build in debug
if %debug% == 1 cmake --build . --config Debug
REM Build in release
if %release% == 1 cmake --build . --config Release

REM Execute Doxygen command
if %doxy% == 1 doxygen %buildPath%/Docs