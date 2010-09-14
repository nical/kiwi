
include_directories (${PROJECT_SOURCE_DIR}/src)

##Recursive calls
## each subdir must contain a ModuleSRC.txt file with a set command on the variable ${KIWI_SRC}
include(core/ModuleSRC.txt)
include(image/ModuleSRC.txt)
include(audio/ModuleSRC.txt)

message("-- src: KIWI_SRC = ${KIWI_SRC}")

# Create a library called "Kiwi".
# The extension is already found. Any number of sources could be listed here.
add_library ( ${LIBKIWI_NAME}  ${KIWI_SRC})
TARGET_LINK_LIBRARIES(${LIBKIWI_NAME} ${optionalLibs})

SET_TARGET_PROPERTIES(${LIBKIWI_NAME} PROPERTIES LINKER_LANGUAGE C)
