#include <dimval/dimval.hpp>

#include <gtest/gtest.h>

namespace dv = dimval;

using meter_range = dv::UnitRangeValue<dv::Meter>;

TEST(UnitRange, ClosedFactoryAndContains) {
    const auto r =
        meter_range::closed(dv::unit_value<dv::Meter>(0.0), dv::unit_value<dv::Meter>(10.0));
    EXPECT_TRUE(r.contains(dv::unit_value<dv::Meter>(5.0)));
    EXPECT_TRUE(r.contains(dv::unit_value<dv::Meter>(0.0)));
    EXPECT_TRUE(r.contains(dv::unit_value<dv::Meter>(10.0)));
    EXPECT_FALSE(r.contains(dv::unit_value<dv::Meter>(-0.1)));
    EXPECT_FALSE(r.contains(dv::unit_value<dv::Meter>(10.1)));
}

TEST(UnitRange, OpenContainsExcludesEndpoints) {
    const auto r =
        meter_range::open(dv::unit_value<dv::Meter>(0.0), dv::unit_value<dv::Meter>(10.0));
    EXPECT_FALSE(r.contains(dv::unit_value<dv::Meter>(0.0)));
    EXPECT_FALSE(r.contains(dv::unit_value<dv::Meter>(10.0)));
    EXPECT_TRUE(r.contains(dv::unit_value<dv::Meter>(5.0)));
}

TEST(UnitRange, LeftAndRightOpen) {
    const auto lo =
        meter_range::left_open(dv::unit_value<dv::Meter>(0.0), dv::unit_value<dv::Meter>(10.0));
    EXPECT_FALSE(lo.contains(dv::unit_value<dv::Meter>(0.0)));
    EXPECT_TRUE(lo.contains(dv::unit_value<dv::Meter>(10.0)));

    const auto ro =
        meter_range::right_open(dv::unit_value<dv::Meter>(0.0), dv::unit_value<dv::Meter>(10.0));
    EXPECT_TRUE(ro.contains(dv::unit_value<dv::Meter>(0.0)));
    EXPECT_FALSE(ro.contains(dv::unit_value<dv::Meter>(10.0)));
}

TEST(UnitRange, MakeRejectsInverted) {
    auto r = meter_range::make(dv::unit_value<dv::Meter>(10.0), dv::unit_value<dv::Meter>(0.0));
    ASSERT_FALSE(r.has_value());
    EXPECT_EQ(r.error().code, dv::RangeErrorCode::MaxLessThanMin);
}

TEST(UnitRange, MakeRejectsEmptyOpenSinglePoint) {
    auto r = meter_range::make(
        dv::unit_value<dv::Meter>(5.0), dv::unit_value<dv::Meter>(5.0), dv::RangeInclusion::open());
    ASSERT_FALSE(r.has_value());
    EXPECT_EQ(r.error().code, dv::RangeErrorCode::EmptyOpenRange);
}

TEST(UnitRange, ContainsRange) {
    const auto outer =
        meter_range::closed(dv::unit_value<dv::Meter>(0.0), dv::unit_value<dv::Meter>(10.0));
    const auto inner =
        meter_range::closed(dv::unit_value<dv::Meter>(2.0), dv::unit_value<dv::Meter>(8.0));
    EXPECT_TRUE(outer.contains(inner));
    EXPECT_FALSE(inner.contains(outer));
}

TEST(UnitRange, Overlaps) {
    const auto a =
        meter_range::closed(dv::unit_value<dv::Meter>(0.0), dv::unit_value<dv::Meter>(5.0));
    const auto b =
        meter_range::closed(dv::unit_value<dv::Meter>(3.0), dv::unit_value<dv::Meter>(8.0));
    const auto c =
        meter_range::closed(dv::unit_value<dv::Meter>(6.0), dv::unit_value<dv::Meter>(7.0));
    EXPECT_TRUE(a.overlaps(b));
    EXPECT_FALSE(a.overlaps(c));
}

