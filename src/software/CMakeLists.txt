message( "--------------------------------------------------------------" )
message( "                    Command line kiwi                         " )
message( "--------------------------------------------------------------" )


include_directories (${PROJECT_SOURCE_DIR}/src)
include_directories (${PROJECT_SOURCE_DIR}/src/cmdkiwi/)


# Make sure the linker can find the library once it is built.
link_directories (${PROJECT_BINARY_DIR})


#------TESTS subdirectories ------

SET(KIWI_CMD_SRC
  kiwiLauncher
  ArgumentProcessor
  Help
  InputWrapper
  TelnetRequestParser
  TelnetServer
   )

message("Kiwi Library : ${LIBKIWI_NAME}")

#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -lboost_filesystem )

add_executable(kiwi ${KIWI_CMD_SRC})
target_link_libraries (kiwi ${LIBKIWI_NAME} )
