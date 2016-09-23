set(RELEVANT_FOLDERS core system io .)

set(TEST03_SRC)

foreach(FOLDER IN ITEMS ${RELEVANT_FOLDERS})
    file(GLOB TEST03_SRC_LOOP
        "${CMAKE_CURRENT_SOURCE_DIR}/${FOLDER}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/${FOLDER}/*.h"
    )
    list(APPEND TEST03_SRC ${TEST03_SRC_LOOP})
endforeach(FOLDER)
 
add_executable(test03 ${TEST03_SRC})
