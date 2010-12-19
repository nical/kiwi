message( "--------------------------------------------------------------" )
message( "                    Command line kiwi                         " )
message( "--------------------------------------------------------------" )


include_directories (${PROJECT_SOURCE_DIR}/src)

link_directories (${PROJECT_BINARY_DIR})

# sources (.cpp files)
SET(KIWI_CMD_SRC
	kiwiLauncher
	ArgumentProcessor
	SimpleFilterProcessor
	Help
	TelnetRequestParser
	TelnetServer
	)

message("Kiwi Library : ${LIBKIWI_NAME}")

add_executable(kiwi ${KIWI_CMD_SRC})
target_link_libraries (kiwi ${LIBKIWI_NAME} -pthread )
