include_directories (${PROJECT_SOURCE_DIR}/src)
include_directories (${CAIRO_INCLUDE_DIR})

SET(KIWI_SRC ${KIWI_SRC}
		utils/DebugOutputStream.cpp
		core/Node.cpp
		core/CanonicalFilter.cpp
		text/TextContainer.cpp
		text/TextReader.cpp
		text/TextWriter.cpp
		pipeline/SimplePipeline.cpp
		image/cairo/ImageContainer/ImageContainer.cpp
		)

SET(optionalLibs ${optionalLibs} ${CAIRO_LIBRARIES} )

SET(CMAKE_CXX_FLAGS ${CAIRO_CFLAGS} -g)
message("${LIBKIWI_NAME} library src: ${KIWI_SRC}")
add_library ( ${LIBKIWI_NAME}  ${KIWI_SRC})
TARGET_LINK_LIBRARIES(${LIBKIWI_NAME} ${optionalLibs} )
