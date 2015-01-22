# Set the required CMake version
cmake_minimum_required(VERSION 3.0) 

# Set the location of the ISE configuration files
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

# Sets the build configurations
include(ISEConfig)

# Create the directory structure for ISE
ISECreateDirs()

# Set the name of the solution
project(ISECore)

# Add each of the associated projects
add_subdirectory(ISE)
add_subdirectory(GameViewer)
