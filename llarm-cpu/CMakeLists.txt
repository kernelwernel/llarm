# basic info
cmake_minimum_required(VERSION 3.29 FATAL_ERROR)


# includes
include("../cmake/flags.cmake")
include("../cmake/variables.cmake")
include("../cmake/target_flags.cmake")
include("../cmake/build_type.cmake")
include("../cmake/compiler.cmake")
include("../cmake/linker.cmake")
include("../cmake/linker_flags.cmake")
include("../cmake/clang_format.cmake")
include("../cmake/clang_tidy.cmake")
include("../cmake/dependencies.cmake")


# targets and variables
set(TARGET_BIN "llarm-cpu-bin")
set(TARGET_LIB "llarm-cpu-lib")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# project details
project(
    llarm-cpu
    VERSION 0.1
    DESCRIPTION "ARM CPU information fetching library and tool"
    LANGUAGES CXX
)


# extra includes
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)


# find or build llarm-shared
add_dependency(
    PACKAGE_NAME llarm-shared
    SOURCE_DIR "../shared"
    TARGET_NAME llarm-shared-lib
    ALIAS_TARGET llarm::llarm-shared-lib
)


# header-only library
add_library(${TARGET_LIB} INTERFACE)

target_include_directories(${TARGET_LIB}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${TARGET_LIB}
    INTERFACE
        ${LLARM_SHARED_TARGET}
)


# executable setup
add_executable(${TARGET_BIN} "main.cpp")
set_target_properties(${TARGET_BIN} PROPERTIES
    OUTPUT_NAME "llarm-cpu"
    INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}"
    BUILD_RPATH "${CMAKE_BINARY_DIR}"
)

target_link_libraries(${TARGET_BIN}
    PRIVATE
        ${TARGET_LIB}
        ${LLARM_SHARED_TARGET}
)


# configure the target flags (binary only — INTERFACE lib has no compile step)
configure_target_flags(${TARGET_BIN})
configure_linker_flags(${TARGET_BIN})


# library package export
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/llarm-cpu-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/llarm-cpu-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/llarm-cpu
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/llarm-cpu-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)


# installations
install(TARGETS ${TARGET_BIN} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES
    llarm/llarm-cpu.h
    llarm/llarm-cpu.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/llarm
)
install(TARGETS ${TARGET_LIB}
    EXPORT llarm-cpu-lib-targets
)
install(EXPORT llarm-cpu-lib-targets
    FILE llarm-cpu-targets.cmake
    NAMESPACE llarm::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/llarm-cpu
)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/llarm-cpu-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/llarm-cpu-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/llarm-cpu
)