TEST(UnitRange, OverlapTouchInclusiveVsExclusive) {
    const auto closed_left =
        meter_range::closed(dv::unit_value<dv::Meter>(0.0), dv::unit_value<dv::Meter>(5.0));
    const auto open_right =
        meter_range::open(dv::unit_value<dv::Meter>(5.0), dv::unit_value<dv::Meter>(10.0));
    EXPECT_FALSE(closed_left.overlaps(open_right));

    const auto closed_right =
        meter_range::closed(dv::unit_value<dv::Meter>(5.0), dv::unit_value<dv::Meter>(10.0));
    EXPECT_TRUE(closed_left.overlaps(closed_right));
}

TEST(UnitRange, Intersect) {
    const auto a =
        meter_range::closed(dv::unit_value<dv::Meter>(0.0), dv::unit_value<dv::Meter>(5.0));
    const auto b =
        meter_range::closed(dv::unit_value<dv::Meter>(3.0), dv::unit_value<dv::Meter>(8.0));
    const auto i = a.intersect(b);
    ASSERT_TRUE(i.has_value());
    EXPECT_EQ(i->min().v, 3.0);
    EXPECT_EQ(i->max().v, 5.0);
}

TEST(MeasureRange, Basics) {
    using mr = dv::MeasureRangeValue<dv::Distance>;
    const auto r =
        mr::closed(dv::measure_value<dv::Distance>(0.0), dv::measure_value<dv::Distance>(100.0));
    EXPECT_TRUE(r.contains(dv::measure_value<dv::Distance>(42.0)));
}

// --- coverage-gap fillers ---

TEST(UnitRange, MakeRejectsEqualBoundsLeftOpen) {
    auto r = meter_range::make(dv::unit_value<dv::Meter>(5.0),
                               dv::unit_value<dv::Meter>(5.0),
                               dv::RangeInclusion::left_open());
    ASSERT_FALSE(r.has_value());
    EXPECT_EQ(r.error().code, dv::RangeErrorCode::EmptyOpenRange);
}

TEST(UnitRange, MakeRejectsEqualBoundsRightOpen) {
    auto r = meter_range::make(dv::unit_value<dv::Meter>(5.0),
                               dv::unit_value<dv::Meter>(5.0),
                               dv::RangeInclusion::right_open());
    ASSERT_FALSE(r.has_value());
    EXPECT_EQ(r.error().code, dv::RangeErrorCode::EmptyOpenRange);
}

TEST(UnitRange, MakeAllowsEqualBoundsClosed) {
    const auto r =
        meter_range::make(dv::unit_value<dv::Meter>(5.0), dv::unit_value<dv::Meter>(5.0));
    ASSERT_TRUE(r.has_value());
    EXPECT_TRUE(r->contains(dv::unit_value<dv::Meter>(5.0)));
}

TEST(UnitRange, IntersectDisjointReturnsNullopt) {
    const auto a =
        meter_range::closed(dv::unit_value<dv::Meter>(0.0), dv::unit_value<dv::Meter>(2.0));
    const auto b =
        meter_range::closed(dv::unit_value<dv::Meter>(5.0), dv::unit_value<dv::Meter>(7.0));
    EXPECT_FALSE(a.intersect(b).has_value());
}

TEST(UnitRange, IntersectHalfOpenWithHalfOpen) {
    const auto a =
        meter_range::left_open(dv::unit_value<dv::Meter>(0.0), dv::unit_value<dv::Meter>(5.0));
    const auto b =
        meter_range::right_open(dv::unit_value<dv::Meter>(0.0), dv::unit_value<dv::Meter>(10.0));
    const auto i = a.intersect(b);
    ASSERT_TRUE(i.has_value());
    EXPECT_EQ(i->min().v, 0.0);
    EXPECT_EQ(i->max().v, 5.0);
    EXPECT_EQ(i->inclusion().lower, dv::Bound::Exclusive);
    EXPECT_EQ(i->inclusion().upper, dv::Bound::Inclusive);
}

