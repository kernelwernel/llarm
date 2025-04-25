## Basic setup
#set(CMAKE_CXX_CLANG_TIDY 
#    clang-tidy
#    -header-filter=.*  # Check headers too
#    -use-color
#    -extra-arg=-Wno-unknown-warning-option  # Silence false positives
#)

## Optional: Specify checks (comma-separated)
#set(CMAKE_CXX_CLANG_TIDY 
#    clang-tidy
#    -checks=*
#    -warnings-as-errors=*
#)

#function(configure_clangtidy)
#    find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
#
#    if(CLANG_TIDY_EXE)
#        #set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}")
#
#        #set_target_properties(${TARGET_LIB} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
#        #set_target_properties(${TARGET_BIN} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
#        message(STATUS "Found clang-tidy: ${CLANG_TIDY_EXE}")
#        #set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
#        #set(CMAKE_CXX_CLANG_TIDY clang-tidy 
#        #    -checks=-*,
#        #    readability-*,
#        #    clang-analyzer-*,
#        #    bugprone-*,
#        #    performance-*,
#        #    portability-*
#        #)
#        set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=google-*,cppcoreguidelines-*")
#    else()
#        message(WARNING "clang-tidy not found")
#    endif()
#endfunction()



set(clang_tidy_checks
    "-*"
    "-header-filter=.*"
    "readability-*"
    "-readability-magic-numbers"
    "-readability-identifier-length"
    "-readability-function-cognitive-complexity"
    "-readability-implicit-bool-conversion"
    "-readability-qualified-auto"
    "clang-analyzer-*"
    "bugprone-*"
    "-bugprone-easily-swappable-parameters"
    "-bugprone-too-small-loop-variable"
    "performance-*"
    "portability-*"
    "modernize-*"
    "-modernize-use-trailing-return-type"
    "cppcoreguidelines-*"
    "-cppcoreguidelines-avoid-magic-numbers"
    "-cppcoreguidelines-pro-bounds-pointer-arithmetic"
)

string(JOIN "," clang_tidy_check_string ${clang_tidy_checks})

set(CMAKE_CXX_CLANG_TIDY clang-tidy "-checks=${clang_tidy_check_string}")