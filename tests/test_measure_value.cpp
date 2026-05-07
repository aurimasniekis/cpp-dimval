#include <dimval/dimval.hpp>

#include <gtest/gtest.h>

namespace dv = dimval;

TEST(MeasureValue, ConstructAndAccess) {
    const dv::MeasureValue<dv::Distance> d = 42.5;
    EXPECT_EQ(d.v, 42.5);
    EXPECT_EQ(d.id(), "distance");
    EXPECT_EQ(d.name(), "Distance");
}

TEST(MeasureValue, AsUnitValue) {
    const dv::MeasureValue<dv::Distance> d = 42.5;
    auto u = d.as_unit_value();
    static_assert(std::is_same_v<decltype(u), dv::UnitValue<dv::Meter>>);
    EXPECT_EQ(u.v, 42.5);
}

TEST(MeasureValue, FromUnitValue) {
    const auto u = dv::unit_value<dv::Meter>(3.14);
    const auto d = dv::from_unit_value<dv::Distance>(u);
    EXPECT_EQ(d.v, 3.14);
}

TEST(MeasureValue, FactoryHelper) {
    const auto d = dv::measure_value<dv::Distance>(7.0);
    EXPECT_EQ(d.v, 7.0);
}

TEST(MeasureValue, Arithmetic) {
    const auto a = dv::measure_value<dv::Distance>(3.0);
    const auto b = dv::measure_value<dv::Distance>(4.0);
    EXPECT_EQ((a + b).v, 7.0);
    EXPECT_EQ((b - a).v, 1.0);
    EXPECT_EQ((a * 2.0).v, 6.0);
    EXPECT_EQ((a / 2.0).v, 1.5);
    EXPECT_EQ(a / a, 1.0);
}

TEST(MeasureValue, Comparison) {
    const auto a = dv::measure_value<dv::Distance>(1.0);
    const auto b = dv::measure_value<dv::Distance>(2.0);
    EXPECT_TRUE(a < b);
}

TEST(MeasureValue, FrequencyUsesHertz) {
    const auto f = dv::measure_value<dv::Frequency>(1000.0);
    auto u = f.as_unit_value();
    static_assert(std::is_same_v<decltype(u), dv::UnitValue<dv::Hertz>>);
    EXPECT_EQ(u.v, 1000.0);
}

TEST(MeasureValue, TypeAliasShorthand) {
    const dv::DistanceValue d = 42.5;
    EXPECT_EQ(d.v, 42.5);
    EXPECT_EQ(d.name(), "Distance");
}

TEST(MeasureValue, ImplicitFromNumericAndOf) {
    const dv::DistanceValue d = 1500.0;  // implicit
    EXPECT_EQ(d.v, 1500.0);

    const dv::DistanceValueShared s = dv::DistanceValue::of(2000.0);
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(s->v, 2000.0);

    const dv::DistanceValueUnique p = dv::DistanceValue::unique(3000.0);
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(p->v, 3000.0);
}

TEST(MeasureValue, MechanicsMeasures) {
    const dv::SpeedValue s = 10.0;
    EXPECT_EQ(s.id(), "speed");
    EXPECT_EQ(s.kind(), "velocity");

    const dv::AccelerationValue a = 9.81;
    EXPECT_EQ(a.id(), "acceleration");

    const dv::AreaValue ar = 100.0;
    EXPECT_EQ(ar.id(), "area");

    const dv::DensityValue dn = 1000.0;
    EXPECT_EQ(dn.id(), "density");

    const dv::VolumeValue vol = 5.0;
    EXPECT_EQ(vol.kind(), "volume");

    const dv::PressureValue pr = 101325.0;
    EXPECT_EQ(pr.kind(), "pressure");

    const dv::ForceValue fr = 1.0;
    EXPECT_EQ(fr.kind(), "force");
}

TEST(MeasureValue, IMeasureValuePolymorphism) {
    const dv::IMeasureValueUnique m = dv::DistanceValue::unique(1.5);
    EXPECT_EQ(m->descriptor().id, "distance");
    EXPECT_EQ(m->unit_descriptor().id, "m");
    EXPECT_EQ(m->descriptor().name, "Distance");
    EXPECT_EQ(m->unit_descriptor().symbol, "m");
    EXPECT_EQ(m->unit_descriptor().kind, "length");
    EXPECT_EQ(m->numeric_as_double(), 1.5);
    EXPECT_EQ(m->to_string(), "1.5 m");

    const auto cloned = m->clone();
    EXPECT_EQ(cloned->descriptor().id, "distance");
}
