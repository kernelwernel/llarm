# basic info
cmake_minimum_required(VERSION 3.29 FATAL_ERROR)


# dependencies
include(FetchContent)
fetchcontent_declare(
    string-view-lite
    GIT_REPOSITORY https://github.com/martinmoene/string-view-lite.git
    GIT_TAG        v1.8.0
    GIT_SHALLOW    TRUE
    SYSTEM
)
fetchcontent_declare(
    robin-hood-hashing
    GIT_REPOSITORY https://github.com/martinus/robin-hood-hashing.git
    GIT_TAG        3.11.5
    GIT_SHALLOW    TRUE
    SYSTEM
)
fetchcontent_makeavailable(string-view-lite robin-hood-hashing)


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


# targets and variables
set(TARGET_LIB "llarm-shared-lib")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# project details
project(
    llarm-shared
    VERSION 0.1 
    DESCRIPTION "Shared utilities for LLARM toolchain"
    LANGUAGES CXX
)
    

# extra includes
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)


# source code collection
file(GLOB_RECURSE ALL_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
set(LIB_SOURCES ${ALL_SOURCES})
set(EXCLUDE_PATTERNS
    ".*/main\\.cpp"
)
foreach(source IN LISTS ALL_SOURCES)
    foreach(pattern IN LISTS EXCLUDE_PATTERNS)
        if(source MATCHES "${pattern}")
            list(REMOVE_ITEM LIB_SOURCES "${source}")
            break()
        endif()
    endforeach()
endforeach()


# library setup
add_library(${TARGET_LIB} SHARED ${LIB_SOURCES})
set_target_properties(${TARGET_LIB} PROPERTIES
    CXX_VISIBILITY_PRESET default
    VISIBILITY_INLINES_HIDDEN NO
    OUTPUT_NAME "llarm-shared"
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)
target_include_directories(${TARGET_LIB}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Expose FetchContent include dirs directly at build time so that they
# propagate to consumers without recording a target-name dependency.
# At install time INSTALL_INTERFACE covers everything via the installed headers.
get_target_property(_sv_includes nonstd::string-view-lite INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(_rh_includes robin_hood::robin_hood   INTERFACE_INCLUDE_DIRECTORIES)

target_include_directories(${TARGET_LIB}
    PUBLIC
        $<BUILD_INTERFACE:${_sv_includes}>
        $<BUILD_INTERFACE:${_rh_includes}>
)

# PRIVATE so the FetchContent target names don't end up in the exported config
target_link_libraries(${TARGET_LIB}
    PRIVATE
        nonstd::string-view-lite
        robin_hood::robin_hood
)

# Install the FetchContent headers alongside llarm-shared's own headers so
# INSTALL_INTERFACE consumers can find <nonstd/string_view.hpp> and <robin_hood.h>
install(DIRECTORY
    "${string-view-lite_SOURCE_DIR}/include/"
    "${robin-hood-hashing_SOURCE_DIR}/src/"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h"
)


# installation
install(TARGETS ${TARGET_LIB}
    EXPORT llarm-shared-lib-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT llarm-shared-lib-targets
    FILE llarm-shared-config.cmake
    NAMESPACE llarm::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/llarm-shared
)


# library package export
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/llarm-shared-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/llarm-shared-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/llarm-shared
)


# custom flag configurations
configure_target_flags(${TARGET_LIB})
configure_linker_flags(${TARGET_LIB})