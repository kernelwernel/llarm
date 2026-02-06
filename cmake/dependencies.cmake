# Function to find a package or build it from source
# Usage: find_or_build_dependency(
#   PACKAGE_NAME <name>
#   SOURCE_DIR <relative_path>
#   TARGET_NAME <target>
#   [ALIAS_TARGET <namespaced_target>]
# )
function(add_dependency)
    set(options "")
    set(oneValueArgs PACKAGE_NAME SOURCE_DIR TARGET_NAME ALIAS_TARGET)
    set(multiValueArgs "")
    
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    
    # Validate required arguments
    if(NOT ARG_PACKAGE_NAME)
        message(FATAL_ERROR "PACKAGE_NAME is required")
    endif()
    if(NOT ARG_SOURCE_DIR)
        message(FATAL_ERROR "SOURCE_DIR is required")
    endif()
    if(NOT ARG_TARGET_NAME)
        message(FATAL_ERROR "TARGET_NAME is required")
    endif()
    
    # Default alias target to namespaced version if not provided
    if(NOT ARG_ALIAS_TARGET)
        set(ARG_ALIAS_TARGET "llarm::${ARG_TARGET_NAME}")
    endif()
    
    # Convert package name to uppercase for the output variable
    string(TOUPPER "${ARG_PACKAGE_NAME}" PACKAGE_NAME_UPPER)
    string(REPLACE "-" "_" PACKAGE_NAME_UPPER "${PACKAGE_NAME_UPPER}")
    
    # Try to find the package
    find_package(${ARG_PACKAGE_NAME} CONFIG QUIET)
    
    if(NOT ${ARG_PACKAGE_NAME}_FOUND)
        message(STATUS "${ARG_PACKAGE_NAME} not found, building from source...")
        
        set(DEP_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${ARG_SOURCE_DIR}")
        
        if(EXISTS "${DEP_SOURCE_DIR}/CMakeLists.txt")
            add_subdirectory("${DEP_SOURCE_DIR}" "${CMAKE_BINARY_DIR}/${ARG_PACKAGE_NAME}")
            # When built from source, use the direct target name
            set(${PACKAGE_NAME_UPPER}_TARGET "${ARG_TARGET_NAME}" PARENT_SCOPE)
        else()
            message(FATAL_ERROR "${ARG_PACKAGE_NAME} not found and source directory doesn't exist at ${DEP_SOURCE_DIR}")
        endif()
    else()
        message(STATUS "Found ${ARG_PACKAGE_NAME}: ${${ARG_PACKAGE_NAME}_DIR}")
        # When found via find_package, use the namespaced alias
        set(${PACKAGE_NAME_UPPER}_TARGET "${ARG_ALIAS_TARGET}" PARENT_SCOPE)
    endif()
endfunction()