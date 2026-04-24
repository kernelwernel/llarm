# Function to find a package or build it from source
# Usage: find_or_build_dependency(
#   PACKAGE_NAME <name>
#   SOURCE_DIR <relative_path>
#   TARGET_NAME <target>
#   [ALIAS_TARGET <namespaced_target>]
# )
option(LLARM_USE_SYSTEM_PACKAGES "Use system-installed LLARM packages instead of building from source" OFF)

function(add_dependency)
    set(options "")
    set(oneValueArgs PACKAGE_NAME SOURCE_DIR TARGET_NAME ALIAS_TARGET)
    set(multiValueArgs "")
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT ARG_PACKAGE_NAME)
        message(FATAL_ERROR "PACKAGE_NAME is required")
    endif()
    if(NOT ARG_SOURCE_DIR)
        message(FATAL_ERROR "SOURCE_DIR is required")
    endif()
    if(NOT ARG_TARGET_NAME)
        message(FATAL_ERROR "TARGET_NAME is required")
    endif()

    if(NOT ARG_ALIAS_TARGET)
        set(ARG_ALIAS_TARGET "llarm::${ARG_TARGET_NAME}")
    endif()

    string(TOUPPER "${ARG_PACKAGE_NAME}" PACKAGE_NAME_UPPER)
    string(REPLACE "-" "_" PACKAGE_NAME_UPPER "${PACKAGE_NAME_UPPER}")

    if(TARGET ${ARG_TARGET_NAME})
        message(STATUS "${ARG_PACKAGE_NAME} target already exists, skipping...")
        set(${PACKAGE_NAME_UPPER}_TARGET "${ARG_TARGET_NAME}" PARENT_SCOPE)
        return()
    endif()

    set(DEP_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${ARG_SOURCE_DIR}")
    set(_package_found FALSE)

    if(LLARM_USE_SYSTEM_PACKAGES)
        find_package(${ARG_PACKAGE_NAME} CONFIG QUIET)
        if(${ARG_PACKAGE_NAME}_FOUND)
            set(_package_found TRUE)
        endif()
    endif()

    if(_package_found)
        message(STATUS "Found ${ARG_PACKAGE_NAME}: ${${ARG_PACKAGE_NAME}_DIR}")
        set(${PACKAGE_NAME_UPPER}_TARGET "${ARG_ALIAS_TARGET}" PARENT_SCOPE)
    elseif(EXISTS "${DEP_SOURCE_DIR}/CMakeLists.txt")
        message(STATUS "Building ${ARG_PACKAGE_NAME} from source...")
        set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "" FORCE)
        add_subdirectory("${DEP_SOURCE_DIR}" "${CMAKE_BINARY_DIR}/${ARG_PACKAGE_NAME}")
        set(${PACKAGE_NAME_UPPER}_TARGET "${ARG_TARGET_NAME}" PARENT_SCOPE)
    else()
        message(FATAL_ERROR "${ARG_PACKAGE_NAME} not found and source directory doesn't exist at ${DEP_SOURCE_DIR}")
    endif()
endfunction()