#Add the core library include header
set(CORE_HEADER ${MGE_INCLUDE_DIR}/Core_include.hpp)

# core library additional include files
FILE( GLOB_RECURSE 
	INC
    ${MGE_INCLUDE_DIR}/Core/ *.hpp
)

FILE( GLOB_RECURSE
	SRC
	${MGE_SOURCE_DIR}/Core/ *.cpp
) 

# find external SFML libraries
find_package(SFML REQUIRED audio graphics window system)

# add include paths of external libraries
include_directories(${SFML_INCLUDE_DIR})

# add MGE library
add_library(MGE ${CORE_HEADER} ${INC} ${SRC})

# link SFML
target_link_libraries(MGE ${SFML_LIBRARIES})
