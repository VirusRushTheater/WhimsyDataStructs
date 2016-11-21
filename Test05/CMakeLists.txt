set(RELEVANT_FOLDERS core third_party/tinyxml .)

set(TEST05_SRC)

foreach(FOLDER IN ITEMS ${RELEVANT_FOLDERS})
    file(GLOB TEST05_SRC_LOOP
        "${CMAKE_CURRENT_SOURCE_DIR}/${FOLDER}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/${FOLDER}/*.h"
    )
    list(APPEND TEST05_SRC ${TEST05_SRC_LOOP})
endforeach(FOLDER)
 
add_executable(test05 ${TEST05_SRC})
