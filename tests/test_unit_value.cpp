#include <dimval/dimval.hpp>

#include <gtest/gtest.h>

namespace dv = dimval;

TEST(UnitValue, DefaultConstructsToZero) {
    const dv::UnitValue<dv::Meter> v;
    EXPECT_EQ(v.v, 0.0);
}

TEST(UnitValue, ExplicitConstruct) {
    const dv::UnitValue<dv::Meter> v = 1.5;
    EXPECT_EQ(v.v, 1.5);
}

TEST(UnitValue, FactoryHelper) {
    const auto v = dv::unit_value<dv::Meter>(2.5);
    EXPECT_EQ(v.v, 2.5);
    EXPECT_EQ(v.id(), "m");
    EXPECT_EQ(v.symbol(), "m");
    EXPECT_EQ(v.kind(), "length");
}

TEST(UnitValue, TypeAliasShorthand) {
    const dv::MeterValue v = 1.78;
    EXPECT_EQ(v.v, 1.78);
    EXPECT_EQ(v.id(), "m");

    dv::WattValue power = 42.0;
    EXPECT_EQ(power.kind(), "power");
}

TEST(UnitValue, IUnitValuePolymorphism) {
    const dv::IUnitValueUnique v = dv::MeterValue::unique(1.5);
    EXPECT_EQ(v->descriptor().id, "m");
    EXPECT_EQ(v->descriptor().symbol, "m");
    EXPECT_EQ(v->descriptor().kind, "length");
    EXPECT_EQ(v->descriptor().long_name, "meter");
    EXPECT_EQ(v->numeric_as_double(), 1.5);
    EXPECT_EQ(v->to_string(), "1.5 m");

    const auto cloned = v->clone();
    EXPECT_EQ(cloned->descriptor().id, "m");
    EXPECT_EQ(cloned->numeric_as_double(), 1.5);
}

TEST(UnitValue, ImplicitFromNumeric) {
    const dv::MeterValue v = 1.78;  // direct-list init via implicit ctor
    EXPECT_EQ(v.v, 1.78);

    const dv::WattValue power = 42.0;
    EXPECT_EQ(power.v, 42.0);
}

TEST(UnitValue, StaticFactoriesOfAndUnique) {
    // of() returns shared_ptr — the heap-owned, shareable form.
    const dv::MeterValueShared s = dv::MeterValue::of(1.5);
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(s->v, 1.5);
    EXPECT_EQ(s->id(), "m");
    auto s2 = s;
    EXPECT_EQ(s.use_count(), 2);

    const dv::MeterValueUnique p = dv::MeterValue::unique(2.5);
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(p->v, 2.5);
}

TEST(UnitValue, HeterogeneousContainer) {
    std::vector<dv::IUnitValueUnique> values;
    values.push_back(dv::MeterValue::unique(1.0));
    values.push_back(dv::KilogramValue::unique(80.0));
    values.push_back(dv::HertzValue::unique(2.4e9));

    EXPECT_EQ(values[0]->descriptor().kind, "length");
    EXPECT_EQ(values[1]->descriptor().kind, "mass");
    EXPECT_EQ(values[2]->descriptor().kind, "frequency");
}

TEST(UnitValue, ConvertSameKind) {
    // Use the canonical→alt-unit pair (no SI prefix variants in the catalog).
    const auto h = dv::unit_value<dv::Hour>(1.5);
    const auto s = dv::convert<dv::Second>(h);
    EXPECT_DOUBLE_EQ(s.v, 5400.0);

    const auto m = dv::convert<dv::Minute>(s);
    EXPECT_DOUBLE_EQ(m.v, 90.0);
}

TEST(UnitValue, ConvertIdentity) {
    const auto a = dv::unit_value<dv::Meter>(42.0);
    const auto b = dv::convert<dv::Meter>(a);
    EXPECT_EQ(a.v, b.v);
}

TEST(UnitValue, ConvertTemperatureWithOffset) {
    const auto c = dv::unit_value<dv::Celsius>(0.0);
    const auto k = dv::convert<dv::Kelvin>(c);
    EXPECT_NEAR(k.v, 273.15, 1e-9);

    const auto f = dv::unit_value<dv::Fahrenheit>(32.0);
    const auto k2 = dv::convert<dv::Kelvin>(f);
    EXPECT_NEAR(k2.v, 273.15, 1e-9);

    const auto c100 = dv::unit_value<dv::Celsius>(100.0);
    const auto f100 = dv::convert<dv::Fahrenheit>(c100);
    EXPECT_NEAR(f100.v, 212.0, 1e-9);
}