TEST(UnitRange, OverlapsTouchingBothExclusive) {
    const auto a =
        meter_range::open(dv::unit_value<dv::Meter>(0.0), dv::unit_value<dv::Meter>(5.0));
    const auto b =
        meter_range::open(dv::unit_value<dv::Meter>(5.0), dv::unit_value<dv::Meter>(10.0));
    EXPECT_FALSE(a.overlaps(b));
}

TEST(UnitRange, EqualityDifferentInclusion) {
    const auto closed =
        meter_range::closed(dv::unit_value<dv::Meter>(0.0), dv::unit_value<dv::Meter>(10.0));
    const auto open =
        meter_range::open(dv::unit_value<dv::Meter>(0.0), dv::unit_value<dv::Meter>(10.0));
    EXPECT_NE(closed, open);
}

TEST(UnitRange, RightOpenFactory) {
    const auto r =
        meter_range::right_open(dv::unit_value<dv::Meter>(0.0), dv::unit_value<dv::Meter>(10.0));
    EXPECT_EQ(r.inclusion().lower, dv::Bound::Inclusive);
    EXPECT_EQ(r.inclusion().upper, dv::Bound::Exclusive);
}

TEST(UnitRange, ContainsScalarAtBoundExclusive) {
    const auto a =
        meter_range::left_open(dv::unit_value<dv::Meter>(0.0), dv::unit_value<dv::Meter>(10.0));
    EXPECT_FALSE(a.contains(dv::unit_value<dv::Meter>(0.0)));  // lower exclusive
    EXPECT_TRUE(a.contains(dv::unit_value<dv::Meter>(10.0)));  // upper inclusive

    const auto b =
        meter_range::right_open(dv::unit_value<dv::Meter>(0.0), dv::unit_value<dv::Meter>(10.0));
    EXPECT_TRUE(b.contains(dv::unit_value<dv::Meter>(0.0)));    // lower inclusive
    EXPECT_FALSE(b.contains(dv::unit_value<dv::Meter>(10.0)));  // upper exclusive
}

TEST(MeasureRange, MakeRejectsInverted) {
    auto r = dv::MeasureRangeValue<dv::Distance>::make(dv::measure_value<dv::Distance>(10.0),
                                                       dv::measure_value<dv::Distance>(0.0));
    ASSERT_FALSE(r.has_value());
    EXPECT_EQ(r.error().code, dv::RangeErrorCode::MaxLessThanMin);
}

TEST(MeasureRange, IntersectAndOverlap) {
    using mr = dv::MeasureRangeValue<dv::Distance>;
    const auto a =
        mr::closed(dv::measure_value<dv::Distance>(0.0), dv::measure_value<dv::Distance>(10.0));
    const auto b =
        mr::closed(dv::measure_value<dv::Distance>(5.0), dv::measure_value<dv::Distance>(15.0));
    EXPECT_TRUE(a.overlaps(b));
    const auto i = a.intersect(b);
    ASSERT_TRUE(i.has_value());
    EXPECT_EQ(i->min().v, 5.0);
    EXPECT_EQ(i->max().v, 10.0);
}

TEST(MeasureRange, ContainsRange) {
    using mr = dv::MeasureRangeValue<dv::Distance>;
    const auto outer =
        mr::closed(dv::measure_value<dv::Distance>(0.0), dv::measure_value<dv::Distance>(100.0));
    const auto inner =
        mr::closed(dv::measure_value<dv::Distance>(20.0), dv::measure_value<dv::Distance>(80.0));
    EXPECT_TRUE(outer.contains(inner));
    EXPECT_FALSE(inner.contains(outer));
}

TEST(MeasureRange, IntersectDisjointReturnsNullopt) {
    using mr = dv::MeasureRangeValue<dv::Distance>;
    const auto a =
        mr::closed(dv::measure_value<dv::Distance>(0.0), dv::measure_value<dv::Distance>(1.0));
    const auto b =
        mr::closed(dv::measure_value<dv::Distance>(5.0), dv::measure_value<dv::Distance>(6.0));
    EXPECT_FALSE(a.intersect(b).has_value());
}
