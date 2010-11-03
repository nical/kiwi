SET(KIWI_TESTS_SRC
   testAudioSampleBuffer.cpp
   )


FOREACH(FILE ${KIWI_TESTS_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} ${LIBKIWI_NAME})
#  add_test(${FILE} ${FILE})
ENDFOREACH(FILE)



