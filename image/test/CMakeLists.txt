
# Make sure the compiler can find include files.
include_directories (${PROJECT_SOURCE_DIR}/src/)
# Make sure the compiler can find include files.
include_directories (${PROJECT_SOURCE_DIR}/test/)


# Make sure the linker can find the library once it is built.
link_directories (${PROJECT_BINARY_DIR})



#------TESTS subdirectories ------

SET(KIWI_IMAGE_TESTS_SRC
	cairo/CairoImageContainerTest
	)

message("Library name: ${LIBKIWIIMAGE_NAME}")

FOREACH(FILE ${KIWI_IMAGE_TESTS_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} ${LIBKIWIIMAGE_NAME} )
#  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)
