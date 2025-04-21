# set standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# universal flags
set(COMMON_CXX_FLAGS
    -w
    -Wall
    -Wextra
    -Werror
    -Wshadow
    -Wconversions
    -Wunused
    -Wpedantic
    -Wpedantic-errors
    -Wconversion
    -Wsign-conversion
    -Wnull-dereference
    -Wdouble-promotion
    -Wduplicated-cond
    -Wduplicated-branches
    -Wlogical-op
    -Wuseless-cast
    -Wlifetime
    -Weverything
)


# release flags
set(RELEASE_CXX_FLAGS
    -O2
    # -flto for some reason this really fucks up in a few cases
    -g0
    -march=native
    -mtune=native
    # -fno-omit-frame-pointer for llvm-bolt
)


# extra flags for embedded systems
set(EMBEDDED_CXX_FLAGS
    -ffunction-sections
    -fdata-sections
    -mcpu=native
)


# debug flags
set(DEBUG_CXX_FLAGS
    -g
    -O0
    -fsanitize=address,undefined,nullability
)


# linker flags
set(COMMON_LINKER_FLAGS
    -lstdc++
    -lm
)