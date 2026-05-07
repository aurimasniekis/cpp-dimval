#include <dimval/dimval.hpp>

#include <gtest/gtest.h>

#include <format>
#include <string>

namespace dv = dimval;

TEST(Format, DefaultUnit) {
    auto v = dv::unit_value<dv::Meter>(42.5);
    EXPECT_EQ(std::format("{}", v), "42.5 m");
}

TEST(Format, ShortStyleNoSpace) {
    auto v = dv::unit_value<dv::Meter>(42.5);
    EXPECT_EQ(std::format("{:short}", v), "42.5m");
}

TEST(Format, FullStyleLongName) {
    auto v = dv::unit_value<dv::Meter>(42.5);
    EXPECT_EQ(std::format("{:full}", v), "42.5 meter");
}

TEST(Format, JsonStyle) {
    auto v = dv::unit_value<dv::Meter>(42.5);
    EXPECT_EQ(std::format("{:json}", v), R"({"unit":"m","value":42.5})");
}

TEST(Format, Precision) {
    auto v = dv::unit_value<dv::Meter>(3.14159);
    EXPECT_EQ(std::format("{:.2}", v), "3.14 m");
    EXPECT_EQ(std::format("{:full.3}", v), "3.142 meter");
}

TEST(Format, CountNoSpace) {
    auto v = dv::unit_value<dv::Count>(7.0);
    // Count has no symbol and no_space_before_symbol=true.
    EXPECT_EQ(std::format("{}", v), "7");
}

TEST(Format, MeasureDefault) {
    auto m = dv::measure_value<dv::Distance>(1.0);
    EXPECT_EQ(std::format("{}", m), "1 m");
}

TEST(Format, MeasureFull) {
    auto m = dv::measure_value<dv::Distance>(1.0);
    EXPECT_EQ(std::format("{:full}", m), "1 Distance (meter)");
}

TEST(Format, MeasureJson) {
    auto m = dv::measure_value<dv::Distance>(1.0);
    EXPECT_EQ(std::format("{:json}", m), R"({"measure":"distance","unit":"m","value":1})");
}

TEST(Format, RangeClosedDefault) {
    auto r = dv::UnitRangeValue<dv::Meter>::closed(dv::unit_value<dv::Meter>(0.0),
                                                   dv::unit_value<dv::Meter>(10.0));
    EXPECT_EQ(std::format("{}", r), "[0 m, 10 m]");
}

TEST(Format, RangeOpenAndMixed) {
    auto r = dv::UnitRangeValue<dv::Meter>::left_open(dv::unit_value<dv::Meter>(0.0),
                                                      dv::unit_value<dv::Meter>(10.0));
    EXPECT_EQ(std::format("{}", r), "(0 m, 10 m]");
}

TEST(Format, RangeJson) {
    auto r = dv::UnitRangeValue<dv::Meter>::closed(dv::unit_value<dv::Meter>(0.0),
                                                   dv::unit_value<dv::Meter>(10.0));
    const auto out = std::format("{:json}", r);
    EXPECT_NE(out.find(R"("unit":"m")"), std::string::npos);
    EXPECT_NE(out.find(R"("min_inclusive":true)"), std::string::npos);
    EXPECT_NE(out.find(R"("max_inclusive":true)"), std::string::npos);
}

// --- coverage-gap fillers ---

TEST(Format, MeasureValueShortStyle) {
    auto m = dv::measure_value<dv::Distance>(42.5);
    EXPECT_EQ(std::format("{:short}", m), "42.5m");
}

TEST(Format, UnitValueSymbolEmptyDefault) {
    // Count has empty symbol; default style renders bare number.
    auto v = dv::unit_value<dv::Count>(42.0);
    EXPECT_EQ(std::format("{}", v), "42");
}

TEST(Format, RangeShortStyle) {
    auto r = dv::UnitRangeValue<dv::Meter>::closed(dv::unit_value<dv::Meter>(0.0),
                                                   dv::unit_value<dv::Meter>(5.0));
    EXPECT_EQ(std::format("{:short}", r), "[0m, 5m]");
}

TEST(Format, RangeFullStyle) {
    auto r = dv::UnitRangeValue<dv::Meter>::closed(dv::unit_value<dv::Meter>(0.0),
                                                   dv::unit_value<dv::Meter>(5.0));
    EXPECT_EQ(std::format("{:full}", r), "[0 meter, 5 meter]");
}

TEST(Format, MeasureRangeJson) {
    auto r = dv::MeasureRangeValue<dv::Distance>::closed(dv::measure_value<dv::Distance>(0.0),
                                                         dv::measure_value<dv::Distance>(10.0));
    const auto out = std::format("{:json}", r);
    EXPECT_NE(out.find(R"("measure":"distance")"), std::string::npos);
    EXPECT_NE(out.find(R"("unit":"m")"), std::string::npos);
}

TEST(Format, InvalidSpecThrows) {
    auto v = dv::unit_value<dv::Meter>(1.0);
    // bogus extra spec → format_error after style/precision parse leaves
    // a non-'}' char behind.
    EXPECT_THROW((void)std::vformat("{:full.x}", std::make_format_args(v)), std::format_error);
}

TEST(Format, PrecisionZero) {
    auto v = dv::unit_value<dv::Meter>(3.6);
    EXPECT_EQ(std::format("{:.0}", v), "4 m");
}

TEST(Format, RangeToStringMatchesFormat) {
    auto r = dv::UnitRangeValue<dv::Meter>::closed(dv::unit_value<dv::Meter>(0.0),
                                                   dv::unit_value<dv::Meter>(10.0));
    EXPECT_EQ(r.to_string(), "[0 m, 10 m]");
    EXPECT_EQ(r.to_formatted_string(), std::format("{}", r));
}

TEST(Format, MeasureRangeToString) {
    auto r = dv::MeasureRangeValue<dv::Distance>::left_open(dv::measure_value<dv::Distance>(0.0),
                                                            dv::measure_value<dv::Distance>(5.0));
    EXPECT_EQ(r.to_string(), "(0 m, 5 m]");
    EXPECT_EQ(r.to_formatted_string(), std::format("{}", r));
}
