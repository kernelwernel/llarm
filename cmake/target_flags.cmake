include(${CMAKE_CURRENT_LIST_DIR}/flags.cmake)

function(configure_target_flags TARGET)
    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        target_compile_options(${TARGET} PRIVATE 
            ${COMMON_CXX_FLAGS}
            ${DEBUG_CXX_FLAGS}
        )
    elseif(CMAKE_BUILD_TYPE MATCHES "Release")
        set(CMAKE_UNITY_BUILD ON)
        
        if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
            target_compile_options(${TARGET} PRIVATE
                ${COMMON_CXX_FLAGS}
                ${RELEASE_CXX_FLAGS}
                ${EMBEDDED_CXX_FLAGS}
            )
        else()
            target_compile_options(${TARGET} PRIVATE
                ${COMMON_CXX_FLAGS}
                ${RELEASE_CXX_FLAGS}
            )
        endif()
    endif()
endfunction()