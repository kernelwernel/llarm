cmake_minimum_required(VERSION 3.22)
project(charm DESCRIPTION "ARM emulation framework" LANGUAGES CXX)

# set standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# set paths
set(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(BUILD_DIR "${CMAKE_BINARY_DIR}")
set(OBJ_DIR "${BUILD_DIR}/objects")
file(MAKE_DIRECTORY ${OBJ_DIR})

# set up source files
file(GLOB_RECURSE SRC "${CMAKE_SOURCE_DIR}/src/*.cpp")
list(REMOVE_DUPLICATES SRC)
set(MAIN "src/main.cpp")

# remove the main source file from manually compiled sources
list(REMOVE_ITEM SRC "${CMAKE_SOURCE_DIR}/${MAIN}")


# compiler 
#set(CMAKE_CXX_FLAGS "")
if (MSVC)
    add_compile_options(/Wall /W4 /EHsc /std:c++20)
    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        MESSAGE(STATUS "Build set to debug mode")
        add_compile_options(/Od)
    elseif(CMAKE_BUILD_TYPE MATCHES "Release")
        MESSAGE(STATUS "Build set to release mode")
        add_compile_options(/O2)
    endif()
else()
    add_compile_options(-fconcepts -Wextra -Wall -Wextra -Wconversion -Wdouble-promotion -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion -std=c++20)
    if(APPLE)
        if(CMAKE_BUILD_TYPE MATCHES "Debug")
            MESSAGE(STATUS "Build set to debug mode")
            add_compile_options(-g -O0 -fsanitize=address)
        elseif(CMAKE_BUILD_TYPE MATCHES "Release")
            MESSAGE(STATUS "Build set to release mode")
            add_compile_options(-g0 -O2)
            add_compile_options(-march=native -mtune=native)
        endif()
    elseif(LINUX)
        if(CMAKE_BUILD_TYPE MATCHES "Debug")
            MESSAGE(STATUS "Build set to debug mode")
            add_compile_options(-g -fmax-errors=5 -DDEBUG -O0 -fsanitize=address)
        elseif(CMAKE_BUILD_TYPE MATCHES "Release")
            MESSAGE(STATUS "Build set to release mode")
            add_compile_options(-g0 -O2)
            if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64")
                add_compile_options(-march=native -mtune=native)
            elseif(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
                add_compile_options(-mcpu=native)
            endif()
        endif()
    endif()
endif()
if(CMAKE_C_COMPILER_ID STREQUAL "Clang" OR CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-lstdc++ -lm)
endif()



# TODO find a way to 

# compile object files
set(OBJECTS "")
foreach(file ${SRC})
file(RELATIVE_PATH rel_path ${CMAKE_SOURCE_DIR} ${file})
string(REPLACE "/" "_" obj_name ${rel_path})
set(object "${CMAKE_BINARY_DIR}/objects/${obj_name}.o")
list(APPEND OBJECTS ${object})
    add_custom_command(
        OUTPUT ${object}
        COMMAND ${CMAKE_CXX_COMPILER} -std=c++20 -Wall -Wextra -c ${file} -o ${object}
        DEPENDS ${source}
        COMMENT "Compiling ${file}"
    )
endforeach()
add_custom_target(compile_objects ALL DEPENDS ${OBJECTS})

# add the main executable
add_executable(${PROJECT_NAME} ${MAIN} ${OBJECTS})

# clean up objects directory
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${CMAKE_BINARY_DIR}/objects/*")