TEST(UnitValue, Comparison) {
    const auto a = dv::unit_value<dv::Meter>(1.0);
    const auto b = dv::unit_value<dv::Meter>(2.0);
    EXPECT_TRUE(a < b);
    EXPECT_TRUE(b > a);
    EXPECT_TRUE(a == a);
    EXPECT_TRUE(a != b);
    EXPECT_TRUE(a <= a);
    EXPECT_TRUE(a >= a);
}

TEST(UnitValue, DescriptorAccessor) {
    constexpr auto d = dv::Meter::descriptor();
    static_assert(d.kind == "length");
    static_assert(d.factor == 1.0);
    static_assert(dv::MeterValue::id() == "m");
    static_assert(dv::MeterValue::kind() == "length");
}

// --- compile-time compatibility checks ---

static_assert(dv::units_compatible<dv::Second, dv::Hour>());
static_assert(!dv::units_compatible<dv::Meter, dv::Kilogram>());
static_assert(dv::units_compatible<dv::Celsius, dv::Kelvin>());
static_assert(dv::units_compatible<dv::Celsius, dv::Fahrenheit>());

// --- imperial / mechanics catalog round-trips ---

TEST(UnitValue, ImperialLengthConvert) {
    const auto m = dv::unit_value<dv::Meter>(1.0);
    EXPECT_NEAR(dv::convert<dv::Foot>(m).v, 1.0 / 0.3048, 1e-9);
    EXPECT_NEAR(dv::convert<dv::Inch>(m).v, 1.0 / 0.0254, 1e-9);
    EXPECT_NEAR(dv::convert<dv::Mile>(dv::unit_value<dv::Meter>(1609.344)).v, 1.0, 1e-9);
    EXPECT_NEAR(dv::convert<dv::NauticalMile>(dv::unit_value<dv::Meter>(1852.0)).v, 1.0, 1e-9);
}

TEST(UnitValue, ImperialMassAndPressure) {
    const auto kg = dv::unit_value<dv::Kilogram>(1.0);
    EXPECT_NEAR(dv::convert<dv::Pound>(kg).v, 1.0 / 0.45359237, 1e-9);

    const auto pa = dv::unit_value<dv::Pascal>(6894.757293168);
    EXPECT_NEAR(dv::convert<dv::PoundsPerSquareInch>(pa).v, 1.0, 1e-9);
}

TEST(UnitValue, MechanicsAccelerationAndArea) {
    const auto g = dv::unit_value<dv::StandardGravity>(1.0);
    EXPECT_NEAR(dv::convert<dv::MeterPerSecondSquared>(g).v, 9.80665, 1e-9);

    const auto ha = dv::unit_value<dv::Hectare>(2.5);
    EXPECT_NEAR(dv::convert<dv::SquareMeter>(ha).v, 25000.0, 1e-9);
}

TEST(UnitValue, BarAndAtmosphere) {
    const auto bar = dv::unit_value<dv::Bar>(1.0);
    EXPECT_NEAR(dv::convert<dv::Pascal>(bar).v, 1e5, 1e-3);
    const auto atm = dv::unit_value<dv::Atmosphere>(1.0);
    EXPECT_NEAR(dv::convert<dv::Pascal>(atm).v, 101325.0, 1e-6);
}

TEST(UnitValue, KilowattHourEnergy) {
    const auto kwh = dv::unit_value<dv::KilowattHour>(1.0);
    EXPECT_NEAR(dv::convert<dv::Joule>(kwh).v, 3.6e6, 1e-3);
}

TEST(UnitValue, SpeedKnotAndKmh) {
    const auto kmh = dv::unit_value<dv::KilometerPerHour>(36.0);
    EXPECT_NEAR(dv::convert<dv::MeterPerSecond>(kmh).v, 10.0, 1e-9);

    const auto kn = dv::unit_value<dv::Knot>(1.0);
    EXPECT_NEAR(dv::convert<dv::MeterPerSecond>(kn).v, 1852.0 / 3600.0, 1e-9);
}

TEST(UnitValue, ArcminuteArcsecond) {
    const auto deg = dv::unit_value<dv::Degree>(1.0);
    EXPECT_NEAR(dv::convert<dv::Arcminute>(deg).v, 60.0, 1e-9);
    EXPECT_NEAR(dv::convert<dv::Arcsecond>(deg).v, 3600.0, 1e-6);
}

static_assert(dv::units_compatible<dv::Meter, dv::Foot>());
static_assert(dv::units_compatible<dv::Pascal, dv::Bar>());
static_assert(dv::units_compatible<dv::MeterPerSecond, dv::Knot>());
static_assert(!dv::units_compatible<dv::Meter, dv::Pound>());
