# cmake for test programs specifically for the emulator:
#  - llarm-diff: basically just a comparison between unicorn emulator and llarm-emu to check for divergences
#  - llarm-uart: just runs the linux kernel but in non-headless mode, meaning it has an output (yippee!)

cmake_minimum_required(VERSION 3.25)
project(llarm-difftest)

include("${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/dependencies.cmake")

get_filename_component(LLARM_EMU_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.." ABSOLUTE)
get_filename_component(LLARM_REPO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../.." ABSOLUTE)

find_package(PkgConfig REQUIRED)
pkg_check_modules(UNICORN unicorn)

if(NOT UNICORN_FOUND)
    message(STATUS "unicorn not found, skipping llarm-difftest")
    return()
endif()

add_dependency(
    PACKAGE_NAME llarm-emu
    SOURCE_DIR "../../"
    TARGET_NAME llarm-emu-lib
    ALIAS_TARGET llarm::llarm-emu-lib
)

add_executable(llarm-difftest diff/diff_test.cpp)

target_compile_features(llarm-difftest PRIVATE cxx_std_20)

target_include_directories(llarm-difftest PRIVATE
    ${LLARM_EMU_DIR}
    ${LLARM_EMU_DIR}/src
    ${LLARM_REPO_ROOT}/shared/include
    ${LLARM_REPO_ROOT}/llarm-asm
    ${UNICORN_INCLUDE_DIRS}
)

target_link_libraries(llarm-difftest PRIVATE ${LLARM_EMU_TARGET} ${UNICORN_LIBRARIES})

target_compile_options(llarm-difftest PRIVATE
    -Wno-old-style-cast
    -Wno-sign-conversion
    -Wno-conversion
)


add_executable(llarm-uart debug/llarm-uart.cpp)

target_include_directories(llarm-uart
    PRIVATE
        ${LLARM_EMU_DIR}
        ${LLARM_EMU_DIR}/src
        ${LLARM_REPO_ROOT}/shared/include
        ${LLARM_REPO_ROOT}/llarm-asm
)

target_link_libraries(llarm-uart
    PRIVATE
        ${LLARM_EMU_TARGET}
)