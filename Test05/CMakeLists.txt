set(RELEVANT_FOLDERS core third_party/tinyxml .)

set(TEST05_SRC)

find_package(PythonLibs)
find_package(Boost COMPONENTS python system thread)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    include_directories(${PYTHON_INCLUDE_DIRS})

    foreach(FOLDER IN ITEMS ${RELEVANT_FOLDERS})
        file(GLOB TEST05_SRC_LOOP
            "${CMAKE_CURRENT_SOURCE_DIR}/${FOLDER}/*.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/${FOLDER}/*.h"
        )
        list(APPEND TEST05_SRC ${TEST05_SRC_LOOP})
    endforeach(FOLDER)

    add_executable(test05 ${TEST05_SRC})

    target_link_libraries(test05 ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
else()
    message("Boost library not found. Extensions test won't be built.")
endif()
