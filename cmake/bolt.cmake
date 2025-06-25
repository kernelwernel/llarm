function(is_bolt_available BOLT_AVAILABLE)
    find_program(BOLT_EXECUTABLE bolt)
    
    if(BOLT_EXECUTABLE)
        message(STATUS "Bolt: llvm-bolt executable found")
        set(${BOLT_AVAILABLE} TRUE PARENT_SCOPE)
        return()
    else()
        message(STATUS "Bolt: executable not found, skipping")
        set(${BOLT_AVAILABLE} FALSE PARENT_SCOPE)
    endif()
endfunction()


function(is_perf_available PERF_AVAILABLE)
    find_program(PERF_EXECUTABLE perf)
    find_program(PERF2BOLT_EXECUTABLE perf2bolt)

    if(PERF_EXECUTABLE AND PERF2BOLT_EXECUTABLE)
        message(STATUS "Bolt: perf executables found")
        set(${PERF_AVAILABLE} TRUE PARENT_SCOPE)
        return()
    else()
        message(STATUS "Bolt: perf executables not found, skipping")
        set(${PERF_AVAILABLE} FALSE PARENT_SCOPE)
    endif()
endfunction()


function(setup_bolt TARGET)
    is_bolt_available(BOLT_AVAILABLE)

    if(NOT BOLT_AVAILABLE)
        return()
    endif()

    get_target_property(TARGET_TYPE ${TARGET} TYPE)
    if(NOT TARGET_TYPE STREQUAL "EXECUTABLE")
        message(WARNING "Bolt: unsupported target found (must be an executable), skipping")
        return()
    endif()

    # bolt doesn't necessarily require perf, but it's a better addition nonetheless
    is_perf_available(PERF_AVAILABLE)


    set(ORIGINAL_BINARY "$<TARGET_FILE:${TARGET}>")
    set(BOLT_BINARY "${ORIGINAL_BINARY}.bolt")
    set(PERF_DATA "${CMAKE_CURRENT_BINARY_DIR}/perf.data")
    set(BOLT_DATA "${CMAKE_CURRENT_BINARY_DIR}/${TARGET}.fdata")


    if(PERF_AVAILABLE)
        add_custom_command(TARGET ${TARGET} POST_BUILD
            COMMAND ${PERF_EXECUTABLE} record 
                -e cycles:u 
                -j any,u 
                -o ${PERF_DATA} 
                -- ${ORIGINAL_BINARY} $<TARGET_PROPERTY:${TARGET},BOLT_ARGS>
            COMMENT "Bolt: collecting perf data"
            VERBATIM
        )
    else()
        add_custom_command(TARGET ${TARGET} POST_BUILD
            COMMAND ${BOLT_EXECUTABLE} 
                ${TARGET}
                -instrument
                -o ${PERF_DATA} 
            COMMENT "Bolt: collecting llvm-bolt instrumentation data"
            VERBATIM
        )
    endif()

    llvm-bolt <executable> -instrument -o <instrumented-executable>



    llvm-bolt <executable> -o <executable>.bolt -data=perf.fdata -reorder-blocks=ext-tsp -reorder-functions=hfsort -split-functions -split-all-cold -split-eh -dyno-stats



#perf record -e cycles:u -j any,u -o perf.data -- <executable> <args> ...

endfunction()