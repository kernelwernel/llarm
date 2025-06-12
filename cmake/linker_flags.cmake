include(${CMAKE_CURRENT_LIST_DIR}/flags.cmake)

function(configure_linker_flags TARGET)
    if (LINUX)
        target_link_options(${TARGET} PRIVATE ${LINUX_COMMON_LINKER_FLAGS})
    endif()
endfunction()