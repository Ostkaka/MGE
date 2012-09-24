#Add the core library include header

set(HEADER_CORE ${INCROOT}/core_include.hpp)

# core library additional include files
set(INC
    ${INCROOT}/Core/Core_types.hpp
	${INCROOT}/Core/interfaces/IApp.cpp
	${INCROOT}/Core/interfaces/IState.cpp
)

set( SRC
	${SRCROOT}/Core/Core_types.cpp
	${SRCROOT}/Core/interfaces/IApp.cpp
	${SRCROOT}/Core/interfaces/IState.cpp
) 

# find external SFML libraries
find_package(SFML REQUIRED audio graphics window system)

# add include paths of external libraries
include_directories(${SFML_INCLUDE_DIR})

#add MGE library
