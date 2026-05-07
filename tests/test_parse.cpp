#include <dimval/dimval.hpp>

#include <gtest/gtest.h>

namespace dv = dimval;

TEST(Parse, BasicUnit) {
    const auto r = dv::parse_unit_value<dv::Meter>("42.5 m");
    ASSERT_TRUE(r.has_value());
    EXPECT_EQ(r->v, 42.5);
}

TEST(Parse, NoSpace) {
    const auto r = dv::parse_unit_value<dv::Meter>("42.5m");
    ASSERT_TRUE(r.has_value());
    EXPECT_EQ(r->v, 42.5);
}

TEST(Parse, NegativeAndExponent) {
    const auto r = dv::parse_unit_value<dv::Meter>("-1.5e3 m");
    ASSERT_TRUE(r.has_value());
    EXPECT_DOUBLE_EQ(r->v, -1500.0);
}

TEST(Parse, EmptyInput) {
    auto r = dv::parse_unit_value<dv::Meter>("   ");
    ASSERT_FALSE(r.has_value());
    EXPECT_EQ(r.error().code, dv::ParseErrorCode::Empty);
}

TEST(Parse, InvalidNumber) {
    auto r = dv::parse_unit_value<dv::Meter>("abc m");
    ASSERT_FALSE(r.has_value());
    EXPECT_EQ(r.error().code, dv::ParseErrorCode::InvalidNumber);
}

TEST(Parse, UnitMismatch) {
    auto r = dv::parse_unit_value<dv::Meter>("1.5 kg");
    ASSERT_FALSE(r.has_value());
    EXPECT_EQ(r.error().code, dv::ParseErrorCode::UnitMismatch);
}

TEST(Parse, MeasureValue) {
    const auto r = dv::parse_measure_value<dv::Distance>("100 m");
    ASSERT_TRUE(r.has_value());
    EXPECT_EQ(r->v, 100.0);
}

TEST(Parse, DynamicByRegistry) {
    const auto r = dv::parse_dynamic_unit_value("3.14 h");
    ASSERT_TRUE(r.has_value());
    ASSERT_NE(r->desc, nullptr);
    EXPECT_EQ(r->desc->id, "h");
    EXPECT_EQ(r->value, 3.14);
}

TEST(Parse, DynamicUnknown) {
    auto r = dv::parse_dynamic_unit_value("3.14 xyz");
    ASSERT_FALSE(r.has_value());
    EXPECT_EQ(r.error().code, dv::ParseErrorCode::UnknownUnit);
}

TEST(Parse, UnitValueStatic) {
    const auto r = dv::MeterValue::parse("42.5 m");
    ASSERT_TRUE(r.has_value());
    EXPECT_EQ(r->v, 42.5);
}

TEST(Parse, UnitValueStaticMismatch) {
    auto r = dv::MeterValue::parse("1.5 kg");
    ASSERT_FALSE(r.has_value());
    EXPECT_EQ(r.error().code, dv::ParseErrorCode::UnitMismatch);
}

TEST(Parse, UnitValueStaticIntT) {
    const auto r = dv::UnitValue<dv::Meter, int>::parse("42 m");
    ASSERT_TRUE(r.has_value());
    EXPECT_EQ(r->v, 42);
}

TEST(Parse, MeasureValueStatic) {
    const auto r = dv::DistanceValue::parse("100 m");
    ASSERT_TRUE(r.has_value());
    EXPECT_EQ(r->v, 100.0);
}

TEST(Parse, UnitValueTrailingGarbage) {
    // The trailing tail must match an id/symbol/short_name; "42 m foo" has
    // both "m" and "foo" in the tail and is not a valid unit symbol.
    auto r = dv::parse_unit_value<dv::Meter>("42 m foo");
    ASSERT_FALSE(r.has_value());
    EXPECT_EQ(r.error().code, dv::ParseErrorCode::UnitMismatch);
}

TEST(Parse, MeasureValueMismatch) {
    auto r = dv::parse_measure_value<dv::Distance>("100 Hz");
    ASSERT_FALSE(r.has_value());
    EXPECT_EQ(r.error().code, dv::ParseErrorCode::UnitMismatch);
}

TEST(Parse, DynamicUnitValueDimensionless) {
    // Bare number with no symbol falls back to "dimensionless".
    const auto r = dv::parse_dynamic_unit_value("3.14");
    ASSERT_TRUE(r.has_value());
    ASSERT_NE(r->desc, nullptr);
    EXPECT_EQ(r->desc->id, "dimensionless");
    EXPECT_EQ(r->value, 3.14);
}

TEST(Parse, NegativeValue) {
    const auto r = dv::parse_unit_value<dv::Meter>("-42.5 m");
    ASSERT_TRUE(r.has_value());
    EXPECT_EQ(r->v, -42.5);
}

TEST(Parse, IntegerValueTypeRejectsFloat) {
    // <int> + "42.5 m" — std::from_chars stops at '.' and reports trailing
    // bytes, so this rejects rather than truncates.
    auto r = dv::UnitValue<dv::Meter, int>::parse("42.5 m");
    ASSERT_FALSE(r.has_value());
    EXPECT_EQ(r.error().code, dv::ParseErrorCode::InvalidNumber);
}

TEST(Parse, LeadingTrailingWhitespace) {
    // Pin behavior: leading/trailing whitespace is trimmed.
    const auto r = dv::parse_unit_value<dv::Meter>("   42.5 m   ");
    ASSERT_TRUE(r.has_value());
    EXPECT_EQ(r->v, 42.5);
}
