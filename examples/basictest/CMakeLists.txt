project(basictest)

set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

# all source files
FILE(GLOB SRC ./*.cpp)

# find external SFML libraries
if(WINDOWS)
  find_package(SFML REQUIRED main)
endif(WINDOWS)

# add include paths of external libraries
include_directories(${SFML_INCLUDE_DIR})

# define the demo target
#add_executable()
