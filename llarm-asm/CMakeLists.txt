# basic info
cmake_minimum_required(VERSION 3.29 FATAL_ERROR)
project(
    llarm-asm
    VERSION 0.1 
    DESCRIPTION "ARM assembly and disassembly framework"
    LANGUAGES CXX
)


# includes
include("../cmake/flags.cmake") # collection of all the necessary flags
include("../cmake/variables.cmake") # general variables, usually file paths
include("../cmake/target_flags.cmake") # flag configurator
include("../cmake/build_type.cmake") # build definitions
include("../cmake/compiler.cmake") # compiler choice
include("../cmake/linker.cmake") # linker config
include("../cmake/linker_flags.cmake") # linker flag config
include("../cmake/clang_format.cmake") # clang-format
include("../cmake/clang-tidy.cmake") # clang-tidy



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


# to include shared/
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)


# library setup
add_library(${TARGET_LIB} STATIC ${LIB_SOURCES})
set_target_properties(${TARGET_LIB} PROPERTIES 
    OUTPUT_NAME "llarm-asm"
)


# executable setup
add_executable(${TARGET_BIN} "src/main.cpp")
set_target_properties(${TARGET_BIN} PROPERTIES OUTPUT_NAME "llarm-asm")
target_link_libraries(${TARGET_BIN} PRIVATE ${TARGET_LIB})


# executable installation
install(TARGETS ${TARGET_BIN} RUNTIME DESTINATION /usr/bin)


# library installation
install(FILES llarm-asm.hpp DESTINATION /usr/include/llarm)
install(TARGETS ${TARGET_LIB}
    EXPORT llarm-asm-lib-targets
    ARCHIVE DESTINATION /usr/lib
    LIBRARY DESTINATION /usr/lib
)


# library export
install(EXPORT llarm-asm-lib-targets
    FILE llarm-asm-config.cmake
    NAMESPACE llarm::
    DESTINATION /usr/lib/cmake/llarm-asm
)




include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    llarm-asm-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/llarm-asm-config-version.cmake
    DESTINATION /usr/lib/cmake/llarm-asm
)


# configure the target flags (defined in llarm/cmake/target_flags.cmake)
configure_target_flags(${TARGET_BIN})
configure_target_flags(${TARGET_LIB})


# linker flags (defined in llarm/cmake/linker_flags.cmake)
configure_linker_flags(${TARGET_BIN})
configure_linker_flags(${TARGET_LIB})