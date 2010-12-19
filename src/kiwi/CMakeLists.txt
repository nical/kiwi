include_directories (${PROJECT_SOURCE_DIR}/src)


if(DEFINED BUILD_KIWI_IMAGE )
	message("build kiwi image")
	SET(KIWI_SRC ${KIWI_SRC}
		image/cairo/ImageContainer/ImageContainer.cpp
		#kiwi::image source files
	)
	include_directories (${CAIRO_INCLUDE_DIR})
	SET(optionalLibs ${optionalLibs} ${CAIRO_LIBRARIES} )
	SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${CAIRO_CFLAGS})
endif(DEFINED BUILD_KIWI_IMAGE)

if(DEFINED BUILD_KIWI_TEXT)
	message("build kiwi text")
	SET(KIWI_SRC ${KIWI_SRC}
		text/TextContainer.cpp
		text/TextReader.cpp
		text/TextWriter.cpp
		utils/TextOperations.cpp
		#kiwi::text source files
	)
endif(DEFINED BUILD_KIWI_TEXT)


SET(KIWI_SRC ${KIWI_SRC}
		utils/DebugOutputStream.cpp
		utils/SocketCreator.cpp
		core/Node.cpp
		core/CanonicalFilter.cpp
		core/NodeFactory.cpp
		pipeline/SimplePipeline.cpp
		# kiwi::core source files
    # tutorial/FilterSkeleton.cpp
		)


message("${LIBKIWI_NAME} library src: ${KIWI_SRC}")
add_library ( ${LIBKIWI_NAME}  ${KIWI_SRC})
TARGET_LINK_LIBRARIES(${LIBKIWI_NAME} ${optionalLibs} )
