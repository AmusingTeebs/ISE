
###################################
## ISE Create Dirs
###################################
## Create the following directories
## ISE/bin
## ISE/data
## ISE/docs
## ISE/images
## ISE/models
## ISE/scripts
## ISE/src
## ISE/src/include
## ISE/src/libs
###################################

macro(ISECreateDirs)

# Get the default path to setup the project
set(ISE_PATH $ENV{ISEDir})
set(ISE_SRC_PATH ${ISE_PATH}/src)

# Create default core directories
file(MAKE_DIRECTORY ${ISE_PATH}/bin)
file(MAKE_DIRECTORY ${ISE_PATH}/data)
file(MAKE_DIRECTORY ${ISE_PATH}/docs)
file(MAKE_DIRECTORY ${ISE_PATH}/images)
file(MAKE_DIRECTORY ${ISE_PATH}/include)
file(MAKE_DIRECTORY ${ISE_PATH}/lib)
file(MAKE_DIRECTORY ${ISE_PATH}/models)
file(MAKE_DIRECTORY ${ISE_PATH}/scripts)

endmacro(ISECreateDirs)

###################################
## ISE Find Qt Console
###################################
## Find all of the Qt console modules
## Adds the modules to Additional Include Directories
###################################

macro(ISEFindQtConsole)

find_package(Qt5 COMPONENTS Core Network OpenGl Sql REQUIRED)

endmacro(ISEFindQtConsole)

###################################
## ISE Find Qt GUI
###################################
## Find all of the Qt GUI modules
## Adds the modules to Additional Include Directories
###################################

macro(ISEFindQtGui)

find_package(Qt5 COMPONENTS Core Gui OpenGl Sql WebKit WebKitWidgets Widgets REQUIRED)

endmacro(ISEFindQtGui)

###################################
## ISE Find Qt (Deprecated)
###################################
## Find all of the Qt modules
## Adds the modules to Additional Include Directories
###################################

macro(ISEFindQt)

find_package(Qt5 COMPONENTS Core Gui Network OpenGl Sql WebKit WebKitWidgets Widgets REQUIRED)

endmacro(ISEFindQt)

###################################
## ISE Use Qt Console
###################################
## Utilize all of the Qt console modules
## Adds the modules to Additional Include Directories
###################################

macro(ISEUseQtConsole)

qt5_use_modules(${PROJECT_NAME} Core Network Sql)

endmacro(ISEUseQtConsole)

###################################
## ISE Use Qt GUI
###################################
## Utilize all of the Qt GUI modules
## Adds the modules to Additional Include Directories
###################################

macro(ISEUseQtGui)

qt5_use_modules(${PROJECT_NAME} Core Gui Network Sql WebKit WebKitWidgets Widgets)

endmacro(ISEUseQtGui)

###################################
## ISE Use Qt (Deprecated)
###################################
## Utilize all of the Qt modules
## Adds the modules to Additional Include Directories
###################################

macro(ISEUseQt)

qt5_use_modules(${PROJECT_NAME} Core Gui Network Sql WebKit WebKitWidgets Widgets)

endmacro(ISEUseQt)

macro(ISEDebugSettings)

# Creates CMake variable to ISEDir environment variable
set(ISE_PATH $ENV{ISEDir})
# Create variable to cmake/template directory
set(TEMPLATE_PATH "${ISE_PATH}/src/cmake/templates")

# Create variable to ISE/bin directory
set(ISE_BIN_PATH "${ISE_PATH}/bin")
# Create variable to ISE/bin/Debug directory
set(ISE_DEBUG_PATH "${ISE_BIN_PATH}/Debug")
# Create variable to ISE/bin/Release directory
set(ISE_RELEASE_PATH "${ISE_BIN_PATH}/Release")

# Create variable to ISE debug executable
set(ISE_DEBUG_EXE "${ISE_DEBUG_PATH}/ISE.exe")
# Create variable to ISE release executable
set(ISE_RELEASE_EXE "${ISE_RELEASE_PATH}/ISE.exe")

