project(basictest)

set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

# all source files
FILE( GLOB SOURCE ${SRCROOT}/*.cpp )

# find external SFML libraries
if(WINDOWS)
  find_package(SFML REQUIRED main)
endif(WINDOWS)

# add include paths of external libraries
include_directories(${SFML_INCLUDE_DIR})

# define the demo target
add_executable(basictest ${SOURCE})

target_link_libraries(basictest ${SFML_MAIN_LIBRARY})
target_link_libraries(basictest mge-core)

install(TARGETS basictest RUNTIME DESTINATION examples/basictest COMPONENT examples)