#include <dimval/dimval.hpp>

#include <gtest/gtest.h>

#include <unordered_map>
#include <unordered_set>

namespace dv = dimval;

TEST(Hash, UnitValueWorksInUnorderedSet) {
    std::unordered_set<dv::UnitValue<dv::Meter>> s;
    s.insert(dv::unit_value<dv::Meter>(1.0));
    s.insert(dv::unit_value<dv::Meter>(2.0));
    s.insert(dv::unit_value<dv::Meter>(1.0));  // duplicate
    EXPECT_EQ(s.size(), 2u);
}

TEST(Hash, MeasureValueAsKey) {
    std::unordered_map<dv::MeasureValue<dv::Distance>, int> m;
    m[dv::measure_value<dv::Distance>(1.0)] = 10;
    m[dv::measure_value<dv::Distance>(2.0)] = 20;
    EXPECT_EQ(m[dv::measure_value<dv::Distance>(1.0)], 10);
    EXPECT_EQ(m[dv::measure_value<dv::Distance>(2.0)], 20);
}

TEST(Hash, EqualValuesShareHash) {
    const auto a = dv::unit_value<dv::Meter>(1.5);
    const auto b = dv::unit_value<dv::Meter>(1.5);
    constexpr auto h = std::hash<dv::UnitValue<dv::Meter>>{};
    EXPECT_EQ(h(a), h(b));
}

TEST(Hash, RangeHashes) {
    const auto r1 = dv::UnitRangeValue<dv::Meter>::closed(dv::unit_value<dv::Meter>(0.0),
                                                          dv::unit_value<dv::Meter>(1.0));
    const auto r2 = dv::UnitRangeValue<dv::Meter>::closed(dv::unit_value<dv::Meter>(0.0),
                                                          dv::unit_value<dv::Meter>(1.0));
    const auto r3 = dv::UnitRangeValue<dv::Meter>::open(dv::unit_value<dv::Meter>(0.0),
                                                        dv::unit_value<dv::Meter>(1.0));
    constexpr auto h = std::hash<dv::UnitRangeValue<dv::Meter>>{};
    EXPECT_EQ(h(r1), h(r2));
    EXPECT_NE(h(r1), h(r3));
}
