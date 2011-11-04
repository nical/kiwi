message( "--------------------------------------------------------------" )
message( " Kiwi::Tests " )
message( "--------------------------------------------------------------" )


include_directories (${PROJECT_SOURCE_DIR}/src)
include_directories (${PROJECT_SOURCE_DIR}/test/)
#include_directories (/usr/include/cairo/)

find_package(GLUT)
find_package(OpenGL)

# Make sure the linker can find the library once it is built.
link_directories (${PROJECT_BINARY_DIR})


SET(KIWI_TESTS_SRC ${KIWI_TESTS_SRC}
core/Node_Test
core/NodeTypeManager_Test
core/Container_Test
core/Algorithm_Test
#glWidget
)

message("-- Kiwi Library : ${LIBKIWI_NAME}")

FOREACH(FILE ${KIWI_TESTS_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} ${LIBKIWI_NAME} ${GLUT_LIBRARY} ${OPENGL_LIBRARY} -lGLEW )
# add_test(${FILE} ${FILE})
ENDFOREACH(FILE)
