include_directories (${PROJECT_SOURCE_DIR}/src)
include_directories (${CAIRO_INCLUDE_DIR})

if(DEFINED BUILD_KIWI_IMAGE )
	SET(KIWI_SRC ${KIWI_SRC}
		image/cairo/ImageContainer/ImageContainer.cpp
		#kiwi::image source files
	)
	
	SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${CAIRO_CFLAGS})
endif(DEFINED BUILD_KIWI_IMAGE)

if(DEFINED BUILD_KIWI_TEXT)
	SET(KIWI_SRC ${KIWI_SRC}
		text/TextContainer.cpp
		text/TextReader.cpp
		text/TextWriter.cpp
		#kiwi::text source files
	)
endif(DEFINED BUILD_KIWI_TEXT)


if(DEFINED BUILD_DDD_FLAG)
	# To build with the -g flag for debug using ddd
	SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)
endif(DEFINED DDD_FLAG)

SET(KIWI_SRC ${KIWI_SRC}
		utils/DebugOutputStream.cpp
		utils/SocketCreator.cpp
		core/Node.cpp
		core/CanonicalFilter.cpp
		core/NodeFactory.cpp
		pipeline/SimplePipeline.cpp
		# kiwi::core source files
		)

SET(optionalLibs ${optionalLibs} ${CAIRO_LIBRARIES} )


message("${LIBKIWI_NAME} library src: ${KIWI_SRC}")
add_library ( ${LIBKIWI_NAME}  ${KIWI_SRC})
TARGET_LINK_LIBRARIES(${LIBKIWI_NAME} ${optionalLibs} )
