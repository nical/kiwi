
include_directories (${PROJECT_SOURCE_DIR}/src)

include_directories ( ${CAIRO_INCLUDE_DIR} )

SET(KIWI_SRC ${KIWI_SRC}
		utils/DebugOutputStream.cpp
		core/Node.cpp
		cairo/ImageContainer/ImageContainer.cpp
		)

SET(optionalLibs ${optionalLibs} ${CAIRO_LIBRARIES} )

set(CMAKE_CXX_FLAGS ${CAIRO_CFLAGS})
# Create a library called "Kiwi".
message("${LIBKIWI_NAME} library src: ${KIWI_SRC}")
add_library ( ${LIBKIWI_NAME}  ${KIWI_SRC})
TARGET_LINK_LIBRARIES(${LIBKIWI_NAME} ${optionalLibs} )
