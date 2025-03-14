cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(
    charm
    DESCRIPTION "ARM emulation framework"
    LANGUAGES CXX
)


# set standards
if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# compiler flags
if (MSVC)
    add_compile_options(/Wall /W4 /EHsc)
else()
    # linux and apple
    add_compile_options(-std=c++20 -Wextra -fconcepts -Wall -Wextra -Wconversion -Wdouble-promotion -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion)
endif()

if(CMAKE_C_COMPILER_ID STREQUAL "Clang" OR CMAKE_C_COMPILER_ID STREQUAL "GNU")
add_compile_options(-std=c++20 -lstdc++ -lm)
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
add_compile_definitions(__CHARM_DEBUG__)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
add_compile_definitions(__CHARM_RELEASE__)
endif()









# Ensure compiler supports C++20
#include(CheckCXXCompilerFlag)
#check_cxx_compiler_flag("-std=c++20" HAS_CPP20_SUPPORT)
#if (NOT HAS_CPP20_SUPPORT)
#    message(FATAL_ERROR "Your compiler does not support C++20.")
#endif()
#
## Set compiler flags
#if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
#    add_compile_options(-std=c++20 -fconcepts -Wall -Wextra -Wconversion -Wdouble-promotion -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion)
#endif()
#
## Fetch and set build type
#set(available_build_types Debug Release)
#if(NOT CMAKE_BUILD_TYPE)
#    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
#endif()
#if(NOT CMAKE_BUILD_TYPE IN_LIST available_build_types)
#    message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}. Allowed values: ${available_build_types}")
#endif()
#
## Define preprocessor macros based on the build type
#if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#    add_compile_definitions(__DEBUG__)
#elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
#    add_compile_definitions(__RELEASE__)
#endif()

set(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(LIB_DIR "${PROJECT_DIR}/lib")
set(BUILD_DIR "${PROJECT_DIR}/build")
set(OBJ_DIR "${BUILD_DIR}/objects")
set(TARGET "charm")


set(MAIN lol/lol.cpp)

include_directories(include)

file(GLOB_RECURSE SRC "${CMAKE_SOURCE_DIR}/lol/*.cpp")

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