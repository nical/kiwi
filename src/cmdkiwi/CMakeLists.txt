message( "--------------------------------------------------------------" )
message( "                    Command line kiwi                         " )
message( "--------------------------------------------------------------" )


include_directories (${PROJECT_SOURCE_DIR}/src)
include_directories (${PROJECT_SOURCE_DIR}/src/cmdkiwi/)


# Make sure the linker can find the library once it is built.
link_directories (${PROJECT_BINARY_DIR})



#------TESTS subdirectories ------

SET(KIWI_CMD_SRC
	kiwi
   )

message("Kiwi Library : ${LIBKIWI_NAME}")

FOREACH(FILE ${KIWI_CMD_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} ${LIBKIWI_NAME} )
ENDFOREACH(FILE)

