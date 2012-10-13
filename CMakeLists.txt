# CMakeLists files in this
# project can refer to the root source directory of the project as
# ${KIWI_SOURCE_DIR} and to the root binary directory of the
# project as ${KIWI_BINARY_DIR}.

# -----------------------------------------------------------------------------
# Project definition
# -----------------------------------------------------------------------------
project (Kiwi)
cmake_minimum_required (VERSION 2.4)

#comment/uncomment some of the folowing lines to enable/disable part of the projects
set(BUILD_KIWI_TESTS "yes") #to build the tests (recommended!)
set(BUILD_DDD_FLAG "yes") #to build using -g argument for debug

#so that each test is built with it's own executable
add_definitions(-DKIWI_TEST_MAIN)


message( "--------------------------------------------------------------" )
message( " Kiwi " )
message( "--------------------------------------------------------------" )

message(STATUS "Source DIR is ${PROJECT_SOURCE_DIR}")
message(STATUS "Binary DIR is ${PROJECT_BINARY_DIR}")


# -- Environement variables
if (UNIX)
  add_definitions(-DUNIX)
endif (UNIX)
if (WIN32)
  add_definitions(-DWIN32)
endif (WIN32)
if (APPLE)
  add_definitions(-DAPPLE)
endif (APPLE)


# -----------------------------------------------------------------------------
# Check packages
# -----------------------------------------------------------------------------

# tell CMake to search first in directories listed in CMAKE_MODULE_PATH when
# you use FIND_PACKAGE() or INCLUDE()
set( CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
list( APPEND CMAKE_MODULE_PATH . )

# -----------------------------------------------------------------------------
# Check Dependencies
# -----------------------------------------------------------------------------

# This is used when searching for include files, binaries, or libraries
set ( CMAKE_PREFIX_PATH "/usr:/usr/local:/opt/local:${CMAKE_PREFIX_PATH}" )
message( "-- CMAKE_PREFIX_PATH = " ${CMAKE_PREFIX_PATH} )

# -----------------------------------------------------------------------------
# Defines some variables
# -----------------------------------------------------------------------------
set ( LIBKIWICORE_NAME "kiwicore${SUFFIXLIB}" )
set ( LIBKIWIPROCESSING_NAME "kiwiprocessing${SUFFIXLIB}" )

# -----------------------------------------------------------------------------
# Compile flags
# -----------------------------------------------------------------------------
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -g -Wall -pedantic")
#SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -gdwarf-2-std=c++0x)

message( "CXX Flags: ${CMAKE_CXX_FLAGS}" )

#------------------------------------------------------------------------------
# Add subdirectories
#------------------------------------------------------------------------------

# Call the CMakeLists.txt in subdirectories

# the library itself
add_subdirectory(src/kiwi)

# tests
add_subdirectory (test)
