include(${CMAKE_CURRENT_LIST_DIR}/flags.cmake)

function(configure_target_flags TARGET)
    set(CXX_FLAGS)

    if(MSVC)
        list(APPEND CXX_FLAGS ${MSVC_CXX_FLAGS})

        if(CMAKE_BUILD_TYPE MATCHES "Debug")
            list(APPEND CXX_FLAGS ${MSVC_DEBUG_CXX_FLAGS})
        endif(CMAKE_BUILD_TYPE MATCHES "Release")
    elseif(LINUX OR APPLE)
        if(USING_COMPILER MATCHES "clang\\+\\+")
            list(APPEND CXX_FLAGS ${CLANG_CXX_FLAGS})
        elseif(USING_COMPILER MATCHES "g\\+\\+")
            list(APPEND CXX_FLAGS ${GCC_CXX_FLAGS})
        else()
            message(WARNING "Unknown compiler: ${CMAKE_CXX_COMPILER_ID}")
        endif()

        if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
            list(APPEND CXX_FLAGS ${LINUX_EMBEDDED_CXX_FLAGS})
        endif()

        if(CMAKE_BUILD_TYPE MATCHES "Release")
            list(APPEND CXX_FLAGS ${LINUX_RELEASE_CXX_FLAGS})
        elseif(CMAKE_BUILD_TYPE MATCHES "Debug")
            list(APPEND CXX_FLAGS ${LINUX_DEBUG_CXX_FLAGS})
        endif()

        #list(APPEND CXX_FLAGS ${LINUX_COMMON_LINKER_FLAGS})
    endif()

    target_compile_options(${TARGET} PRIVATE ${CXX_FLAGS})
endfunction()