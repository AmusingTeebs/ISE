@echo off

REM Path to ISE src directory
set srcPath=%ISEDir%/src
REM Path to ISE batch scripts directory
set batchPath=%srcPath%/scripts/batch
REM Path to ISE core directory
set corePath=%srcPath%/core
REM Path to ISE plugins directory
set pluginsPath=%srcPath%/modules

echo WARNING: Nuclear Launch Detected...

REM Delete the contents of core/build
cd %corePath%
IF EXIST build rmdir /s /q build
echo Nuked ISE/src/core/build...

REM Delete the contents of plugins/build
cd %pluginsPath%
IF EXIST build rmdir /s /q build
echo Nuked ISE/src/modules/build...

REM Navigate to ISE
cd %ISEDir%

REM Delete the contents of bin
IF EXIST bin rmdir /s /q bin
echo Nuked ISE/bin...

REM Delete the contents of data
IF EXIST data rmdir /s /q data
echo Nuked ISE/data...

REM Delete the contents of data
IF EXIST docs rmdir /s /q docs
echo Nuked ISE/docs...

REM Delete the contents of data
IF EXIST images rmdir /s /q images
echo Nuked ISE/images...

REM Delete the contents of include
IF EXIST include rmdir /s /q include
echo Nuked ISE/include...

REM Delete the contents of lib
IF EXIST lib rmdir /s /q lib
echo Nuked ISE/lib...

REM Delete the contents of lib
IF EXIST scripts rmdir /s /q scripts
echo Nuked ISE/scripts...

REM Navigate back to scripts directory
cd %batchPath%