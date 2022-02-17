# CMakeList.txt : CMake project for DistribtutedSystem, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(HEADERS
        ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/IContent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IController.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ILogger.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/INetwork.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IQueue.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IRemoteAgent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ITask.hpp
        PARENT_SCOPE
        )