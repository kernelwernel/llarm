# basic info
cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(
    charm
    VERSION 0.1 
    DESCRIPTION "ARM emulator framework"
    LANGUAGES CXX
)


# compiler flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-w -Wall -Wextra -Werror -Wshadow -Wconversion -Wunused -Wpedantic -Wpedantic -Wpedantic-errors -Weverything -fmodules-ts")
set(CMAKE_EXE_LINKER_FLAGS "-lstdc++ -lm")


## g++/clang++ compiler choice
find_program(CLANGPP_EXECUTABLE NAMES clang++)
if(CLANGPP_EXECUTABLE)
    set(CMAKE_CXX_COMPILER "${CLANGPP_EXECUTABLE}")
else()
    set(CMAKE_CXX_COMPILER "g++")
endif()
get_filename_component(COMPILER_NAME ${CMAKE_CXX_COMPILER} NAME)
MESSAGE(STATUS "Using ${COMPILER_NAME} compiler")


# fetch and set build type
set(available_build_types Debug Release)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
if(NOT CMAKE_BUILD_TYPE IN_LIST available_build_types)
    MESSAGE(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}. Allowed values: ${available_build_types}")
endif()


# Define preprocessor macros based on the build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(__DEBUG__)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(__RELEASE__)
endif()


# debug/release CXX flag options
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    MESSAGE(STATUS "Build set to debug mode")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DDEBUG -O0 -fsanitize=address,undefined,nullability") # -fsanitize=address,undefined,nullability
#  --analyze --end-no-unused-arguments -fcf-protection=full
elseif(CMAKE_BUILD_TYPE MATCHES "Release")
    MESSAGE(STATUS "Build set to release mode")
    set(CMAKE_UNITY_BUILD ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g0 -flto")
    if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -mtune=native")
    elseif(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcpu=native")
    endif()
endif()


# general variables
set(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(BUILD_DIR "${PROJECT_DIR}/build")
set(OBJ_DIR "${BUILD_DIR}/objects")
set(TARGET "charm")


# directories and dependencies
#add_subdirectory(src/charm-asm ${CMAKE_CURRENT_BINARY_DIR}/charm-asm)


# compile all source files
#include_directories(${CMAKE_SOURCE_DIR}/charm-asm)
file(GLOB_RECURSE SRC
"${PROJECT_DIR}/src/*.cpp"
#"${PROJECT_DIR}/../charm-asm/src/*.cpp"
    #"${PROJECT_DIR}/src/main.cpp"
    )
list(REMOVE_ITEM SRC 
"${PROJECT_DIR}/../charm-asm/src/main.cpp"
)
set(OBJECTS "")
foreach(source ${SRC})

#get_filename_component(filename ${source} NAME_WE)
#set(object "${OBJ_DIR}/${filename}.o")
#list(APPEND OBJECTS ${object})

file(RELATIVE_PATH rel_path ${CMAKE_SOURCE_DIR} ${source})
string(REPLACE "/" "_" obj_name ${rel_path})
set(object "${CMAKE_BINARY_DIR}/objects/${obj_name}.o")

add_custom_command(
    OUTPUT ${object}
    COMMAND ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} ${CMAKE_INCLUDE_DIRECTORIES} -c ${source} -MMD -o ${object}
    DEPENDS ${source}
    COMMENT "Compiling ${source}"
)
endforeach()
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${OBJ_DIR}/*)




# generate executable
add_executable(${TARGET} ${SRC} ${MAIN_SOURCE_FILE})

set(SHARED_DIR "${CMAKE_SOURCE_DIR}/../shared")
include_directories(${SHARED_DIR})

# OR the more modern target-specific approach:
target_include_directories(${TARGET} PRIVATE ${SHARED_DIR})

#target_link_libraries(charm PRIVATE charm-asm)
#
#target_include_directories(charm PRIVATE
#    ${CMAKE_CURRENT_SOURCE_DIR}/src
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/charm-asm
#    ${CMAKE_CURRENT_SOURCE_DIR}/../shared/
#)



# MAKE SURE TO USE THIS (for the static library link for charm-asm)
#target_link_libraries(charm-emu PRIVATE charm-asm)