# define preprocessor macros (or "build definitions") based on the build type
function(configure_build_type TARGET)
    # fetch and set build type
    set(available_build_types Debug Release)
    if(NOT CMAKE_BUILD_TYPE)
        # default to using the debug type, this is just for dev purposes
        # and should be changed when the project is production-ready
        set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
    endif()
    if(NOT CMAKE_BUILD_TYPE IN_LIST available_build_types)
        MESSAGE(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}. Allowed values: ${available_build_types}")
    endif()

    # set the macros
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_definitions(${TARGET} PRIVATE __DEBUG__)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_definitions(${TARGET} PRIVATE __RELEASE__)
    endif()
endfunction()


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Build set to debug mode")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Build set to release mode")
endif()
