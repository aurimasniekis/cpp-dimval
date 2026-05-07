include(GoogleTest)

set(_dimval_test_sources
    test_unit_value.cpp
    test_measure_value.cpp
    test_range.cpp
    test_arithmetic.cpp
    test_compatibility.cpp
    test_format.cpp
    test_ostream.cpp
    test_hash.cpp
    test_parse.cpp
    test_registry.cpp
    test_custom_unit.cpp
    test_custom_measure.cpp
    test_traits.cpp
)

if(DIMVAL_WITH_NLOHMANN_JSON AND TARGET nlohmann_json::nlohmann_json)
    list(APPEND _dimval_test_sources test_json.cpp)
endif()

if(DIMVAL_WITH_PARCEL AND TARGET parcel::parcel)
    list(APPEND _dimval_test_sources test_parcel.cpp)
endif()

add_executable(dimval_tests ${_dimval_test_sources})

target_link_libraries(dimval_tests
    PRIVATE
        dimval::dimval
        GTest::gtest_main
)

dimval_set_warnings(dimval_tests PRIVATE)
dimval_enable_sanitizers(dimval_tests)
dimval_enable_coverage(dimval_tests)

gtest_discover_tests(dimval_tests)
