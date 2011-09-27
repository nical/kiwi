include_directories (${PROJECT_SOURCE_DIR}/src)

SET(optionalLibs ${optionalLibs}  ) #additional libs here
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})


SET(KIWI_GLWIDGET_SRC ${KIWI_GLWIDGET_SRC}
    NodeWidget.cpp
# kiwi::core source files
)

add_library ( kiwi-glWidget ${KIWI_GLWIDGET_SRC})
TARGET_LINK_LIBRARIES( kiwi-glWidget ${optionalLibs} )
