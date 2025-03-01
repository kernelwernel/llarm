# basic info
cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(
    charm
    DESCRIPTION "ARM emulator framework"
    LANGUAGES CXX
)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++20" HAS_CPP20_SUPPORT)
if (NOT HAS_CPP20_SUPPORT)
    message(FATAL_ERROR "Your compiler does not support C++20.")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_program(CLANGPP_EXECUTABLE NAMES clang++)
if(CLANGPP_EXECUTABLE)
set(CMAKE_CXX_COMPILER "${CLANGPP_EXECUTABLE}")
else()
set(CMAKE_CXX_COMPILER "g++")
endif()
get_filename_component(COMPILER_NAME ${CMAKE_CXX_COMPILER} NAME)
MESSAGE(STATUS "Using ${COMPILER_NAME} compiler")



# compiler flags

#if (MSVC)
#    set(CMAKE_CXX_FLAGS "/Wall /W4 /EHsc")
#else()
#    set(CMAKE_CXX_FLAGS "-Wextra -Wall -Wextra -Wconversion -Wdouble-promotion -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion")
#endif()

if(CMAKE_C_COMPILER_ID STREQUAL "Clang" OR CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -lstdc++ -lm")
endif()


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
if (MSVC)
    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        MESSAGE(STATUS "Build set to debug mode")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Od")
    elseif(CMAKE_BUILD_TYPE MATCHES "Release")
        MESSAGE(STATUS "Build set to release mode")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O3")
    endif()
elseif(LINUX)
    list(APPEND CMAKE_CXX_FLAGS "-std=c++20")
    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        MESSAGE(STATUS "Build set to debug mode")
        list(APPEND CMAKE_CXX_FLAGS "-g" "-Wall" "-Werror" "-DDEBUG" "-O0" "-fsanitize=address")
        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        list(APPEND CMAKE_CXX_FLAGS "-ferror-limit=5")
        elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        list(APPEND CMAKE_CXX_FLAGS "-fmax-errors=5")
        endif()
    elseif(CMAKE_BUILD_TYPE MATCHES "Release")
        MESSAGE(STATUS "Build set to release mode")
        list(APPEND CMAKE_CXX_FLAGS "-Wall" "-Werror" "-g0" "-O2")
        if (CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
            list(APPEND CMAKE_CXX_FLAGS "-march=native" "-mtune=native")
        elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
            list(APPEND CMAKE_CXX_FLAGS "-mcpu=native")
        endif()
    endif()
endif()




set(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(LIB_DIR "${PROJECT_DIR}/lib")
set(BUILD_DIR "${PROJECT_DIR}/build")
set(OBJ_DIR "${BUILD_DIR}/objects")
set(TARGET "charm")




set(MAIN src/main.cpp)

include_directories(include)

file(GLOB_RECURSE SRC "${CMAKE_SOURCE_DIR}/src/*.cpp")

list(REMOVE_DUPLICATES SRC)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/objects)

set(OBJECTS "")
foreach(source ${SRC})
    file(RELATIVE_PATH rel_path ${CMAKE_SOURCE_DIR} ${source})
    string(REPLACE "/" "_" obj_name ${rel_path})
    set(object "${CMAKE_BINARY_DIR}/objects/${obj_name}.o")
    list(APPEND OBJECTS ${object})
    add_custom_command(
        OUTPUT ${object}
        COMMAND ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} -I${CMAKE_SOURCE_DIR}/include -c ${source} -o ${object}
        DEPENDS ${source}
        COMMENT "Compiling ${source}"
    )
endforeach()
add_custom_target(compile_objects ALL DEPENDS ${OBJECTS})

add_executable(my_program ${MAIN} ${OBJECTS})

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${CMAKE_BINARY_DIR}/objects/*")
#target_link_libraries(main hello)


## CTest stuff
#include(CTest)
##find_package(Python REQUIRED)
#enable_testing()
#if(MSVC)
#add_test(executable, "${BUILD_DIR}/Release/${TARGET}")
#else()
#add_test(executable, "${BUILD_DIR}/${TARGET}")
#endif()


# release stuff
#if (NOT MSVC)
#    if(CMAKE_BUILD_TYPE MATCHES "Release")
#        install(TARGETS ${TARGET} DESTINATION /usr/local/bin)
#        install(FILES "src/vmaware.hpp" DESTINATION /usr/include)
#    else()
#        install(TARGETS ${TARGET} DESTINATION ${CMAKE_SOURCE_DIR})
#    endif()
#elseif(MSVC)
#    set(CMAKE_INSTALL_PREFIX "C:\\Program Files\\YourApplication")
#    install(TARGETS ${TARGET} DESTINATION .)
#endif()