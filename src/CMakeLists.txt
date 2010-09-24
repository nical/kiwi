
include_directories (${PROJECT_SOURCE_DIR}/src)

##Recursive calls
## each subdir must contain a ModuleSRC.txt file with a set command on the variable ${KIWI_SRC}


include(audio/ModuleSRC.txt)
include(core/ModuleSRC.txt)
include(image/ModuleSRC.txt)

# Create a library called "Kiwi".
add_library ( ${LIBKIWI_NAME}  ${KIWI_SRC})
TARGET_LINK_LIBRARIES(${LIBKIWI_NAME} ${optionalLibs})

SET_TARGET_PROPERTIES(${LIBKIWI_NAME} PROPERTIES LINKER_LANGUAGE C)