# Generate the user profile containing debug information
configure_file("${TEMPLATE_PATH}/visual_studio_2010.vcxproj.user" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.vcxproj.user" NEWLINE_STYLE WIN32)
	  
endmacro(ISEDebugSettings)

###################################
## ISE Config
###################################
## Setup variables for each project
## Should be the first line in each project's CMakeList.txt
###################################

macro(ISEConfig)

# Supress all of Microsoft's dumb warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CRT_SECURE_NO_DEPRECATE /arch:SSE2 /Oi /Ob2 /MP")

# Creates CMake variable to ISEDir environment variable
set(ISE_PATH $ENV{ISEDIR})

# Creates variable to ISE/bin
set(ISE_BIN "${ISE_PATH}/bin")
# Creates variable to ISE/src/include directory
set(ISE_INCLUDE "${ISE_PATH}/include")
# Creates variable to ISE/src/lib
set(ISE_LIB "${ISE_PATH}/lib")

# Set the output directory for libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ISE_BIN})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ISE_LIB})
set(ARCHIVE_OUTPUT_DIRECTORY ${ISE_LIB})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ISE_LIB})

# Tells CMake where to look for library files
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# Create CMake variables
set(CMAKE_PREFIX_PATH $ENV{WinLib})
set(QT_DIR $ENV{Qt_PATH})
set(QT_PATH "${QT_DIR}/bin")

# Set AutoMoc variables
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

endmacro(ISEConfig)

###################################
## ISE Install
###################################
## Copy over the contents for the common ISE dirs
###################################

macro(ISEInstall)

# Copy all of the header file to src/include directory
install(FILES ${PROJECT_HEADERS} DESTINATION ${ISE_INCLUDE})

# Copy the images directory to ISE/images
if(EXISTS "${PROJECT_SOURCE_DIR}/images") 
	install(DIRECTORY "${PROJECT_SOURCE_DIR}/images" DESTINATION ${ISE_PATH})
endif(EXISTS "${PROJECT_SOURCE_DIR}/images")

# Copy the data directory to ISE/data
if(EXISTS "${PROJECT_SOURCE_DIR}/data") 
	install(DIRECTORY "${PROJECT_SOURCE_DIR}/data" DESTINATION ${ISE_PATH})
endif(EXISTS "${PROJECT_SOURCE_DIR}/data")
	
# Copy the docs directory to ISE/docs
if(EXISTS "${PROJECT_SOURCE_DIR}/docs") 
	install(DIRECTORY "${PROJECT_SOURCE_DIR}/docs" DESTINATION ${ISE_PATH})
endif(EXISTS "${PROJECT_SOURCE_DIR}/docs")

# Copy the models directory to ISE/models
if(EXISTS "${PROJECT_SOURCE_DIR}/models") 
	install(DIRECTORY "${PROJECT_SOURCE_DIR}/models" DESTINATION ${ISE_PATH})
endif(EXISTS "${PROJECT_SOURCE_DIR}/models")

# Copy the scripts directory to ISE/scripts
if(EXISTS "${PROJECT_SOURCE_DIR}/scripts") 
	install(DIRECTORY "${PROJECT_SOURCE_DIR}/scripts" DESTINATION ${ISE_PATH})
endif(EXISTS "${PROJECT_SOURCE_DIR}/scripts")

# Add prebuild command to copy over the neccessary files
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND 
				   ${CMAKE_COMMAND} -DBUILD_TYPE=$(Configuration)
				   -P cmake_install.cmake)
				   
ISEDebugSettings()
				   
endmacro(ISEInstall)

###################################
## ISE Install Qt Plugins
###################################
## Copy over all of the Qt Plugins into bin
###################################

macro(ISEInstallQtPlugins)

