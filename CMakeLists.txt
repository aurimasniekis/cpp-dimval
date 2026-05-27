cmake_minimum_required(VERSION 3.25)

project(dimval
    VERSION     0.2.0
    DESCRIPTION "Modern C++23 header-only library of dimensional values (units, measures, ranges)"
    LANGUAGES   CXX
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD          23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        Debug Release RelWithDebInfo MinSizeRel)
endif()

option(DIMVAL_BUILD_TESTS         "Build dimval tests"                  ${PROJECT_IS_TOP_LEVEL})
option(DIMVAL_BUILD_EXAMPLES      "Build dimval examples"               ${PROJECT_IS_TOP_LEVEL})
option(DIMVAL_BUILD_DOCS          "Build Doxygen API documentation"     OFF)
option(DIMVAL_ENABLE_CLANG_TIDY   "Run clang-tidy during build"         OFF)
option(DIMVAL_ENABLE_SANITIZERS   "Build with ASan + UBSan (Debug)"     OFF)
option(DIMVAL_ENABLE_COVERAGE     "Build with Clang source-based coverage" OFF)
option(DIMVAL_WARNINGS_AS_ERRORS  "Treat compiler warnings as errors"   ${PROJECT_IS_TOP_LEVEL})
option(DIMVAL_INSTALL             "Generate install rules for dimval"   ${PROJECT_IS_TOP_LEVEL})
option(DIMVAL_WITH_NLOHMANN_JSON  "Enable optional nlohmann/json integration" ON)
option(DIMVAL_WITH_PARCEL         "Enable optional cpp-parcel integration" ON)

if(DIMVAL_WITH_PARCEL AND NOT DIMVAL_WITH_NLOHMANN_JSON)
    message(STATUS
        "dimval: DIMVAL_WITH_PARCEL forced OFF because cpp-parcel depends on "
        "nlohmann_json, which is disabled (DIMVAL_WITH_NLOHMANN_JSON=OFF)."
    )
    set(DIMVAL_WITH_PARCEL OFF CACHE BOOL "Enable optional cpp-parcel integration" FORCE)
endif()

include(CompilerWarnings)
include(Sanitizers)
include(Coverage)
include(Dependencies)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/include/dimval/version.hpp.in"
    "${CMAKE_CURRENT_BINARY_DIR}/include/dimval/version.hpp"
    @ONLY
)

add_library(dimval INTERFACE)
add_library(dimval::dimval ALIAS dimval)

target_include_directories(dimval
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(dimval INTERFACE cxx_std_23)

# commons is required unconditionally — dimval's core descriptor types use
# comms::Icon / comms::Color regardless of the optional integrations.
target_link_libraries(dimval INTERFACE commons::commons)

if(DIMVAL_WITH_NLOHMANN_JSON AND TARGET nlohmann_json::nlohmann_json)
    target_link_libraries(dimval INTERFACE nlohmann_json::nlohmann_json)
    target_compile_definitions(dimval INTERFACE DIMVAL_WITH_NLOHMANN_JSON=1)
endif()

if(DIMVAL_WITH_PARCEL AND TARGET parcel::parcel)
    target_link_libraries(dimval INTERFACE parcel::parcel)
    target_compile_definitions(dimval INTERFACE DIMVAL_WITH_PARCEL=1)
endif()

if(DIMVAL_ENABLE_CLANG_TIDY)
    find_program(DIMVAL_CLANG_TIDY_EXE NAMES clang-tidy REQUIRED)
    set(_dimval_tidy_cmd
        "${DIMVAL_CLANG_TIDY_EXE}"
        "--config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy"
    )
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        execute_process(
            COMMAND "${CMAKE_CXX_COMPILER}" -print-search-dirs
            OUTPUT_VARIABLE _dimval_gcc_search_dirs
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        if(_dimval_gcc_search_dirs MATCHES "install: ([^\n]+)")
            list(APPEND _dimval_tidy_cmd
                "--extra-arg-before=--gcc-install-dir=${CMAKE_MATCH_1}")
            message(STATUS
                "dimval: pinning clang-tidy to gcc install dir ${CMAKE_MATCH_1}")
        endif()
    endif()
    set(CMAKE_CXX_CLANG_TIDY "${_dimval_tidy_cmd}")
    message(STATUS "dimval: clang-tidy enabled (${DIMVAL_CLANG_TIDY_EXE})")
endif()

if(DIMVAL_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(DIMVAL_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(DIMVAL_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    set(DIMVAL_DOXYGEN_OUTPUT_DIR "${CMAKE_BINARY_DIR}/docs")
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in"
        "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
        @ONLY
    )
    add_custom_target(dimval_docs
        COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Generating Doxygen documentation"
        VERBATIM
    )
endif()

if(DIMVAL_INSTALL AND (DEFINED commons_SOURCE_DIR OR DEFINED nlohmann_json_SOURCE_DIR OR DEFINED parcel_SOURCE_DIR))
    message(STATUS
        "dimval: DIMVAL_INSTALL disabled — a fetched dependency (commons, nlohmann_json or parcel) "
        "cannot be re-exported. Install it via system package or find_package, or disable "
        "DIMVAL_WITH_NLOHMANN_JSON / DIMVAL_WITH_PARCEL, to re-enable install rules."
    )
    set(DIMVAL_INSTALL OFF)
endif()

if(DIMVAL_INSTALL)
    include(GNUInstallDirs)
    include(CMakePackageConfigHelpers)

    install(TARGETS dimval
        EXPORT  dimvalTargets
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    install(DIRECTORY include/dimval
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.hpp"
    )

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/include/dimval/version.hpp"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/dimval
    )

    install(EXPORT dimvalTargets
        FILE        dimvalTargets.cmake
        NAMESPACE   dimval::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/dimval
    )

    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/dimvalConfigVersion.cmake"
        VERSION       ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
        ARCH_INDEPENDENT
    )

    configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/dimvalConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/dimvalConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/dimval
    )

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/dimvalConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/dimvalConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/dimval
    )
endif()
