cmake_minimum_required(VERSION 3.25)
project(llarm-difftest)

find_package(PkgConfig REQUIRED)
pkg_check_modules(UNICORN unicorn)

if(NOT UNICORN_FOUND)
    message(STATUS "unicorn not found, skipping llarm-difftest")
    return()
endif()

add_executable(llarm-difftest diff_test.cpp)

target_compile_features(llarm-difftest PRIVATE cxx_std_20)

target_include_directories(llarm-difftest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../llarm-asm
    ${UNICORN_INCLUDE_DIRS}
)

find_library(LLARM_ASM_LIB llarm-asm REQUIRED)

if(TARGET llarm-emu-lib)
    target_link_libraries(llarm-difftest PRIVATE llarm-emu-lib ${LLARM_ASM_LIB} ${UNICORN_LIBRARIES})
else()
    find_library(LLARM_EMU_LIB llarm-emu REQUIRED)
    target_link_libraries(llarm-difftest PRIVATE ${LLARM_EMU_LIB} ${LLARM_ASM_LIB} ${UNICORN_LIBRARIES})
endif()

target_compile_options(llarm-difftest PRIVATE
    -Wno-old-style-cast
    -Wno-sign-conversion
    -Wno-conversion
)
