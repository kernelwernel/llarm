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


# targets
set(TARGET_BIN "llarm-asm-bin")
set(TARGET_LIB "llarm-asm-lib")


# general
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


# installations
install(TARGETS ${TARGET_BIN} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES llarm-asm.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/llarm)
install(TARGETS ${TARGET_LIB}
    EXPORT llarm-asm-lib-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(EXPORT llarm-asm-lib-targets
    FILE llarm-asm-config.cmake
    NAMESPACE llarm::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/llarm-asm
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/llarm-asm-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/llarm-asm
)


# library export
write_basic_package_version_file(
    llarm-asm-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)


# configure the target flags (defined in llarm/cmake/target_flags.cmake)
configure_target_flags(${TARGET_BIN})
configure_target_flags(${TARGET_LIB})


# linker flags (defined in llarm/cmake/linker_flags.cmake)
configure_linker_flags(${TARGET_BIN})
configure_linker_flags(${TARGET_LIB})