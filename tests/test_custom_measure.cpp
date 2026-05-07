#include <dimval/dimval.hpp>

#include <gtest/gtest.h>

namespace dv = dimval;

// We need a unit to base our custom measure on. Reuse a built-in.
DIMVAL_DEFINE_MEASURE(StorageCapacity,
                      ::dimval::Byte,
                      "storage_capacity",
                      "Storage capacity",
                      "mdi:harddisk",
                      dv::palette::cyan_500)

TEST(CustomMeasure, Registered) {
    const auto& mreg = dv::MeasureRegistry::global();
    EXPECT_NE(mreg.find("storage_capacity"), nullptr);
}

TEST(CustomMeasure, UsableAndConvertsToBaseUnit) {
    const auto cap = dv::measure_value<dv::StorageCapacity>(512.0);
    auto u = cap.as_unit_value();
    static_assert(std::is_same_v<decltype(u), dv::UnitValue<dv::Byte>>);
    EXPECT_EQ(u.v, 512.0);
}

TEST(CustomMeasure, IconAndColor) {
    auto cap = dv::measure_value<dv::StorageCapacity>(1.0);
    EXPECT_EQ(cap.icon(), "mdi:harddisk");
    EXPECT_EQ(cap.color(), dv::palette::cyan_500);
}
