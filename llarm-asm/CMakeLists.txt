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
set(TARGET_BIN "llarm-asm-bin")
set(TARGET_LIB "llarm-asm-lib")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# project details
project(
    llarm-asm
    VERSION 0.1 
    DESCRIPTION "ARM assembly and disassembly framework"
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


# source code generation
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
    OUTPUT_NAME "llarm-asm"
    INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}"
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)

#target_include_directories(${TARGET_LIB}
#    PUBLIC
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
#        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/llarm/asm>
#)


target_include_directories(${TARGET_LIB}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/llarm/asm>
)


# executable setup
add_executable(${TARGET_BIN} "src/main.cpp")
set_target_properties(${TARGET_BIN} PROPERTIES
    OUTPUT_NAME "llarm-asm"
    INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}"
    BUILD_RPATH "${CMAKE_BINARY_DIR}"
)


# library linkage
target_link_libraries(${TARGET_BIN}
    PRIVATE
        ${TARGET_LIB}
        ${LLARM_SHARED_TARGET}
)

target_link_libraries(${TARGET_LIB}
    PUBLIC
        ${LLARM_SHARED_TARGET}
)


# configure the target flags
configure_target_flags(${TARGET_BIN})
configure_target_flags(${TARGET_LIB})


# linker flags
configure_linker_flags(${TARGET_BIN})
configure_linker_flags(${TARGET_LIB})


# library package export
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/llarm-asm-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/llarm-asm-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/llarm-asm
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/llarm-asm-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)


# installations
install(TARGETS ${TARGET_BIN} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES llarm/llarm-asm.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/llarm)
install(DIRECTORY src/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/llarm/asm/src
    FILES_MATCHING PATTERN "*.hpp"
)
install(TARGETS ${TARGET_LIB}
    EXPORT llarm-asm-lib-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(EXPORT llarm-asm-lib-targets
    FILE llarm-asm-targets.cmake
    NAMESPACE llarm::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/llarm-asm
)
install(FILES 
    ${CMAKE_CURRENT_BINARY_DIR}/llarm-asm-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/llarm-asm-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/llarm-asm
)