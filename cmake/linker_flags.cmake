include(${CMAKE_CURRENT_LIST_DIR}/flags.cmake)

function(configure_linker_flags TARGET)
    if (LINUX)
        target_link_options(${TARGET} PRIVATE ${LINUX_COMMON_LINKER_FLAGS})
    endif()

    if(NOT MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        if(LLARM_USE_TSAN)
            target_link_options(${TARGET} PRIVATE ${LINUX_DEBUG_TSAN_CXX_FLAGS})
        else()
            target_link_options(${TARGET} PRIVATE ${LINUX_DEBUG_ASAN_CXX_FLAGS})
        endif()

        # 32-bit ARM (not arm64/aarch64, which has native 8-byte atomics) has no
        # lock-free 8-byte atomics in hardware, so libasan/libtsan's
        # __atomic_load_8/__atomic_store_8 references need libatomic explicitly
        # linked. Linux-only: macOS has no standalone libatomic to link against,
        # and CMAKE_SYSTEM_PROCESSOR there is "arm64" for Apple Silicon anyway.
        if(LINUX AND CMAKE_SYSTEM_PROCESSOR STREQUAL "arm")
            target_link_libraries(${TARGET} PRIVATE atomic)
        endif()
    endif()
endfunction()