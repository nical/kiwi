#
#                         kiwi src
#


include_directories (${PROJECT_SOURCE_DIR}/src)
include_directories (${PROJECT_SOURCE_DIR}/src/extern/log)

if(DEFINED BUILD_KIWI_CORE)
  message("-- build kiwi image")
	SET(KIWI_CORE_SRC ${KIWI_CORE_SRC}
    kiwi/core/interfaces.d
    kiwi/core/dynamic.d
    kiwi/core/data.d
    extern/log/logstream.d
	)
endif(DEFINED BUILD_KIWI_CORE)

message("binary dir:  ${CMAKE_BINARY_DIR}")

SET(KIWI_SRC "${KIWI_CORE_SRC}")

SET(LIBKIWID_NAME "kiwid")
message("-- kiwi.core src: ${KIWI_CORE_SRC}")
add_library ( ${LIBKIWID_NAME} STATIC ${KIWI_CORE_SRC})
#add_library ( ${LIBKIWID_NAME} SHARED ${KIWI_CORE_SRC})
#TARGET_LINK_LIBRARIES(${LIBKIWI_NAME} ${optionalLibs} )
