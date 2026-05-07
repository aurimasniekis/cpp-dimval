#include <dimval/dimval.hpp>

#include <gtest/gtest.h>

namespace dv = dimval;

// Static checks that enforce compile-time type safety. If any of these fail to
// compile we lose the property; if any of the negative checks accidentally
// hold we've leaked silent coercion.

static_assert(dv::units_compatible<dv::Meter, dv::Meter>());
static_assert(dv::units_compatible<dv::Second, dv::Hour>());
static_assert(dv::units_compatible<dv::Celsius, dv::Kelvin>());
static_assert(dv::units_compatible<dv::Bit, dv::Byte>());
static_assert(dv::units_compatible<dv::Decibel, dv::Decibel>());

static_assert(!dv::units_compatible<dv::Meter, dv::Kilogram>());
static_assert(!dv::units_compatible<dv::Second, dv::Hertz>());
static_assert(!dv::units_compatible<dv::Decibel, dv::DecibelMilliwatt>());

static_assert(dv::measure_uses_unit<dv::Distance, dv::Meter>());
static_assert(dv::measure_uses_unit<dv::Frequency, dv::Hertz>());
static_assert(!dv::measure_uses_unit<dv::Distance, dv::Second>());

// MeasureBase derives base_unit_id directly from the BaseUnit type — no
// duplicated string at the macro call site can drift from the unit's id.
static_assert(dv::Length::base_unit_id == "m");
static_assert(dv::Length::descriptor().base_unit_id == "m");
static_assert(dv::Snr::base_unit_id == "dB");

TEST(Compatibility, RuntimeCompatibleViaRegistry) {
    const auto& reg = dv::UnitRegistry::global();
    EXPECT_TRUE(reg.compatible("s", "h"));
    EXPECT_TRUE(reg.compatible("K", "degC"));
    EXPECT_FALSE(reg.compatible("m", "kg"));
    EXPECT_FALSE(reg.compatible("m", "no_such_unit"));
}

TEST(Compatibility, MeasureUsesDeclaredBaseUnit) {
    const auto& mreg = dv::MeasureRegistry::global();
    EXPECT_TRUE(mreg.compatible("distance", "m"));
    EXPECT_FALSE(mreg.compatible("distance", "kg"));
}
