set(RELEVANT_FOLDERS core system .)

set(TEST02_SRC)

foreach(FOLDER IN ITEMS ${RELEVANT_FOLDERS})
    file(GLOB TEST02_SRC_LOOP
        "${CMAKE_CURRENT_SOURCE_DIR}/${FOLDER}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/${FOLDER}/*.h"
    )
    message(${TEST02_SRC_LOOP})
    list(APPEND TEST02_SRC ${TEST02_SRC_LOOP})
endforeach(FOLDER)
 
add_executable(test02 ${TEST02_SRC})
