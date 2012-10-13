include_directories (${PROJECT_SOURCE_DIR}/include/cpp)

SET(optionalLibs ${optionalLibs} ) #additional libs here
#SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ) #additional flags here

SET(KIWI_CORE_SRC ${KIWI_CORE_SRC}
    core/Node.cpp
    core/NodeGroup.cpp
    core/TypeSystem.cpp
)

SET(KIWI_PROCESSING_SRC ${KIWI_PROCESSING_SRC}
    processing/StackFrame.cpp
    processing/Operation.cpp
    processing/ProgramBuilder.cpp
)

add_library ( ${LIBKIWICORE_NAME} ${KIWI_CORE_SRC})
add_library ( ${LIBKIWIPROCESSING_NAME} ${KIWI_PROCESSING_SRC})
#TARGET_LINK_LIBRARIES(${LIBKIWICORE_NAME} ${optionalLibs} )
#TARGET_LINK_LIBRARIES(${LIBKIWIPROCESSINg_NAME} ${optionalLibs} )