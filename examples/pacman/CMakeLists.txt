project(pacman)

set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

# all source files
FILE( GLOB SOURCE ${SRCROOT}/*.cpp ${SRCROOT}/*.hpp)

# find external SFML libraries
if(WINDOWS)
  find_package(SFML REQUIRED main)
endif(WINDOWS)

# add include paths of external libraries
include_directories(${SFML_INCLUDE_DIR})

# define the demo target
add_executable(pacman ${SOURCE})

target_link_libraries(pacman ${SFML_MAIN_LIBRARY})
target_link_libraries(pacman mge-core)
target_link_libraries(pacman mge-tile)

install(TARGETS pacman RUNTIME DESTINATION examples/pacman COMPONENT examples)