project(example_basictest)

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
add_executable(example_basictest ${SOURCE})

target_link_libraries(example_basictest ${SFML_MAIN_LIBRARY})
target_link_libraries(example_basictest mge-core)
target_link_libraries(example_basictest mge-tile)

install(TARGETS example_basictest RUNTIME DESTINATION examples/basictest COMPONENT examples)