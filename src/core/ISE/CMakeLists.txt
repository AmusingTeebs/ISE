# Set the necessary variables
ISEConfig()

# Create the project
project(ISE) 

# Find all of the Qt packages 
ISEFindQt()
  
# Add all header and source files to the project
file(GLOB PROJECT_HEADERS *.h)  
file(GLOB PROJECT_SOURCES *.cpp)  
   
# Create separate directory for resource files 
file(GLOB PROJECT_RESOURCES *.rc) 
source_group("Resource Files" FILES ${PROJECT_RESOURCES})

# Set the include directories 
include_directories(${INCLUDE_DIR} ${ISE_INCLUDE} GameViewer)

# Add the executable 
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_RESOURCES})

# Set the library links
target_link_libraries(${PROJECT_NAME} GameViewer)

# Sets the build order 
#add_dependencies(${PROJECT_NAME} GameViewer)

# Use all of the Qt packages
ISEUseQt()

# Install the Qt DLLs in the bin directory
ISEInstallQt()

# Install the common ISE directories
ISEInstall() 