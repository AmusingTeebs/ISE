@echo off

REM ISE greeting
echo.
echo Hey dude!
echo I need your assistance locating a couple files...
echo Please note, your compiler (Windows 98) would prefer you to use / over \

REM ISE Path Example
echo.            
echo First, where is your ISE directory located? 
echo For example: C:/Projects/ISE

REM Get the path to ISE input
set /p ISEPath=ISE File Path:

REM Qt Path Example
echo.
echo Next, where is your Qt directory located?
echo This is the directory containing bin, lib, plugins, etc...
echo Recommended: C:/Projects/Qt/5.4/msvc2010_opengl

REM Get the path to Qt
set /p qtPath=Qt File Path:

REM Environment variable pointing to top level ISE directory (used by ISE)
setx ISEDIR "%ISEPath%"

REM Add the scripts/batch path to PATH variable
set localPath=%PATH%;%ISEPath%/src/scripts/batch
setx PATH "%localPath%"

REM Inform user about PATH variable enhancement
echo.
echo BTW - I've added the scripts directory to your PATH variable...
echo That means you can call ISE commands like build from any command prompt...

REM Environment variable pointing to top level Qt directory (used by ISE)
setx Qt_PATH %qtPath%
REM Environment variable pointing to Qt CMake scripts (used by CMake/Qt)
setx Qt5_DIR %qtPath%"/lib/cmake/Qt5"
REM Environment variable pointing to GLU (used by CMake/Qt)
setx WinLib "C:/Program Files (x86)/Microsoft SDKs/Windows/v7.0A/Lib"

REM Good Bye Message
echo.
echo Can you do me a favor???
echo Can you have a GREAT day... 
echo Thanks mate!
echo.

REM Exit Script
pause
exit