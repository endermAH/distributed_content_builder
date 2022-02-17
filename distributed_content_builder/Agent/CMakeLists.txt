# CMakeList.txt : CMake project for DistribtutedSystem, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include_directories(./../Interfaces/)

set(HEADERS
        ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/Agent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RemoteAgent.cpp
        PARENT_SCOPE
        )

set(SOURCE
        ${SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/Agent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RemoteAgent.cpp
        PARENT_SCOPE
        )