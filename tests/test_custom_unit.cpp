#include <dimval/dimval.hpp>

#include <gtest/gtest.h>

namespace dv = dimval;

// User-defined unit using the same DIMVAL_DEFINE_UNIT macro.

DIMVAL_DEFINE_UNIT(Frame,
                   "frame",
                   "frm",
                   "frm",
                   "frame",
                   "count_event",
                   1.0,
                   "mdi:movie-roll",
                   dv::palette::blue_400)

DIMVAL_DEFINE_UNIT(SubFrame,
                   "subframe",
                   "subfrm",
                   "subfrm",
                   "subframe",
                   "count_event",
                   1.0 / 16.0,  // 16 subframes per frame
                   "mdi:movie-roll-outline",
                   dv::palette::blue_300)

TEST(CustomUnit, DefinesAndRegisters) {
    const auto& reg = dv::UnitRegistry::global();
    EXPECT_NE(reg.find("frame"), nullptr);
    EXPECT_NE(reg.find("frm"), nullptr);
}

TEST(CustomUnit, UsableInUnitValue) {
    auto v = dv::unit_value<dv::Frame>(42.0);
    EXPECT_EQ(v.id(), "frame");
    EXPECT_EQ(v.kind(), "count_event");
}

TEST(CustomUnit, ConvertWithinKind) {
    const auto frames = dv::unit_value<dv::Frame>(2.0);
    const auto sub = dv::convert<dv::SubFrame>(frames);
    EXPECT_DOUBLE_EQ(sub.v, 32.0);
}

TEST(CustomUnit, IconAndColor) {
    auto v = dv::unit_value<dv::Frame>(1.0);
    EXPECT_EQ(v.icon(), "mdi:movie-roll");
    EXPECT_EQ(v.color(), dv::palette::blue_400);
}

TEST(CustomUnit, RuntimeRegistration) {
    auto& reg = dv::UnitRegistry::global();
    constexpr dv::UnitDescriptor d{
        .id = "furlong",
        .symbol = "fur",
        .short_name = "fur",
        .long_name = "furlong",
        .kind = "length",
        .factor = 201.168,
    };
    reg.register_unit(d);
    EXPECT_NE(reg.find("furlong"), nullptr);
    EXPECT_EQ(reg.find("fur")->kind, "length");
}
