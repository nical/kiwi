# The name of our project is "Kiwi". CMakeLists files in this
# project can refer to the root source directory of the project as
# ${KIWI_SOURCE_DIR} and to the root binary directory of the
# project as ${KIWI_BINARY_DIR}.

# -----------------------------------------------------------------------------
# Project definition
# -----------------------------------------------------------------------------
project (Kiwi)
cmake_minimum_required (VERSION 2.4) 



message( "--------------------------------------------------------------" )
message( "                         Kiwi	  	                            " )
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
# Look for modules
set( CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
list( APPEND CMAKE_MODULE_PATH . )

# -----------------------------------------------------------------------------
# Check Dependencies
# -----------------------------------------------------------------------------

set ( CMAKE_PREFIX_PATH "/usr:/usr/local:/opt/local:${CMAKE_PREFIX_PATH}" )
message( "-- CMAKE_PREFIX_PATH = " ${CMAKE_PREFIX_PATH} )

FIND_PACKAGE(Boost REQUIRED)
if ( Boost_FOUND )
   message( "-- Boost found. include=${Boost_INCLUDE_DIR}" )
   include_directories( ${Boost_INCLUDE_DIR} )
endif ( Boost_FOUND )

find_package(Cairo REQUIRED)



# -----------------------------------------------------------------------------
# Defines some variables
# -----------------------------------------------------------------------------
set ( LIBKIWI_NAME "Kiwi${SUFFIXLIB}" )

#CONFIGURE_FILE( "${PROJECT_SOURCE_DIR}/src/core/Config.h.in" "${PROJECT_SOURCE_DIR}/src/core/Config.h" IMMEDIATE)


#------------------------------------------------------------------------------
# Add subdirectories
#------------------------------------------------------------------------------
add_subdirectory (src/kiwi)
add_subdirectory (src/cmdkiwi)
add_subdirectory (test)

