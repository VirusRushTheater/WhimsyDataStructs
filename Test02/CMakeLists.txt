file(GLOB TEST02_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)
 
add_executable(test02 ${TEST02_SRC})
