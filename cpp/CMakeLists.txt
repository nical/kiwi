# The name of our project is "Kiwi". CMakeLists files in this
# project can refer to the root source directory of the project as
# ${KIWI_SOURCE_DIR} and to the root binary directory of the
# project as ${KIWI_BINARY_DIR}.

# -----------------------------------------------------------------------------
# Project definition
# -----------------------------------------------------------------------------
project (Kiwi)
cmake_minimum_required (VERSION 2.4)

#comment/uncomment some of the folowing lines to enable/disable part of the projects
set(BUILD_KIWI_TESTS "yes") #to build the tests (recommended !)
#set(BUILD_DDD_FLAG "yes") #to build using -g argument for debug

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

# Find the boost library
FIND_PACKAGE(Boost REQUIRED)
# MACPORT
if(DEFINED APPLE AND NOT DEFINED ${MACPORT_BOOST_FOUND})
SET( MACPORT_BOOST_INCLUDES "/opt/local/include/boost")
SET( MACPORT_BOOST_LIBS "/opt/local/lib/")

    include_directories( ${MACPORT_BOOST_INCLUDES} )
    link_directories( ${MACPORT_BOOST_LIBS} )
set( MACPORT_BOOST_FOUND TRUE)

message( "-- Apple plateform detected : Boost lib path added." )
endif(DEFINED APPLE AND NOT DEFINED ${MACPORT_BOOST_FOUND})

if ( Boost_FOUND )
   message( "-- Boost found. include=${Boost_INCLUDE_DIR}" )
   include_directories( ${Boost_INCLUDE_DIR} )
endif ( Boost_FOUND )



# -----------------------------------------------------------------------------
# Defines some variables
# -----------------------------------------------------------------------------
set ( LIBKIWI_NAME "kiwicpp${SUFFIXLIB}" )

# -----------------------------------------------------------------------------
# Compile flags
# -----------------------------------------------------------------------------
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -g")
#SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -gdwarf-2-std=c++0x)

message( "CXX Flags: ${CMAKE_CXX_FLAGS}" )

#------------------------------------------------------------------------------
# Add subdirectories
#------------------------------------------------------------------------------

# Call the CMakeLists.txt in subdirectories

# the library itself
add_subdirectory(src/kiwi)

# tests
if(DEFINED BUILD_KIWI_TESTS)
add_subdirectory (test)
endif(DEFINED BUILD_KIWI_TESTS)
