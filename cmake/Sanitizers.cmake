include_guard(GLOBAL)

# dimval_enable_sanitizers(<target>)
#
# Adds AddressSanitizer + UndefinedBehaviorSanitizer flags to <target> when
# DIMVAL_ENABLE_SANITIZERS is ON and the toolchain is GCC or Clang.
function(dimval_enable_sanitizers target)
    if(NOT DIMVAL_ENABLE_SANITIZERS)
        return()
    endif()

    if(MSVC)
        message(STATUS "dimval: sanitizers requested but skipped on MSVC")
        return()
    endif()

    set(_san_flags
        -fsanitize=address
        -fsanitize=undefined
        -fno-omit-frame-pointer
        -fno-sanitize-recover=all
    )

    target_compile_options(${target} PRIVATE ${_san_flags})
    target_link_options   (${target} PRIVATE ${_san_flags})
endfunction()
