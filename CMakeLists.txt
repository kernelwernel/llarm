cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

project(llarm VERSION 0.1 LANGUAGES CXX)

# includes shared by all subprojects
include("cmake/flags.cmake")
include("cmake/variables.cmake")
include("cmake/target_flags.cmake")
include("cmake/build_type.cmake")
include("cmake/compiler.cmake")
include("cmake/linker.cmake")
include("cmake/linker_flags.cmake")
include("cmake/clang_format.cmake")
include("cmake/clang_tidy.cmake")
include("cmake/dependencies.cmake")

# the order matters, each depends on the one above it
add_subdirectory(shared)
add_subdirectory(llarm-asm)
add_subdirectory(llarm-emu)