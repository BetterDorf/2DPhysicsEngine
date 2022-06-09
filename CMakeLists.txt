# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Name of the solution
project ("2dphysicsengine")

# Include sub-projects.
set(EXECUTABLE_CUSTOM_NAME "2DPhysicsEngine")
add_subdirectory ("2DPhysicsEngine")

set(EXECUTABLE_CUSTOM_NAME "Vector")
add_subdirectory ("Vector")

set(EXECUTABLE_CUSTOM_NAME "Sfml")
add_subdirectory ("Sfml")
