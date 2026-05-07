#include <dimval/dimval.hpp>

#include <gtest/gtest.h>

#include <thread>
#include <vector>

namespace dv = dimval;

TEST(Registry, BuiltinsAreRegistered) {
    const auto& r = dv::UnitRegistry::global();
    EXPECT_NE(r.find("m"), nullptr);
    EXPECT_NE(r.find("kg"), nullptr);
    EXPECT_NE(r.find("s"), nullptr);
    EXPECT_NE(r.find("Hz"), nullptr);
    EXPECT_NE(r.find("dB"), nullptr);
}

TEST(Registry, FindBySymbol) {
    const auto& r = dv::UnitRegistry::global();
    const auto* d = r.find("°C");
    ASSERT_NE(d, nullptr);
    EXPECT_EQ(d->id, "degC");
}

TEST(Registry, ListNonEmpty) {
    const auto& r = dv::UnitRegistry::global();
    const auto all = r.list();
    EXPECT_GT(all.size(), 20u);
}

TEST(Registry, ByKind) {
    const auto& r = dv::UnitRegistry::global();
    const auto lengths = r.by_kind("length");
    EXPECT_GE(lengths.size(), 1u);
    const auto times = r.by_kind("time");
    EXPECT_GE(times.size(), 4u);  // Second + Minute + Hour + Day (alt non-prefix units)
    const auto temps = r.by_kind("temperature");
    EXPECT_EQ(temps.size(), 3u);  // Kelvin + Celsius + Fahrenheit
}

TEST(Registry, MeasureBuiltins) {
    const auto& r = dv::MeasureRegistry::global();
    EXPECT_NE(r.find("distance"), nullptr);
    EXPECT_NE(r.find("frequency"), nullptr);
    EXPECT_NE(r.find("snr"), nullptr);
}

TEST(Registry, RegisterByTagSucceedsThenReportsAlreadyPresent) {
    // Built-ins are pre-registered, so the tag-based call should report
    // "already present" (returns false) for any built-in unit/measure.
    auto& r = dv::UnitRegistry::global();
    EXPECT_FALSE(r.register_unit<dv::Meter>());
    EXPECT_FALSE(r.register_unit<dv::Hertz>());

    auto& mr = dv::MeasureRegistry::global();
    EXPECT_FALSE(mr.register_measure<dv::Distance>());
    EXPECT_FALSE(mr.register_measure<dv::Frequency>());
}

TEST(Registry, NewCatalogUnitsRegistered) {
    const auto& r = dv::UnitRegistry::global();
    // Imperial.
    EXPECT_NE(r.find("ft"), nullptr);
    EXPECT_NE(r.find("in"), nullptr);
    EXPECT_NE(r.find("mi"), nullptr);
    EXPECT_NE(r.find("nmi"), nullptr);
    EXPECT_NE(r.find("lb"), nullptr);
    EXPECT_NE(r.find("psi"), nullptr);
    EXPECT_NE(r.find("gal"), nullptr);
    // Mechanics.
    EXPECT_NE(r.find("m_per_s2"), nullptr);
    EXPECT_NE(r.find("g0"), nullptr);
    EXPECT_NE(r.find("m2"), nullptr);
    EXPECT_NE(r.find("ha"), nullptr);
    EXPECT_NE(r.find("kg_per_m3"), nullptr);
    // SI alternates.
    EXPECT_NE(r.find("bar"), nullptr);
    EXPECT_NE(r.find("atm"), nullptr);
    EXPECT_NE(r.find("kWh"), nullptr);
    EXPECT_NE(r.find("G"), nullptr);
    EXPECT_NE(r.find("arcmin"), nullptr);
    EXPECT_NE(r.find("arcsec"), nullptr);
    // Practical speed.
    EXPECT_NE(r.find("km_per_h"), nullptr);
    EXPECT_NE(r.find("kn"), nullptr);
}

TEST(Registry, NewCatalogMeasuresRegistered) {
    const auto& mr = dv::MeasureRegistry::global();
    EXPECT_NE(mr.find("speed"), nullptr);
    EXPECT_NE(mr.find("acceleration"), nullptr);
    EXPECT_NE(mr.find("area"), nullptr);
    EXPECT_NE(mr.find("density"), nullptr);
    EXPECT_NE(mr.find("volume"), nullptr);
    EXPECT_NE(mr.find("pressure"), nullptr);
    EXPECT_NE(mr.find("force"), nullptr);
}

TEST(Registry, ConcurrentReads) {
    const auto& r = dv::UnitRegistry::global();
    constexpr int n_threads = 8;
    constexpr int per_thread = 1000;
    std::vector<std::thread> threads;
    threads.reserve(n_threads);
    for (int i = 0; i < n_threads; ++i) {
        threads.emplace_back([&] {
            for (int k = 0; k < per_thread; ++k) {
                EXPECT_NE(r.find("m"), nullptr);
            }
        });
    }
    for (auto& t : threads) {
        t.join();
    }
}
