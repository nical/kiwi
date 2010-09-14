
# Make sure the compiler can find include files.
include_directories (${PROJECT_SOURCE_DIR}/src/)
# Make sure the compiler can find include files.
include_directories (${PROJECT_SOURCE_DIR}/test/)


# Make sure the linker can find the library once it is built.
link_directories (${PROJECT_BINARY_DIR})



#------TESTS subdirectories ------

add_subdirectory(core)
add_subdirectory(image)
#add_subdirectory(audio)