# Get the Qt default paths
set(QT_DIR $ENV{Qt_PATH})
set(QT_PLATFORM_PATH "${QT_DIR}/plugins/platforms")
set(QT_ACCESS_PATH "${QT_DIR}/plugins/accessible")

# Find the accessible DLLs for debug
set(QT_ACCESS_DLLS_DEBUG ${QT_ACCESS_DLLS_DEBUG}
	${QT_ACCESS_PATH}/qtaccessiblequickd.dll
	${QT_ACCESS_PATH}/qtaccessiblewidgetsd.dll)
	
# Find the accessible DLLs for release
set(QT_ACCESS_DLLS_RELEASE ${QT_ACCESS_DLLS_RELEASE}
	${QT_ACCESS_PATH}/qtaccessiblequick.dll
	${QT_ACCESS_PATH}/qtaccessiblewidgets.dll)

# Find the platform DLLs for debug
set(QT_PLATFORM_DLLS_DEBUG ${QT_PLATFORM_DLLS_DEBUG}
	${QT_PLATFORM_PATH}/qminimald.dll
	${QT_PLATFORM_PATH}/qoffscreend.dll
	${QT_PLATFORM_PATH}/qwindowsd.dll)
	
# Find the platform DLLs for release
set(QT_PLATFORM_DLLS_RELEASE ${QT_PLATFORM_DLLS_RELEASE}
	${QT_PLATFORM_PATH}/qminimal.dll
	${QT_PLATFORM_PATH}/qoffscreen.dll
	${QT_PLATFORM_PATH}/qwindows.dll)

# Install all of the Qt DLLs
install(FILES ${QT_PLATFORM_DLLS_DEBUG} DESTINATION ${ISE_BIN}/Debug/platforms)
install(FILES ${QT_ACCESS_DLLS_DEBUG} DESTINATION ${ISE_BIN}/Debug/accessible)

install(FILES ${QT_PLATFORM_DLLS_RELEASE} DESTINATION ${ISE_BIN}/Release/platforms)
install(FILES ${QT_ACCESS_DLLS_RELEASE} DESTINATION ${ISE_BIN}/Release/accessible)

endmacro(ISEInstallQtPlugins)

###################################
## ISE Install Qt DLLs
###################################
## Copy over all of the Qt DLLs into bin
###################################

macro(ISEInstallQtDlls)

# Get the Qt default paths
set(QT_DIR $ENV{Qt_PATH})
set(QT_BIN_PATH "${QT_DIR}/bin")

# Find all of the icu DLLs
# This are needed for debug and release
file(GLOB QT_ICU_DLLS "${QT_DIR}/bin/icu*.dll")

# Create a list of the all the Qt Debug DLLs
set(QT_DLLS_DEBUG ${QT_DLLS_DEBUG}
	${QT_PATH}/Enginiod.dll
	${QT_PATH}/Qt5Bluetoothd.dll
	${QT_PATH}/Qt5CLucened.dll
	${QT_PATH}/Qt5Concurrentd.dll
	${QT_PATH}/Qt5Cored.dll
	${QT_PATH}/Qt5Declaratived.dll
	${QT_PATH}/Qt5Designerd.dll
	${QT_PATH}/Qt5DesignerComponentsd.dll
	${QT_PATH}/Qt5Guid.dll
	${QT_PATH}/Qt5Helpd.dll
	${QT_PATH}/Qt5Multimediad.dll
	${QT_PATH}/Qt5MultimediaQuick_pd.dll
	${QT_PATH}/Qt5MultimediaWidgetsd.dll
	${QT_PATH}/Qt5Networkd.dll
	${QT_PATH}/Qt5Nfcd.dll
	${QT_PATH}/Qt5OpenGLd.dll
	${QT_PATH}/Qt5Positioningd.dll
	${QT_PATH}/Qt5PrintSupportd.dll
	${QT_PATH}/Qt5Qmld.dll
	${QT_PATH}/Qt5Quickd.dll
	${QT_PATH}/Qt5QuickParticlesd.dll
	${QT_PATH}/Qt5QuickTestd.dll
	${QT_PATH}/Qt5QuickWidgetsd.dll
	${QT_PATH}/Qt5Scriptd.dll
	${QT_PATH}/Qt5Sensorsd.dll
	${QT_PATH}/Qt5SerialPortd.dll
	${QT_PATH}/Qt5Sqld.dll
	${QT_PATH}/Qt5Svgd.dll
	${QT_PATH}/Qt5Testd.dll
	${QT_PATH}/Qt5WebKitd.dll
	${QT_PATH}/Qt5WebKitWidgetsd.dll
	${QT_PATH}/Qt5WebSocketsd.dll
	${QT_PATH}/Qt5Widgetsd.dll
	${QT_PATH}/Qt5WinExtrasd.dll
	${QT_PATH}/Qt5Xmld.dll
	${QT_PATH}/Qt5XmlPatternsd.dll)

