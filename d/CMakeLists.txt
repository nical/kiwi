cmake_minimum_required(VERSION 2.8.1)

message( "--------------------------------------------------------------" )
message( "                     Kiwi - D	  	                            " )
message( "--------------------------------------------------------------" )


set(BUILD_KIWI_TEST "yes")
set(BUILD_KIWI_CORE "yes")

# We must explicitly indicate we're using the D language
# in the project declaration.  Listing other languages
# is fine.
PROJECT (KiwiDcd D )
SET( GLOBAL_DMD_DEFS "-w" )
SET( GLOBAL_GCC_DEFS "-Wall -pedantic" )

# Don't use ADD_DEFINITIONS() with a mixed C + D project
# since that adds the same flags to both C and D builds.
# Also, the D linker preference is set to 40, which is
# higher than C++ (30) and C (10).  This causes CMAKE
# to use the D linker in mixed linking cases.
# Append our own definitions to the defaults.
SET( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GLOBAL_GCC_DEFS}" )
SET( CMAKE_D_FLAGS "${CMAKE_D_FLAGS} ${GLOBAL_DMD_DEFS}" )

enable_testing()

# build libs first, then apps
ADD_SUBDIRECTORY (src)
ADD_SUBDIRECTORY (test)
