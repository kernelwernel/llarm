 # clang-tidy is off by default due to the compilation slowdown
option(ENABLE_CLANG_TIDY "Run clang-tidy during build" OFF)

find_program(CLANG_TIDY_EXE NAMES clang-tidy)

if(CLANG_TIDY_EXE AND ENABLE_CLANG_TIDY)
    message(STATUS "clang-tidy enabled: ${CLANG_TIDY_EXE}")
elseif(NOT CLANG_TIDY_EXE)
    message(STATUS "clang-tidy not found, skipping")
else()
    message(STATUS "clang-tidy disabled")
endif()

function(configure_clang_tidy TARGET)
    if(CLANG_TIDY_EXE AND ENABLE_CLANG_TIDY AND CMAKE_BUILD_TYPE STREQUAL "Debug")
        set_target_properties(${TARGET} PROPERTIES
            CXX_CLANG_TIDY "${CLANG_TIDY_EXE};--use-color;--extra-arg=-Wno-unknown-warning-option"
        )
    endif()
endfunction()