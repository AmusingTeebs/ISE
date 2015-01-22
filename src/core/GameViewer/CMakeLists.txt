# Set the necessary variables
ISEConfig()

# Create the project
project(GameViewer) 

# Find all of the Qt packages
ISEFindQt()

# Add all header and source files to the project
file(GLOB PROJECT_HEADERS *.h)
file(GLOB PROJECT_SOURCES *.cpp) 

# Set the include directories
include_directories(${INCLUDE_DIR} ${SPECTR_INCLUDE})
   
# Add the header and source files 
add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES} ${PROJECT_HEADERS})
 
# Set the library links
target_link_libraries(${PROJECT_NAME}) 

#add_dependencies(${PROJECT_NAME}) 
 
# Use all of the Qt packages 
ISEUseQt()
  
# Install the Qt DLLs in the bin directory
ISEInstall()
 