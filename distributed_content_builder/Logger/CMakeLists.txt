# CMakeList.txt : CMake project for DistribtutedSystem, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(HEADERS
        ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/MacLogger.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/UnixLogger.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/WinLogger.hpp
        PARENT_SCOPE
        )