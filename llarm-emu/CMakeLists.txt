# basic info
cmake_minimum_required(VERSION 3.29 FATAL_ERROR)


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
include("../cmake/dependencies.cmake") # dependency management


# targets and variables
set(TARGET_BIN "llarm-emu-bin")
set(TARGET_LIB "llarm-emu-lib")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# project details
project(
    llarm-emu
    VERSION 0.1 
    DESCRIPTION "ARM emulation framework"
    LANGUAGES CXX
)


# extra includes
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)


# find or build llarm-asm
add_dependency(
    PACKAGE_NAME llarm-asm
    SOURCE_DIR "../llarm-asm"
    TARGET_NAME llarm-asm-lib
    ALIAS_TARGET llarm::llarm-asm-lib
)


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
    OUTPUT_NAME "llarm-emu"
    INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}"
)

#target_include_directories(${TARGET_LIB}
#    PUBLIC
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
#        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/llarm/asm>
#)


# Add include directories for dependencies built from source
target_include_directories(${TARGET_LIB}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../llarm-asm
        ${CMAKE_CURRENT_SOURCE_DIR}/../shared/include
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/llarm/emu>
)



# executable setup
add_executable(${TARGET_BIN} "src/main.cpp")
set_target_properties(${TARGET_BIN} PROPERTIES
    OUTPUT_NAME "llarm-emu"
    INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}"
    BUILD_RPATH "${CMAKE_BINARY_DIR}"
)


# library linkage
target_link_libraries(${TARGET_BIN}
    PRIVATE
        ${TARGET_LIB}
        ${LLARM_ASM_TARGET}
)

target_link_libraries(${TARGET_LIB}
    PUBLIC
        ${LLARM_ASM_TARGET}
)


# configure the target flags
configure_target_flags(${TARGET_BIN})
configure_target_flags(${TARGET_LIB})


# linker flags
configure_linker_flags(${TARGET_BIN})
configure_linker_flags(${TARGET_LIB})


# library package export
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/llarm-emu-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/llarm-emu-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/llarm-emu
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/llarm-emu-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)


# installations
install(TARGETS ${TARGET_BIN} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES llarm/llarm-emu.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/llarm)
install(DIRECTORY src/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/llarm/emu/src
    FILES_MATCHING PATTERN "*.hpp"
)
install(TARGETS ${TARGET_LIB}
    EXPORT llarm-emu-lib-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(EXPORT llarm-emu-lib-targets
    FILE llarm-emu-targets.cmake
    NAMESPACE llarm::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/llarm-emu
)
install(FILES 
    ${CMAKE_CURRENT_BINARY_DIR}/llarm-emu-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/llarm-emu-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/llarm-emu
)