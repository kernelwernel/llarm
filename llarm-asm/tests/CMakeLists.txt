# basic info
cmake_minimum_required(VERSION 3.29 FATAL_ERROR)


# includes
include("../../cmake/flags.cmake")
include("../../cmake/variables.cmake")
include("../../cmake/target_flags.cmake")
include("../../cmake/build_type.cmake")
include("../../cmake/compiler.cmake")
include("../../cmake/linker.cmake")
include("../../cmake/linker_flags.cmake")
include("../../cmake/clang_format.cmake")
include("../../cmake/clang_tidy.cmake")
include("../../cmake/dependencies.cmake")


# targets and variables
set(TARGET "disassembly-test")

# project details
project(
    disassembly-test
    VERSION 0.1 
    DESCRIPTION "Disassembly test for llarm-asm"
    LANGUAGES CXX
)

include(FetchContent)

FetchContent_Declare(
    capstone
    GIT_REPOSITORY https://github.com/capstone-engine/capstone.git
    GIT_TAG        5.0.1  # or whatever the latest stable tag is
)

set(CAPSTONE_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(CAPSTONE_BUILD_CSTOOL OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(capstone)


# find or build llarm-asm
add_dependency(
    PACKAGE_NAME llarm-asm
    SOURCE_DIR ".."
    TARGET_NAME llarm-asm-lib
    ALIAS_TARGET llarm::llarm-asm-lib
)


# source code generation
file(GLOB_RECURSE ALL_SOURCES CONFIGURE_DEPENDS "*.cpp")
set(LIB_SOURCES ${ALL_SOURCES})
foreach(source IN LISTS ALL_SOURCES)
    if(source MATCHES "${pattern}")
        list(REMOVE_ITEM LIB_SOURCES "${source}")
        break()
    endif()
endforeach()



# executable setup
add_executable(${TARGET} "arm_disassembly.cpp")
#set_target_properties(${TARGET} PROPERTIES
#    OUTPUT_NAME "llarm-asm"
#    INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}"
#    BUILD_RPATH "${CMAKE_BINARY_DIR}"
#)


# library linkage
target_link_libraries(${TARGET}
    PRIVATE
        ${LLARM_ASM_TARGET}
        capstone
)


# configure the target flags
configure_target_flags(${TARGET})
configure_linker_flags(${TARGET})