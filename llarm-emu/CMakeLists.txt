# basic info
cmake_minimum_required(VERSION 3.29 FATAL_ERROR)
project(
    llarm-emu
    VERSION 0.1 
    DESCRIPTION "ARM emulation framework"
    LANGUAGES CXX
)


find_package(llarm-asm CONFIG REQUIRED)


# includes
include("../cmake/flags.cmake") # collection of all the necessary flags
include("../cmake/variables.cmake") # general variables, usually file paths
include("../cmake/target_flags.cmake") # flag configurator
include("../cmake/build_type.cmake") # build definitions
include("../cmake/compiler.cmake") # compiler choice
include("../cmake/linker.cmake") # linker config
include("../cmake/linker_flags.cmake") # linker flag config
include("../cmake/clang_format.cmake") # clang-format
include("../cmake/clang_tidy.cmake") # clang-tidy


# targets
set(TARGET_BIN "llarm-emu-bin")
set(TARGET_LIB "llarm-emu-lib")


# general
file(GLOB_RECURSE ALL_SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp")
set(LIB_SOURCES ${ALL_SOURCES})


# clang-format
clangformat_setup(${ALL_SOURCES})


# library setup
add_library(${TARGET_LIB} STATIC ${LIB_SOURCES})
set_target_properties(${TARGET_LIB} PROPERTIES 
    OUTPUT_NAME "llarm-emu"
)


# executable setup
add_executable(${TARGET_BIN} "src/main.cpp")
target_link_libraries(${TARGET_BIN} PRIVATE ${TARGET_LIB} llarm-asm)
set_target_properties(${TARGET_BIN} PROPERTIES OUTPUT_NAME "llarm-emu")
install(TARGETS ${TARGET_BIN} RUNTIME DESTINATION /usr/bin)


# for shared/ inclusion
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)


# configure the target flags (defined in llarm/cmake/target_flags.cmake)
configure_target_flags(${TARGET_BIN})


# linker flags (defined in llarm/cmake/linker_flags.cmake)
configure_linker_flags(${TARGET_BIN})