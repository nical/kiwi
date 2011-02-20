message( "--------------------------------------------------------------" )
message( "                         Kiwi::Tests                          " )
message( "--------------------------------------------------------------" )


include_directories (${PROJECT_SOURCE_DIR}/src)
include_directories (${PROJECT_SOURCE_DIR}/test/)
include_directories (/usr/include/cairo/)


# Make sure the linker can find the library once it is built.
link_directories (${PROJECT_BINARY_DIR})




if(DEFINED BUILD_KIWI_IMAGE)	
	SET(KIWI_TESTS_SRC ${KIWI_TESTS_SRC}
		image/CairoImageContainerTest
#		image/ContrastTest
	)
endif(DEFINED BUILD_KIWI_IMAGE)

if(DEFINED BUILD_KIWI_TEXT)	
	SET(KIWI_TESTS_SRC ${KIWI_TESTS_SRC}
		text/PlainTextContainerTest
	)
endif(DEFINED BUILD_KIWI_TEXT)


SET(KIWI_TESTS_SRC ${KIWI_TESTS_SRC}
#	TestSuite
	core/NodeTest
	core/FactoryTest
	core/TagTest
	utils/ConnectorTest
	utils/UnorderedArrayTest
	utils/typesTest
	utils/randomTest
	image/ImageContainerTest
	image/MixedImageTest
	image/CopyImageTest
	core/FilterTest
#	core/MetaFilterTest
	generic/PointTest
	generic/ArrayContainerTest
	generic/StructuredArrayContainerTest
	generic/MultiArrayContainerTest
	generic/ValueContainerTest
	generic/PointVectorContainerTest
   )

message("Kiwi Library : ${LIBKIWI_NAME}")

FOREACH(FILE ${KIWI_TESTS_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} ${LIBKIWI_NAME} )
#  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)

