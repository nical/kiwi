include_directories (${PROJECT_SOURCE_DIR}/include)

include_directories (${CAIRO_INCLUDE_DIR})
SET(optionalLibs ${optionalLibs}  ) #additional libs here
#SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${CAIRO_CFLAGS})

SET(KIWI_SRC ${KIWI_SRC}
    extern/log/DebugStream.cpp
    utils/Testing.cpp
    mock/MockNodeUpdater.cpp
    mock/MockPipeline.cpp
    mock/MockNode.cpp
    core/NodeTypeManager.cpp
    core/Node.cpp
    core/InputPort.cpp
    core/OutputPort.cpp
    core/OpConnect.cpp
    core/Connect.cpp
    core/Pipeline.cpp
    core/PipelineManager.cpp
    core/DataTypeManager.cpp
    core/DynamicNodeUpdater.cpp
    core/Blob.cpp
    core/DataProxy.cpp
    core/Context.cpp
    view/NodeView
    view/PipelineView
    processing/ProcessingPipelineUpdater
    
# kiwi::core source files
)

add_library ( ${LIBKIWI_NAME} ${KIWI_SRC})
TARGET_LINK_LIBRARIES(${LIBKIWI_NAME} ${optionalLibs} )

