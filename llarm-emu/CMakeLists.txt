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


# targets
set(TARGET_BIN "llarm-emu-bin")
#set(TARGET_LIB "llarm-emu-lib")


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



set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



# clang-format
#clangformat_setup(${ALL_SOURCES})


# library setup
#add_library(${TARGET_LIB} STATIC ${LIB_SOURCES})
#set_target_properties(${TARGET_LIB} PROPERTIES 
#    OUTPUT_NAME "llarm-emu"
#)


# executable setup
#add_executable(${TARGET_BIN} "src/main.cpp")
#target_link_libraries(${TARGET_BIN} PRIVATE ${TARGET_LIB} llarm-asm)
#set_target_properties(${TARGET_BIN} PROPERTIES OUTPUT_NAME "llarm-emu")
#install(TARGETS ${TARGET_BIN} RUNTIME DESTINATION /usr/bin)


# executable setup
add_executable(${TARGET_BIN} ${ALL_SOURCES})
set_target_properties(${TARGET_BIN} PROPERTIES
    OUTPUT_NAME "llarm-emu"
    INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}"
    BUILD_RPATH "${CMAKE_BINARY_DIR}"
)


# Add include directories for when dependencies are built from source
target_include_directories(${TARGET_BIN}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../llarm-asm  # For llarm/llarm-asm.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../shared/include  # For llarm/shared/*.hpp
)


# library linkage
target_link_libraries(${TARGET_BIN}
    PRIVATE
    ${LLARM_ASM_TARGET}
)


# installations
install(TARGETS ${TARGET_BIN} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
#install(FILES llarm-asm.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/llarm)
#install(TARGETS ${TARGET_LIB}
#    EXPORT llarm-asm-lib-targets
#    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)
#install(EXPORT llarm-emu-lib-targets
#    FILE llarm-emu-config.cmake
#    NAMESPACE llarm::
#    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/llarm-emu
#)
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/llarm-emu-config-version.cmake
#    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/llarm-emu
#)


# configure the target flags (defined in llarm/cmake/target_flags.cmake)
configure_target_flags(${TARGET_BIN})


# linker flags (defined in llarm/cmake/linker_flags.cmake)
configure_linker_flags(${TARGET_BIN})