include(${CMAKE_CURRENT_LIST_DIR}/flags.cmake)

function(configure_linker_flags TARGET)
#    # use mold linker if available
#    find_program(MOLD mold)
#    if(MOLD)
#        #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=mold")
#        #set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fuse-ld=mold")
#        target_link_options(${TARGET} PRIVATE -fuse-ld=mold)
#        message(STATUS "found mold :)")
#    else()
#        message(STATUS "mold not found :(")
#    endif()
#
#
#    find_program(MOLD mold)
#    if(MOLD)
#        message(STATUS "Using mold linker")
#        target_link_options(${TARGET} PRIVATE ${COMMON_LINKER_FLAGS} -fuse-ld=mold)
#    else()
#        target_link_options(${TARGET} PRIVATE ${COMMON_LINKER_FLAGS})
#    endif()
#
#
#        # Get ACTUAL linker being used
#        execute_process(
#            COMMAND ${CMAKE_CXX_COMPILER} -Wl,--version
#            OUTPUT_VARIABLE LINKER_INFO
#            ERROR_VARIABLE LINKER_ERROR
#        )
#    
#        if(LINKER_INFO MATCHES "mold")
#            set(ACTIVE_LINKER "mold")
#        elseif(LINKER_INFO MATCHES "LLD")
#            set(ACTIVE_LINKER "lld")
#        elseif(LINKER_INFO MATCHES "GNU ld")
#            set(ACTIVE_LINKER "ld.bfd")
#        else()
#            set(ACTIVE_LINKER "unknown")
#        endif()
#    
#        message(STATUS "Active linker for ${TARGET}: ${ACTIVE_LINKER}")
#
#
#
#
#    get_filename_component(LINKER_NAME ${CMAKE_LINKER} NAME)
#    message(STATUS "Linker: ${LINKER_NAME}")
#
#    target_link_options(${TARGET} PRIVATE ${COMMON_LINKER_FLAGS})


#        unset(CMAKE_LINKER CACHE)
#        unset(CMAKE_LINKER_ID CACHE)
#
#
#        # Try to use mold if available
#        find_program(MOLD mold)
#        if(MOLD)
#            target_link_options(${TARGET} PRIVATE 
#                ${COMMON_LINKER_FLAGS}
#                -fuse-ld=mold
#            )
#        else()
#            target_link_options(${TARGET} PRIVATE 
#                ${COMMON_LINKER_FLAGS}
#            )
#        endif()
#
#
#        # Get ACTUAL linker being used
#        execute_process(
#            COMMAND ${CMAKE_CXX_COMPILER} -Wl,--version
#            OUTPUT_VARIABLE LINKER_INFO
#            ERROR_VARIABLE LINKER_ERROR
#        )
#    
#        if(LINKER_INFO MATCHES "mold")
#            set(ACTIVE_LINKER "mold")
#        elseif(LINKER_INFO MATCHES "LLD")
#            set(ACTIVE_LINKER "lld")
#        elseif(LINKER_INFO MATCHES "GNU ld")
#            set(ACTIVE_LINKER "ld.bfd")
#        else()
#            set(ACTIVE_LINKER "unknown")
#        endif()
#    
#        message(STATUS "Active linker for ${TARGET}: ${ACTIVE_LINKER}")










    # Try to use mold
    find_program(MOLD mold)
    if(MOLD)
        # Force mold usage through compiler flags
        target_link_options(${TARGET} PRIVATE 
            "LINKER:--fuse-ld=mold"
            ${COMMON_LINKER_FLAGS}
        )
        
        # Verify it worked
        execute_process(
            COMMAND ${CMAKE_CXX_COMPILER} -Wl,--version
            OUTPUT_VARIABLE LINKER_INFO
            ERROR_VARIABLE LINKER_ERROR
        )
    else()
        target_link_options(${TARGET} PRIVATE ${COMMON_LINKER_FLAGS})
    endif()
endfunction()


if(LINKER_INFO MATCHES "mold")
    message(STATUS "Successfully using mold linker")
else()
    message(STATUS "Failed to activate mold linker - using default")
endif()