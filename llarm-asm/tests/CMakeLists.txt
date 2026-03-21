# basic info
cmake_minimum_required(VERSION 3.29 FATAL_ERROR)


# includes
include("../../cmake/flags.cmake")
include("../../cmake/variables.cmake")
include("../../cmake/target_flags.cmake")
include("../../cmake/build_type.cmake")
include("../../cmake/compiler.cmake")
include("../../cmake/linker.cmake")
include("../../cmake/linker_flags.cmake")
include("../../cmake/clang_format.cmake")
include("../../cmake/clang_tidy.cmake")
include("../../cmake/dependencies.cmake")


# targets and variables
set(TARGET_ARM "disassembly-test-arm")
set(TARGET_THUMB "disassembly-test-thumb")
set(TARGET_BENCH_ARM "disassembly-bench-arm")
set(TARGET_CAP "capstone-test")

# project details
project(
    disassembly-test
    VERSION 0.1 
    DESCRIPTION "ARM and thumb disassembly test fuzzing for llarm-asm"
    LANGUAGES CXX
)

include(FetchContent)

FetchContent_Declare(
    capstone
    GIT_REPOSITORY https://github.com/capstone-engine/capstone.git
    GIT_TAG        5.0.1  # or whatever the latest stable tag is
)

set(CAPSTONE_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(CAPSTONE_BUILD_CSTOOL OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(capstone)


FetchContent_Declare(
    nyxstone
    GIT_REPOSITORY https://github.com/emproof-com/nyxstone.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(nyxstone)



# patch nyxstone's broken include paths
set_target_properties(nyxstone PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ""
)
target_include_directories(nyxstone PUBLIC
    $<BUILD_INTERFACE:${nyxstone_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${nyxstone_SOURCE_DIR}/vendor>
)



# find or build llarm-asm
add_dependency(
    PACKAGE_NAME llarm-asm
    SOURCE_DIR ".."
    TARGET_NAME llarm-asm-lib
    ALIAS_TARGET llarm::llarm-asm-lib
)


# source code generation
file(GLOB_RECURSE ALL_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# executable setup
add_executable(${TARGET_ARM} "src/arm_disassembly.cpp")
add_executable(${TARGET_THUMB} "src/thumb_disassembly.cpp")
add_executable(${TARGET_BENCH_ARM} "src/arm_benchmark.cpp")
add_executable(${TARGET_CAP} "src/capstone.cpp")


target_include_directories(${TARGET_BENCH_ARM} SYSTEM PRIVATE nyxstone/include)


# library linkage
target_link_libraries(${TARGET_ARM} PRIVATE ${LLARM_ASM_TARGET} capstone)
target_link_libraries(${TARGET_THUMB} PRIVATE ${LLARM_ASM_TARGET} capstone)
target_link_libraries(${TARGET_BENCH_ARM} PRIVATE ${LLARM_ASM_TARGET} capstone)
target_link_libraries(${TARGET_CAP} PRIVATE ${LLARM_ASM_TARGET} capstone)
target_link_libraries(${TARGET_BENCH_ARM} PRIVATE ${LLARM_ASM_TARGET} nyxstone::nyxstone)



# configure the target flags
configure_target_flags(${TARGET_ARM})
configure_linker_flags(${TARGET_ARM})
configure_target_flags(${TARGET_THUMB})
configure_linker_flags(${TARGET_THUMB})
configure_target_flags(${TARGET_BENCH_ARM})
configure_linker_flags(${TARGET_BENCH_ARM})
configure_target_flags(${TARGET_CAP})
configure_linker_flags(${TARGET_CAP})