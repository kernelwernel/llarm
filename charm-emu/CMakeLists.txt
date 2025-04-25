# basic info
cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(
    charm-emu
    VERSION 0.1 
    DESCRIPTION "ARM emulation framework"
    LANGUAGES CXX
)


include(ExternalProject)
ExternalProject_Add(
    charm-asm
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../charm-asm"
    BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/charm-asm-build"  # Better practice
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
set(TARGET_BIN "charm-emu-bin")
set(TARGET_LIB "charm-emu-lib")


# general
file(GLOB_RECURSE ALL_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
set(LIB_SOURCES ${ALL_SOURCES})
#set(EXCLUDE_PATTERNS
#    ".*/main\\.cpp"
#)
#foreach(source IN LISTS ALL_SOURCES)
#    foreach(pattern IN LISTS EXCLUDE_PATTERNS)
#        if(source MATCHES "${pattern}")
#            list(REMOVE_ITEM LIB_SOURCES "${source}")
#            break()
#        endif()
#    endforeach()
#endforeach()


# library setup
add_library(${TARGET_LIB} STATIC ${LIB_SOURCES})
set_target_properties(${TARGET_LIB} PROPERTIES 
    OUTPUT_NAME "charm-emu"
)
#install(FILES charm-asm.hpp DESTINATION include/charm)
#install(DIRECTORY src/ DESTINATION include/charm/internal/charm-asm/src)
#install(TARGETS ${TARGET_LIB}
#    ARCHIVE DESTINATION lib
#    LIBRARY DESTINATION lib
#)


# executable setup
add_executable(${TARGET_BIN} "src/main.cpp")
set_target_properties(${TARGET_BIN} PROPERTIES OUTPUT_NAME "charm-emu")
target_link_libraries(${TARGET_BIN} PRIVATE ${TARGET_LIB})
install(TARGETS ${TARGET_BIN} RUNTIME DESTINATION bin)


# to include shared/
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)


# select the compiler, preferably clang++ (defined in charm/cmake/compiler.cmake)
configure_compiler()


# define compiler macros and the release/debug build type (defined in charm/cmake/build_type.cmake)
config_build_type(${TARGET_BIN})
#config_build_type(${TARGET_LIB})


# configure the target flags (defined in charm/cmake/target_flags.cmake)
configure_target_flags(${TARGET_BIN})
#configure_target_flags(${TARGET_LIB})


# linker flags (defined in charm/cmake/linker_flags.cmake)
configure_linker_flags(${TARGET_BIN})
#configure_linker_flags(${TARGET_LIB})