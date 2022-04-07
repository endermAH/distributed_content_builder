# CMakeList.txt : CMake project for DistribtutedSystem, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include_directories(./../Interfaces/)

set(SOURCE
        ${SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/DebugController.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Controller.cpp
        PARENT_SCOPE
        )

set(HEADERS
        ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/MetricsControllerDecorator.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Controller.hpp
        PARENT_SCOPE
        )