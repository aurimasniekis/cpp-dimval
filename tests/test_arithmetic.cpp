#include <dimval/dimval.hpp>
#include <dimval/math.hpp>

#include <gtest/gtest.h>

namespace dv = dimval;

TEST(Arithmetic, AddSubSameUnit) {
    const auto a = dv::unit_value<dv::Meter>(1.0);
    const auto b = dv::unit_value<dv::Meter>(2.5);
    EXPECT_EQ((a + b).v, 3.5);
    EXPECT_EQ((b - a).v, 1.5);
}

TEST(Arithmetic, MulDivScalar) {
    const auto a = dv::unit_value<dv::Meter>(2.0);
    EXPECT_EQ((a * 3.0).v, 6.0);
    EXPECT_EQ((3.0 * a).v, 6.0);
    EXPECT_EQ((a / 2.0).v, 1.0);
}

TEST(Arithmetic, DivSameUnitYieldsScalar) {
    const auto a = dv::unit_value<dv::Meter>(10.0);
    const auto b = dv::unit_value<dv::Meter>(2.0);
    auto r = a / b;
    static_assert(std::is_same_v<decltype(r), double>);
    EXPECT_EQ(r, 5.0);
}

TEST(Arithmetic, UnaryNegation) {
    const auto a = dv::unit_value<dv::Meter>(2.0);
    EXPECT_EQ((-a).v, -2.0);
    EXPECT_EQ((+a).v, 2.0);
}

TEST(Arithmetic, CompoundAssignment) {
    auto a = dv::unit_value<dv::Meter>(2.0);
    a += dv::unit_value<dv::Meter>(1.0);
    EXPECT_EQ(a.v, 3.0);
    a -= dv::unit_value<dv::Meter>(0.5);
    EXPECT_EQ(a.v, 2.5);
    a *= 2.0;
    EXPECT_EQ(a.v, 5.0);
    a /= 5.0;
    EXPECT_EQ(a.v, 1.0);
}

TEST(Arithmetic, IntValueType) {
    const dv::UnitValue<dv::Count, int> a = 3;
    const dv::UnitValue<dv::Count, int> b = 4;
    EXPECT_EQ((a + b).v, 7);
    EXPECT_EQ((b - a).v, 1);
}

// --- math.hpp helpers ---

TEST(Math, AbsUnit) {
    EXPECT_EQ(dv::abs(dv::unit_value<dv::Meter>(-3.0)).v, 3.0);
    EXPECT_EQ(dv::abs(dv::unit_value<dv::Meter>(2.0)).v, 2.0);
}

TEST(Math, MinMaxUnit) {
    const auto a = dv::unit_value<dv::Meter>(2.0);
    const auto b = dv::unit_value<dv::Meter>(5.0);
    EXPECT_EQ(dv::min(a, b).v, 2.0);
    EXPECT_EQ(dv::max(a, b).v, 5.0);
}

TEST(Math, ClampUnit) {
    const auto lo = dv::unit_value<dv::Meter>(0.0);
    const auto hi = dv::unit_value<dv::Meter>(10.0);
    EXPECT_EQ(dv::clamp(dv::unit_value<dv::Meter>(-1.0), lo, hi).v, 0.0);
    EXPECT_EQ(dv::clamp(dv::unit_value<dv::Meter>(5.0), lo, hi).v, 5.0);
    EXPECT_EQ(dv::clamp(dv::unit_value<dv::Meter>(11.0), lo, hi).v, 10.0);
}

TEST(Math, AbsMinMaxClampMeasure) {
    const auto a = dv::measure_value<dv::Distance>(-3.0);
    EXPECT_EQ(dv::abs(a).v, 3.0);

    const auto b = dv::measure_value<dv::Distance>(7.0);
    EXPECT_EQ(dv::min(dv::abs(a), b).v, 3.0);
    EXPECT_EQ(dv::max(dv::abs(a), b).v, 7.0);

    EXPECT_EQ(dv::clamp(dv::measure_value<dv::Distance>(100.0),
                        dv::measure_value<dv::Distance>(0.0),
                        dv::measure_value<dv::Distance>(50.0))
                  .v,
              50.0);
}

TEST(Math, MidpointUnitRange) {
    const auto r = dv::UnitRangeValue<dv::Meter>::closed(dv::unit_value<dv::Meter>(2.0),
                                                         dv::unit_value<dv::Meter>(8.0));
    EXPECT_EQ(dv::midpoint(r).v, 5.0);
}

TEST(Math, MidpointMeasureRange) {
    const auto r = dv::MeasureRangeValue<dv::Distance>::closed(
        dv::measure_value<dv::Distance>(0.0), dv::measure_value<dv::Distance>(100.0));
    EXPECT_EQ(dv::midpoint(r).v, 50.0);
}
