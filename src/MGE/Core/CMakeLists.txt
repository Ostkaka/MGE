#Add the core library include header
set(CORE_HEADER ${MGE_INCLUDE_DIR}/Core_include.hpp)

# core library additional include files
FILE( GLOB_RECURSE 
	INCLUDES
    ${MGE_INCLUDE_DIR}/Core/*.hpp
)

FILE( GLOB_RECURSE
	SOURCES
	${MGE_SOURCE_DIR}/Core/*.cpp
) 

# find external SFML libraries
find_package(SFML REQUIRED audio graphics window system)

# add include paths of external libraries
include_directories(${SFML_INCLUDE_DIR})

# add MGE library
add_library(mge-core ${CORE_HEADER} ${INCLUDES} ${SOURCES})

# link SFML
target_link_libraries(mge-core ${SFML_LIBRARIES})
