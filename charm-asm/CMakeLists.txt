# basic info
cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(
    charm-asm
    VERSION 0.1 
    DESCRIPTION "ARM assembler and disassembler framework"
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


# define preprocessor macros based on the build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(__DEBUG__)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(__RELEASE__)
endif()


# debug/release CXX flag options
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    MESSAGE(STATUS "Build set to debug mode")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DDEBUG -O0 -fsanitize=address,undefined,nullability")
elseif(CMAKE_BUILD_TYPE MATCHES "Release")
    MESSAGE(STATUS "Build set to release mode")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -g0 -ffunction-sections -fdata-sections -ftree-vectorize -flto -fPIE -ffast-math")
    set(CMAKE_UNITY_BUILD ON)
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


# fetch source files
file(GLOB_RECURSE SOURCES
    "${PROJECT_DIR}/src/*.cpp"
)


# compile each file
set(OBJECTS "")
foreach(source ${SOURCES})
    file(RELATIVE_PATH rel_path ${CMAKE_SOURCE_DIR} ${source})
    string(REPLACE "/" "_" obj_name ${rel_path})
    set(object "${CMAKE_BINARY_DIR}/objects/${obj_name}.o")
    add_custom_command(
        OUTPUT ${object}
        COMMAND ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} ${CMAKE_INCLUDE_DIRECTORIES} -c ${source} -MMD -o ${object}
        DEPENDS ${source}
    )
endforeach()
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${OBJ_DIR}/*)


# executable setup
add_executable(charm-asm-bin ${SOURCES} "src/main.cpp")
set_target_properties(charm-asm-bin PROPERTIES OUTPUT_NAME "charm-asm")
install(TARGETS charm-asm-bin RUNTIME DESTINATION bin)


# library setup
add_library(charm-asm-lib STATIC ${SOURCES})
set_target_properties(charm-asm-lib PROPERTIES 
    OUTPUT_NAME "charm-asm"
)
install(FILES charm-asm.hpp DESTINATION include/charm)
install(DIRECTORY src/ DESTINATION include/charm/internal/charm-asm/src)
install(DIRECTORY ../shared/ DESTINATION include/charm/internal/shared)
install(TARGETS charm-asm-lib
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)