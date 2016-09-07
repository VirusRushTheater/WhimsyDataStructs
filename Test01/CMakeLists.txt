
file(GLOB TEST01_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)
 
add_executable(test01 ${TEST01_SRC})