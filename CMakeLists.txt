# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
#cmake_minimum_required (VERSION 3.8)
#
#project ("distributed_content_builder")
#
#include(ExternalProject)
#include("${CMAKE_SOURCE_DIR}/vendor/rapidjson.cmake")
#
#include_directories(${RAPIDJSON_INCLUDE_DIR})
#set(CMAKE_CXX_STANDARD 17)
## Include sub-projects.
#add_subdirectory ("distributed_content_builder")


cmake_minimum_required (VERSION 3.8)

project ("distributed_content_builder")

include(ExternalProject)
include("${CMAKE_SOURCE_DIR}/vendor/rapidjson.cmake")

set(CMAKE_CXX_STANDARD 17)
# Include sub-projects.
add_subdirectory ("distributed_content_builder")