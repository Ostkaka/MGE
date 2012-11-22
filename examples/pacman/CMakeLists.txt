project(example_pacman)

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
add_executable(example_pacman ${SOURCE})

target_link_libraries(example_pacman ${SFML_MAIN_LIBRARY})
target_link_libraries(example_pacman mge-core)
target_link_libraries(example_pacman mge-tile)

install(TARGETS example_pacman RUNTIME DESTINATION examples/pacman COMPONENT examples)