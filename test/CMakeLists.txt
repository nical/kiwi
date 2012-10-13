include_directories (${PROJECT_SOURCE_DIR}/include/cpp)
include_directories (${PROJECT_SOURCE_DIR}/test/)

message("-- Kiwi Test suite")
  
# Make sure the linker can find the library once it is built.
link_directories (${PROJECT_BINARY_DIR})

SET(KIWI_TEST_SRC ${KIWI_TEST_SRC}
    all
    test_arithmetic
)

FOREACH(FILE ${KIWI_TEST_SRC})
  message("-- ${FILE}")
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} ${LIBKIWICORE_NAME})
  target_link_libraries (${FILE} ${LIBKIWIPROCESSING_NAME})
ENDFOREACH(FILE)
