function(configure_compiler)
    # find available compilers
    find_program(CLANGPP_EXECUTABLE NAMES clang++)
    find_program(GPP_EXECUTABLE NAMES g++)

    # select compiler with preference for clang++ (just a personal choice of mine, i'm kinda obsessed with llvm honestly)
    if(CLANGPP_EXECUTABLE)
        set(CMAKE_CXX_COMPILER "${CLANGPP_EXECUTABLE}" PARENT_SCOPE)
        get_filename_component(COMPILER_NAME ${CLANGPP_EXECUTABLE} NAME)
    elseif(GPP_EXECUTABLE)
        set(CMAKE_CXX_COMPILER "${GPP_EXECUTABLE}" PARENT_SCOPE)
        get_filename_component(COMPILER_NAME ${GPP_EXECUTABLE} NAME)
    endif()

    set(USING_COMPILER "${COMPILER_NAME}" PARENT_SCOPE)
    
    message(STATUS "Compiler: ${COMPILER_NAME}")
    #message(STATUS "Compiler version: ${CMAKE_CXX_COMPILER_VERSION}")
endfunction()
