#Add the core library include header
set(CORE_HEADER ${MGE_INCLUDE_DIR}/Tile_include.hpp)

# core library additional include files
FILE( GLOB_RECURSE 
	INCLUDES
    ${MGE_INCLUDE_DIR}/Tile/*.h
)

FILE( GLOB_RECURSE
	SOURCES
	${MGE_SOURCE_DIR}/Tile/*.cpp
) 

# find external SFML libraries
find_package(SFML REQUIRED audio graphics window system)

# add include paths of external libraries
include_directories(${SFML_INCLUDE_DIR})

# add MGE library
add_library(mge-tile ${CORE_HEADER} ${INCLUDES} ${SOURCES})

# link SFML
target_link_libraries(mge-tile ${SFML_LIBRARIES} mge-core)
