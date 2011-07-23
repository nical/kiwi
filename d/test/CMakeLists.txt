message( "--------------------------------------------------------------" )
message( "                         Kiwi::Tests                          " )
message( "--------------------------------------------------------------" )

include_directories (${PROJECT_SOURCE_DIR}/src)
include_directories (${PROJECT_SOURCE_DIR}/test/)

# Make sure the linker can find the library once it is built.
link_directories (${PROJECT_BINARY_DIR})

include_directories (${PROJECT_SOURCE_DIR}/test)
include_directories (${PROJECT_SOURCE_DIR}/include)


if(DEFINED BUILD_KIWI_TEST)
	SET(KIWI_TESTS_SRC ${KIWI_TESTS_SRC}
    core.d
	)
endif(DEFINED BUILD_KIWI_TEST)

FOREACH(FILE ${KIWI_TESTS_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} ${LIBKIWID_NAME} )
  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)


