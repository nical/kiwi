# The name of our project is "Kiwi". CMakeLists files in this
# project can refer to the root source directory of the project as
# ${KIWI_SOURCE_DIR} and to the root binary directory of the
# project as ${KIWI_BINARY_DIR}.

# ----------------------------------------------------------------------
# Project definition
# ----------------------------------------------------------------------
project (Kiwi_image)
cmake_minimum_required (VERSION 0.1) 



message( "--------------------------------------------------------------" )
message( "                     Kiwi::image		                        " )
message( "--------------------------------------------------------------" )

message(STATUS "Source DIR is ${PROJECT_SOURCE_DIR}")
message(STATUS "Binary DIR is ${PROJECT_BINARY_DIR}")

#set(INSTALL_DOC_PATH ${CMAKE_INSTALL_PREFIX}/doc/${CMAKE_PROJECT_NAME} )
#set(CMAKE_BUILD_TYPE  Debug)


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


# ----------------------------------------------------------------------
# Check packages
# ----------------------------------------------------------------------
# Look for modules
set( CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
list( APPEND CMAKE_MODULE_PATH . )

# ----------------------------------------------------------------------
# Check Dependencies
# ----------------------------------------------------------------------
#FIND_PACKAGE(Boost REQUIRED PATHS /opt/local /opt/local/include /opt/local/lib)
set ( CMAKE_PREFIX_PATH "/usr:/usr/local:/opt/local:${CMAKE_PREFIX_PATH}" )
message( "-- CMAKE_PREFIX_PATH = " ${CMAKE_PREFIX_PATH} )
#find_path( Boost_DIR include/boost/assert.hpp )
#message( "Boost_DIR = " ${Boost_DIR} )
FIND_PACKAGE(Boost REQUIRED)
if ( Boost_FOUND )
   message( "-- Boost found. include=${Boost_INCLUDE_DIR}" )
   include_directories( ${Boost_INCLUDE_DIR} )
endif ( Boost_FOUND )




# ----------------------------------------------------------------------
# Defines some variables
# ----------------------------------------------------------------------
set ( LIBKIWIIMAGE_NAME "Kiwi_image${SUFFIXLIB}" )


# ----------------------------------------------------------------------
# Parsing cmake options
# ----------------------------------------------------------------------

#OPTION(BUILD_SHARED_LIBS "Build shared libraries." ON)

#OPTION(INLINE_FUNCTION_BUILD "Build inline functions." ON)

include_directories (${PROJECT_SOURCE_DIR}/../engine/src)
include_directories (${PROJECT_SOURCE_DIR}/src)

#-----------------------------------------------------------------------
# Add subdirectories
#-----------------------------------------------------------------------
add_subdirectory (test)
add_subdirectory (src/cairo)


#add_executable(testFilter ${KIWI_SRC})
