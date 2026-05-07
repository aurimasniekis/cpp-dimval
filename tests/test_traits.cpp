#include <dimval/dimval.hpp>

#include <gtest/gtest.h>

namespace dv = dimval;

// All trait queries are pure compile-time predicates — exercise them with
// static_assert to lock the API in.

static_assert(dv::UnitLike<dv::Meter>);
static_assert(dv::UnitLike<dv::Kilogram>);
static_assert(dv::UnitLike<dv::Foot>);
static_assert(!dv::UnitLike<int>);
static_assert(!dv::UnitLike<double>);
static_assert(!dv::UnitLike<dv::Distance>);

static_assert(dv::MeasureLike<dv::Distance>);
static_assert(dv::MeasureLike<dv::Frequency>);
static_assert(dv::MeasureLike<dv::Speed>);
static_assert(!dv::MeasureLike<dv::Meter>);
static_assert(!dv::MeasureLike<int>);

static_assert(dv::units_compatible<dv::Meter, dv::Meter>());
static_assert(dv::units_compatible<dv::Meter, dv::Foot>());
static_assert(dv::units_compatible<dv::Second, dv::Hour>());
static_assert(!dv::units_compatible<dv::Meter, dv::Kilogram>());
static_assert(!dv::units_compatible<dv::Hertz, dv::Watt>());

static_assert(dv::measure_uses_unit<dv::Distance, dv::Meter>());
static_assert(dv::measure_uses_unit<dv::Frequency, dv::Hertz>());
static_assert(!dv::measure_uses_unit<dv::Distance, dv::Kilogram>());

TEST(Traits, UnitDescriptorOfMatchesTagDescriptor) {
    constexpr auto d_meter = dv::unit_descriptor_of<dv::Meter>();
    EXPECT_EQ(d_meter.id, "m");
    EXPECT_EQ(d_meter.kind, "length");

    constexpr auto d_hz = dv::unit_descriptor_of<dv::Hertz>();
    EXPECT_EQ(d_hz.id, "Hz");
    EXPECT_EQ(d_hz.kind, "frequency");
}

TEST(Traits, MeasureDescriptorOfMatchesTagDescriptor) {
    constexpr auto d_distance = dv::measure_descriptor_of<dv::Distance>();
    EXPECT_EQ(d_distance.id, "distance");
    EXPECT_EQ(d_distance.base_unit_id, "m");

    constexpr auto d_speed = dv::measure_descriptor_of<dv::Speed>();
    EXPECT_EQ(d_speed.id, "speed");
}
