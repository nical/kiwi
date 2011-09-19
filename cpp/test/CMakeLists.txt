message( "--------------------------------------------------------------" )
message( " Kiwi::Tests " )
message( "--------------------------------------------------------------" )


include_directories (${PROJECT_SOURCE_DIR}/src)
include_directories (${PROJECT_SOURCE_DIR}/test/)
include_directories (/usr/include/cairo/)


# Make sure the linker can find the library once it is built.
link_directories (${PROJECT_BINARY_DIR})


if(DEFINED BUILD_KIWI_TEXT)
SET(KIWI_TESTS_SRC ${KIWI_TESTS_SRC}
# text/PlainTextContainerTest
)
endif(DEFINED BUILD_KIWI_TEXT)


SET(KIWI_TESTS_SRC ${KIWI_TESTS_SRC}
core/Node_Test
)

message("-- Kiwi Library : ${LIBKIWI_NAME}")

FOREACH(FILE ${KIWI_TESTS_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} ${LIBKIWI_NAME} )
# add_test(${FILE} ${FILE})
ENDFOREACH(FILE)


