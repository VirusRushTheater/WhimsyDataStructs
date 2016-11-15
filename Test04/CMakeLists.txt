set(RELEVANT_FOLDERS core third_party/tinyxml .)

set(TEST04_SRC)

foreach(FOLDER IN ITEMS ${RELEVANT_FOLDERS})
    file(GLOB TEST04_SRC_LOOP
        "${CMAKE_CURRENT_SOURCE_DIR}/${FOLDER}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/${FOLDER}/*.h"
    )
    list(APPEND TEST04_SRC ${TEST04_SRC_LOOP})
endforeach(FOLDER)
 
add_executable(test04 ${TEST04_SRC})
