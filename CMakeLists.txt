# The name of our project is "Kiwi". CMakeLists files in this
# project can refer to the root source directory of the project as
# ${KIWI_SOURCE_DIR} and to the root binary directory of the
# project as ${KIWI_BINARY_DIR}.

# -----------------------------------------------------------------------------
# Project definition
# -----------------------------------------------------------------------------
project (Kiwi)
cmake_minimum_required (VERSION 2.4) 

set(BUILD_KIWI_TESTS "yes")
set(BUILD_KIWI_IMAGE "yes")
set(BUILD_KIWI_TEXT "yes")
set(BUILD_KIWI_CMDLINE "yes")
set(BUILD_DDD_FLAG "yes")
add_definitions(-DKIWI_TEST_MAIN)


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

if(DEFINED APPLE AND NOT DEFINED ${MACPORT_BOOST_FOUND})
	SET( MACPORT_BOOST_INCLUDES "/opt/local/includes/boost")	
	SET( MACPORT_BOOST_LIBS "/opt/local/lib/")	

   	include_directories( ${MACPORT_BOOST_INCLUDES} )
   	link_directories( ${MACPORT_BOOST_LIBS} )
	set( MACPORT_BOOST_FOUND TRUE) 	
     	
	message( "-- Apple plateform detected : Boost lib path added." )
endif(DEFINED APPLE AND NOT DEFINED MACPORT_BOOST_FOUND)
endif ( Boost_FOUND )

if(DEFINED BUILD_KIWI_IMAGE)
	find_package(Cairo REQUIRED)
	if ( Cairo_FOUND )
		message( "-- Cairo found. include=${Cairo_INCLUDE_DIR}" )
		include_directories( ${Cairo_INCLUDE_DIR} )
	endif ( Cairo_FOUND )
endif(DEFINED BUILD_KIWI_IMAGE)


# -----------------------------------------------------------------------------
# Defines some variables
# -----------------------------------------------------------------------------
set ( LIBKIWI_NAME "Kiwi${SUFFIXLIB}" )

#CONFIGURE_FILE( "${PROJECT_SOURCE_DIR}/src/core/Config.h.in" "${PROJECT_SOURCE_DIR}/src/core/Config.h" IMMEDIATE)



# -----------------------------------------------------------------------------
# Compile flags 
# -----------------------------------------------------------------------------
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -gdwarf-2)



#------------------------------------------------------------------------------
# Add subdirectories
#------------------------------------------------------------------------------


if(DEFINED BUILD_KIWI_CMDLINE)
	add_subdirectory (src/software)
endif(DEFINED BUILD_KIWI_CMDLINE)

if(DEFINED BUILD_KIWI_TESTS)
	add_subdirectory (test)
endif(DEFINED BUILD_KIWI_TESTS)


add_subdirectory(src/kiwi)
