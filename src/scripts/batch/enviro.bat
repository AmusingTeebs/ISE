@echo off

REM Spectr greeting
echo.
echo Greetings human...
echo I need your assistance locating a couple files...
echo Please note, your compiler would prefer you to use / over \

REM Spectr Path Example
echo.            
echo First, where is your Spectr directory located? 
echo For example: C:/Projects/Spectr

REM Get the path to SPECTR input
set /p spectrPath=SPECTR File Path:

REM Qt Path Example
echo.
echo Next, where is your Qt directory located?
echo This is the directory containing bin, lib, plugins, etc...
echo For example: C:/Projects/Qt/5.3.1/5.3/msvc2010_opengl

REM Get the path to Qt
set /p qtPath=Qt File Path:

REM Environment variable pointing to top level SPECTR directory (used by SPECTR)
setx SPECTRDIR "%spectrPath%"

REM Add the scripts/batch path to PATH variable
set localPath=%PATH%;%spectrPath%/src/scripts/batch
setx PATH "%localPath%"

REM Inform user about PATH variable enhancement
echo.
echo BTW - I've added the scripts directory to your PATH variable...
echo That means you can call Spectr commands like build from any command prompt...

REM Environment variable pointing to top level Qt directory (used by SPECTR)
setx Qt_PATH %qtPath%
REM Environment variable pointing to Qt CMake scripts (used by CMake/Qt)
setx Qt5_DIR %qtPath%"/lib/cmake/Qt5"
REM Environment variable pointing to GLU (used by CMake/Qt)
setx WinLib "C:/Program Files (x86)/Microsoft SDKs/Windows/v7.0A/Lib"

REM Good Bye Message
echo.
echo Can you do me a favor???
echo Can you have a GREAT day...
echo Can you do that for me?
echo.

REM Exit Script
pause
exit