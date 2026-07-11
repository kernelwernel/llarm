cmake_minimum_required(VERSION 3.25)
project(llarm-difftest)

include("${CMAKE_CURRENT_SOURCE_DIR}/../../../cmake/dependencies.cmake")

find_package(PkgConfig REQUIRED)
pkg_check_modules(UNICORN unicorn)

if(NOT UNICORN_FOUND)
    message(STATUS "unicorn not found, skipping llarm-difftest")
    return()
endif()

# with LLARM_USE_SYSTEM_PACKAGES=ON, links against the installed llarm-emu
# (run `cmake --install` on the top-level build first). otherwise builds
# llarm-emu from source as part of this build, same as every other subproject.
add_dependency(
    PACKAGE_NAME llarm-emu
    SOURCE_DIR "../../"
    TARGET_NAME llarm-emu-lib
    ALIAS_TARGET llarm::llarm-emu-lib
)

add_executable(llarm-difftest diff_test.cpp)

target_compile_features(llarm-difftest PRIVATE cxx_std_20)

target_include_directories(llarm-difftest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../shared/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../llarm-asm
    ${UNICORN_INCLUDE_DIRS}
)

target_link_libraries(llarm-difftest PRIVATE ${LLARM_EMU_TARGET} ${UNICORN_LIBRARIES})

target_compile_options(llarm-difftest PRIVATE
    -Wno-old-style-cast
    -Wno-sign-conversion
    -Wno-conversion
)
