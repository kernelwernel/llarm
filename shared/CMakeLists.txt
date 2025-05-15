# basic info
cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(
    llarm-shared
    VERSION 0.1
    DESCRIPTION "Internally shared utilities for LLARM subprojects"
    LANGUAGES CXX
)


# includes
include("../cmake/flags.cmake") # collection of all the necessary flags
include("../cmake/variables.cmake") # general variables, usually file paths
include("../cmake/target_flags.cmake") # flag configurator
include("../cmake/build_type.cmake") # build definitions
include("../cmake/compiler.cmake") # compiler choice
include("../cmake/linker_flags.cmake") # linker config


# general
set(TARGET "llarm-shared-lib")
file(GLOB_RECURSE SOURCES
    "${PROJECT_DIR}/*.cpp"
)
add_library(${TARGET} STATIC ${SOURCES})
set_target_properties(${TARGET} PROPERTIES 
    OUTPUT_NAME "llarm-shared"
)


# select the compiler, preferably clang++ (defined in llarm/cmake/compiler.cmake)
configure_compiler()


# define compiler macros and the release/debug build type (defined in llarm/cmake/build_type.cmake)
config_build_type(${TARGET})


# configure the target flags (defined in llarm/cmake/config_flags.cmake)
configure_target_flags(${TARGET})


# linker flags
configure_linker_flags(${TARGET})


# Install and export the target
install(TARGETS ${TARGET}
    EXPORT llarm-shared-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)


# generate the package
install(EXPORT llarm-shared-targets
    FILE llarm-shared-config.cmake
    NAMESPACE llarm::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/llarm-shared
)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/llarm-shared-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/llarm-shared-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/llarm-shared
)




install(DIRECTORY tools/ DESTINATION include/llarm/internal/shared/tools)
install(FILES out.hpp types.hpp util.hpp DESTINATION include/llarm/internal/shared)
install(TARGETS ${TARGET}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)