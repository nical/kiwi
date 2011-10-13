include_directories (${PROJECT_SOURCE_DIR}/src)

include_directories (${CAIRO_INCLUDE_DIR})
SET(optionalLibs ${optionalLibs}  ) #additional libs here
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${CAIRO_CFLAGS})


if(DEFINED BUILD_KIWI_TEXT)
    message("build kiwi text")
    SET(KIWI_SRC ${KIWI_SRC} #kiwi::text source files
    )
endif(DEFINED BUILD_KIWI_TEXT)


SET(KIWI_SRC ${KIWI_SRC}
    extern/log/DebugStream.cpp
    extern/utest/Testing.cpp
    utils/Testing.cpp
    core/Node.cpp
    core/InputPort.cpp
    core/OutputPort.cpp
    core/OpConnect.cpp
    core/Connect.cpp
    core/Pipeline.cpp
    core/DataTypeManager.cpp
    processing/ProcessingPipeline.cpp
    
# kiwi::core source files
)

add_library ( ${LIBKIWI_NAME} ${KIWI_SRC})
TARGET_LINK_LIBRARIES(${LIBKIWI_NAME} ${optionalLibs} )

