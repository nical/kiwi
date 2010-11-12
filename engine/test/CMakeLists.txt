
# Make sure the compiler can find include files.
include_directories (${PROJECT_SOURCE_DIR}/src/)
# Make sure the compiler can find include files.
include_directories (${PROJECT_SOURCE_DIR}/test/)

include_directories ( /usr/include/cairo/ )


# Make sure the linker can find the library once it is built.
link_directories (${PROJECT_BINARY_DIR})



#------TESTS subdirectories ------

SET(KIWI_TESTS_SRC
	TestSuite
   )

message("Kiwi Library : ${LIBKIWI_NAME}")

FOREACH(FILE ${KIWI_TESTS_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} ${LIBKIWI_NAME} )
#  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)

