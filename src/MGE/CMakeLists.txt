# include the MGE specific macros
include(${PROJECT_SOURCE_DIR}/cmake/macros.cmake)

# add the MGE sources path
include_directories(${PROJECT_SOURCE_DIR}/src)

# set the output directory for MGE libraries
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")

# set the source directory for include and source files
set(MGE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/MGE)
set(MGE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/MGE)

# MGE needs to export symbols when build so define the export flag
add_definitions(-DMGE_EXPORTS)

# add the modules subdirectories
add_subdirectory(Core)

# install Config header include file
install(FILES ${INCROOT}/Config.hpp
        DESTINATION include/MGE
        COMPONENT dev)
