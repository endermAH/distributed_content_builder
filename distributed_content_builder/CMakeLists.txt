# CMakeList.txt : CMake project for DistribtutedSystem, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/main.h
        )

set(SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )

add_subdirectory ("Agent")
add_subdirectory ("Content")
add_subdirectory ("Controller")
add_subdirectory ("Interfaces")
add_subdirectory ("Logger")
add_subdirectory ("Network")
add_subdirectory ("Queue")
add_subdirectory ("Task")

include_directories(./Agent/)
include_directories(./Content/)
include_directories(./Controller/)
include_directories(./Interfaces/)
include_directories(./Logger/)
include_directories(./Network/)
include_directories(./Queue/)
include_directories(./Task/)

# Add source to this project's executable.
add_executable (distributed_content_builder ${HEADERS} ${SOURCE} )

# TODO: Add tests and install targets if needed.