# CMake for MGE
#
#

# Build options
set_option(BUILD_EXAMPLES TRUE BOOL "If example applications should be build" )

# setup version numbers
set(MGE_VERSION_MAJOR 0)
set(MGE_VERSION_MINOR 22)
set(MGE_VERSION_PATCH 4)
set(MGE_VERSION "${MGE_VERSION_MAJOR}.${MGE_VERSION_MINOR}.${MGE_VERSION_PATCH}")

# define the path of our additional CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/Modules/)

# set up include-directories
include_directories(
  "${PROJECT_SOURCE_DIR}/include"
  )

# add the examples subdirectory
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

