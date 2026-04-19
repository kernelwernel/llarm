find_program(CLANG_TIDY_EXE NAMES clang-tidy)

if(CLANG_TIDY_EXE)
    message(STATUS "clang-tidy enabled: ${CLANG_TIDY_EXE}")
else()
    message(STATUS "clang-tidy not found, skipping")
endif()

function(configure_clang_tidy TARGET)
    if(CLANG_TIDY_EXE)
        set_target_properties(${TARGET} PROPERTIES
            CXX_CLANG_TIDY "${CLANG_TIDY_EXE};--use-color;--extra-arg=-Wno-unknown-warning-option"
        )
    endif()
endfunction()