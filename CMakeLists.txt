# CMake master file for MGE
#
#

# Make sure they are using a recent version of CMake
cmake_minimum_required(VERSION 2.6)

# Project name
project(MGE)

# Include the macros file for this project
include(${PROJECT_SOURCE_DIR}/cmake/macros.cmake)

# Build options
set_option(BUILD_EXAMPLES TRUE BOOL "If example applications should be build" )

# setup version numbers
set(MGE_VERSION_MAJOR 0)
set(MGE_VERSION_MINOR 22)
set(MGE_VERSION_PATCH 4)
set(MGE_VERSION "${MGE_VERSION_MAJOR}.${MGE_VERSION_MINOR}.${MGE_VERSION_PATCH}")

# define the path of our additional CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/Modules/)

#Find external libraires
include_directories(
  "${PROJECT_SOURCE_DIR}/include"
)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# add the MGE subdirectory
message("Configuring MGE...")
add_subdirectory(src/MGE)

# add the examples subdirectory
if(BUILD_EXAMPLES)
	message("Configuring examples...")
    add_subdirectory(examples)
endif()


