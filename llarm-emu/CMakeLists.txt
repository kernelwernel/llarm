# basic info
cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(
    llarm-emu
    VERSION 0.1 
    DESCRIPTION "ARM emulation framework"
    LANGUAGES CXX
)


include(ExternalProject)
ExternalProject_Add(
    llarm-asm
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../llarm-asm"
    BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/llarm-asm-build"
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}  # Optional: Consistent install dir
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}         # Inherit build type
    # BUILD_ALWAYS OFF  # Uncomment to prevent unnecessary rebuilds
    # INSTALL_COMMAND ""  # Uncomment to skip installation
)


# includes
include("../cmake/flags.cmake") # collection of all the necessary flags
include("../cmake/variables.cmake") # general variables, usually file paths
include("../cmake/target_flags.cmake") # flag configurator
include("../cmake/build_type.cmake") # build definitions
include("../cmake/compiler.cmake") # compiler choice
include("../cmake/linker_flags.cmake") # linker config


# targets
set(TARGET_BIN "llarm-emu-bin")


# general
file(GLOB_RECURSE ALL_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
set(LIB_SOURCES ${ALL_SOURCES})


# library setup
add_library(${TARGET_LIB} STATIC ${LIB_SOURCES})
set_target_properties(${TARGET_LIB} PROPERTIES 
    OUTPUT_NAME "llarm-emu"
)


# executable setup
add_executable(${TARGET_BIN} "src/main.cpp")
target_link_libraries(llarm-emu-bin PRIVATE STATIC libllarm-asm.a)
set_target_properties(${TARGET_BIN} PROPERTIES OUTPUT_NAME "llarm-emu")
install(TARGETS ${TARGET_BIN} RUNTIME DESTINATION /usr/bin)


# to include shared/
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)


# select the compiler, preferably clang++ (defined in llarm/cmake/compiler.cmake)
configure_compiler()


# define compiler macros and the release/debug build type (defined in llarm/cmake/build_type.cmake)
configure_build_type(${TARGET_BIN})


# configure the target flags (defined in llarm/cmake/target_flags.cmake)
configure_target_flags(${TARGET_BIN})


# linker flags (defined in llarm/cmake/linker_flags.cmake)
configure_linker_flags(${TARGET_BIN})