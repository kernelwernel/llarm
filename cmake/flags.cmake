# set standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# from https://github.com/cpp-best-practices/cmake_template/blob/main/cmake/CompilerWarnings.cmake
set(MSVC_CXX_FLAGS
    /W4 # Baseline reasonable warnings
    /w14242 # 'identifier': conversion from 'type1' to 'type2', possible loss of data
    /w14254 # 'operator': conversion from 'type1:field_bits' to 'type2:field_bits', possible loss of data
    /w14263 # 'function': member function does not override any base class virtual member function
    /w14265 # 'classname': class has virtual functions, but destructor is not virtual instances of this class may not
            # be destructed correctly
    /w14287 # 'operator': unsigned/negative constant mismatch
    /we4289 # nonstandard extension used: 'variable': loop control variable declared in the for-loop is used outside
            # the for-loop scope
    /w14296 # 'operator': expression is always 'boolean_value'
    /w14311 # 'variable': pointer truncation from 'type1' to 'type2'
    /w14545 # expression before comma evaluates to a function which is missing an argument list
    /w14546 # function call before comma missing argument list
    /w14547 # 'operator': operator before comma has no effect; expected operator with side-effect
    /w14549 # 'operator': operator before comma has no effect; did you intend 'operator'?
    /w14555 # expression has no effect; expected expression with side- effect
    /w14619 # pragma warning: there is no warning number 'number'
    /w14640 # Enable warning on thread un-safe static member initialization
    /w14826 # Conversion from 'type1' to 'type2' is sign-extended. This may cause unexpected runtime behavior.
    /w14905 # wide string literal cast to 'LPSTR'
    /w14906 # string literal cast to 'LPWSTR'
    /w14928 # illegal copy-initialization; more than one user-defined conversion has been implicitly applied
    /permissive- # standards conformance mode for MSVC compiler.
)


set(CLANG_CXX_FLAGS
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Wcast-align
    -Woverloaded-virtual
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wnull-dereference
    -Wdouble-promotion
    -Wformat=2
    -Wimplicit-fallthrough
)


set(LINUX_EXTRA_CXX_FLAGS
    -fcolor-diagnostics
    -fvisibility=hidden
)


set(GCC_CXX_FLAGS
    ${CLANG_CXX_FLAGS}
    -Wmisleading-indentation
    -Wduplicated-cond
    -Wduplicated-branches
    -Wlogical-op
    -Wuseless-cast
    -Wsuggest-override
    -Wnrvo
)


set(LINUX_RELEASE_CXX_FLAGS
    -O2
    # -flto for some reason this really fucks up in a few cases
    -g0
    -march=native
    -mtune=native
    # -fno-omit-frame-pointer for llvm-bolt
    -Wall
    -Werror
    -Wextra
    -Wshadow
    -Wunused
)


set(LINUX_EMBEDDED_CXX_FLAGS
    -ffunction-sections
    -fdata-sections
    -mcpu=native
)


set(LINUX_DEBUG_CXX_FLAGS
    -g
    -O0
    #-fsanitize=address,undefined,nullability
    -Wno-return-type # for prototyping purposes
)


set(MSVC_DEBUG_CXX_FLAGS
    /Od
    /Zi
    /RTC1
)


set(LINUX_COMMON_LINKER_FLAGS
    -lstdc++
    -lm
)


set(BOLT_LINKER_FLAGS
    --emit-relocs
    -fno-reorder-blocks-and-partition # specifically for GCC8 
)