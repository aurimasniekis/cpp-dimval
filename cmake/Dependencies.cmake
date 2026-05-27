include_guard(GLOBAL)
include(FetchContent)

if(DIMVAL_WITH_NLOHMANN_JSON)
    set(JSON_BuildTests OFF CACHE INTERNAL "")
    set(JSON_Install    OFF CACHE INTERNAL "")
    FetchContent_Declare(
        nlohmann_json
        URL      https://github.com/nlohmann/json/archive/refs/tags/v3.12.0.tar.gz
        URL_HASH SHA256=4b92eb0c06d10683f7447ce9406cb97cd4b453be18d7279320f7b2f025c10187
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        FIND_PACKAGE_ARGS 3.12.0
    )
    FetchContent_MakeAvailable(nlohmann_json)
endif()

# commons is a hard dependency of dimval's core descriptor types (comms::Icon /
# comms::Color), independent of the optional parcel integration. Declaring it
# here, before the parcel block, also makes parcel's own internal
# FetchContent_Declare(commons) a no-op — avoiding a double fetch.
FetchContent_Declare(
    commons
    GIT_REPOSITORY https://github.com/aurimasniekis/cpp-commons.git
    GIT_TAG        v0.1.3
    FIND_PACKAGE_ARGS 0.1.3
)
FetchContent_MakeAvailable(commons)

if(DIMVAL_WITH_PARCEL)
    set(PARCEL_BUILD_TESTS    OFF CACHE INTERNAL "")
    set(PARCEL_BUILD_EXAMPLES OFF CACHE INTERNAL "")
    FetchContent_Declare(
        parcel
        GIT_REPOSITORY https://github.com/aurimasniekis/cpp-parcel.git
        GIT_TAG        v0.2.0
        FIND_PACKAGE_ARGS 0.2.0
    )
    FetchContent_MakeAvailable(parcel)
endif()

if(DIMVAL_BUILD_TESTS)
    set(INSTALL_GTEST OFF CACHE INTERNAL "")
    set(BUILD_GMOCK   OFF CACHE INTERNAL "")
    FetchContent_Declare(
        googletest
        URL      https://github.com/google/googletest/archive/refs/tags/v1.17.0.tar.gz
        URL_HASH SHA256=65fab701d9829d38cb77c14acdc431d2108bfdbf8979e40eb8ae567edf10b27c
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        FIND_PACKAGE_ARGS NAMES GTest
    )
    FetchContent_MakeAvailable(googletest)
endif()
