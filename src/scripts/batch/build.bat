@echo off

REM Path to ISE src directory
set srcPath=%ISEDir%/src
REM Path to ISE batch scripts directory
set batchPath=%srcPath%/scripts/batch
REM Path to ISE core directory
set corePath=%srcPath%/core
REM Path to ISE modules directory
set modulesPath=%srcPath%/modules

REM The architecture type (32 or 64 bit)
set arch=32

REM Configure the "core" directory
set core=0
REM Configure the "modules" directory
set modules=0
REM Configure all of the projects
set all=0

REM Performs a full clean up (deletes bin, lib and include)
set fullClean=0
REM Performs a clean up (deletes build)
set clean=0

REM Performs a Visual Studio compile in debug
set debug=0
REM Performs a Visual Studio compile in release
set release=0

REM Performs a Doxygen 
set doxy=0

REM Loop through all of the input variables
for %%a in (%*) do (

	REM Set the build architecture
	if [%%a] == [-32] set arch=32
	if [%%a] == [-64] set arch=64
	
	REM Set the affected directories
	if [%%a] == [-core] set core=1
	if [%%a] == [-modules] set modules=1
	
	REM Capture the ALL command
	if [%%a] == [-all] set core=1
	if [%%a] == [-all] set modules=1
	
	REM Set cleaning tasks
	if [%%a] == [-fc] set fullClean=1
	if [%%a] == [-c] set clean=1
		
	REM Set build tasks
	if [%%a] == [-debug] set debug=1
	if [%%a] == [-release] set release=1
		
	REM Set documentation
	if [%%a] == [-doxy] set doxy=1
)

REM Perform a full clean on ISE
if %fullClean% == 1 (
call fullClean
cd ..
cd ..
)

REM Configure the ISE/src/core solution
if %core% == 1 (
	echo Configuring ISE/src/core...
	cd %batchPath%
	call config %corePath% %arch% %clean% %debug% %release% %doxy%
)

REM Configure the ISE/src/plugins solution
if %modules% == 1 (
	echo Configuring ISE/src/modules...
	cd %batchPath%
	call config %modulesPath% %arch% %clean% %debug% %release% %doxy%
)

cd %batchPath%