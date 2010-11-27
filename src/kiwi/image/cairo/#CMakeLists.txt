
SET(KIWIIMAGE_SRC ${KIWIIMAGE_SRC}
		CairoImageContainer/CairoImageContainer.hpp
		)


#FIND_PACKAGE(Kiwi REQUIRED)
#MESSAGE(STATUS "LibKiwi found")

SET( LIBKIWI_NAME "Kiwi" )
message( "Kiwi Library name:  ${LIBKIWI_NAME}" )

# Create a library called "Kiwi".
message("Kiwi image Library src = ${KIWIIMAGE_SRC}")
add_library ( ${LIBKIWIIMAGE_NAME}  ${KIWIIMAGE_SRC})
TARGET_LINK_LIBRARIES(${LIBKIWIIMAGE_NAME} ${optionalLibs} ${LIBKIWI_NAME})

SET_TARGET_PROPERTIES(${LIBKIWIIMAGE_NAME} PROPERTIES LINKER_LANGUAGE C)