# Create a list of the all the Qt Release DLLs
set(QT_DLLS_RELEASE ${QT_DLLS_RELEASE}
	${QT_PATH}/Enginio.dll
	${QT_PATH}/Qt5Bluetooth.dll
	${QT_PATH}/Qt5CLucene.dll
	${QT_PATH}/Qt5Concurrent.dll
	${QT_PATH}/Qt5Core.dll
	${QT_PATH}/Qt5Declarative.dll
	${QT_PATH}/Qt5Designer.dll
	${QT_PATH}/Qt5DesignerComponents.dll
	${QT_PATH}/Qt5Gui.dll
	${QT_PATH}/Qt5Help.dll
	${QT_PATH}/Qt5Multimedia.dll
	${QT_PATH}/Qt5MultimediaQuick_p.dll
	${QT_PATH}/Qt5MultimediaWidgets.dll
	${QT_PATH}/Qt5Network.dll
	${QT_PATH}/Qt5Nfc.dll
	${QT_PATH}/Qt5OpenGL.dll
	${QT_PATH}/Qt5Positioning.dll
	${QT_PATH}/Qt5PrintSupport.dll
	${QT_PATH}/Qt5Qml.dll
	${QT_PATH}/Qt5Quick.dll
	${QT_PATH}/Qt5QuickParticles.dll
	${QT_PATH}/Qt5QuickTest.dll
	${QT_PATH}/Qt5QuickWidgets.dll
	${QT_PATH}/Qt5Script.dll
	${QT_PATH}/Qt5Sensors.dll
	${QT_PATH}/Qt5SerialPort.dll
	${QT_PATH}/Qt5Sql.dll
	${QT_PATH}/Qt5Svg.dll
	${QT_PATH}/Qt5Test.dll
	${QT_PATH}/Qt5WebKit.dll
	${QT_PATH}/Qt5WebKitWidgets.dll
	${QT_PATH}/Qt5WebSockets.dll
	${QT_PATH}/Qt5Widgets.dll
	${QT_PATH}/Qt5WinExtras.dll
	${QT_PATH}/Qt5Xml.dll
	${QT_PATH}/Qt5XmlPatterns.dll)

# Install all of the Qt DLLs
install(FILES ${QT_DLLS_DEBUG} DESTINATION ${ISE_BIN}/Debug)	
install(FILES ${QT_ICU_DLLS} DESTINATION ${ISE_BIN}/Debug)	

install(FILES ${QT_DLLS_RELEASE} DESTINATION ${ISE_BIN}/Release)
install(FILES ${QT_ICU_DLLS} DESTINATION ${ISE_BIN}/Release)

endmacro(ISEInstallQtDlls)

macro(ISEInstallQt)

# Install all of the Qt DLLs
ISEInstallQtDlls()
# Install all of the plugins
ISEInstallQtPlugins()

endmacro(ISEInstallQt)