#include <dimval/dimval.hpp>
#include <dimval/parcel.hpp>

#include <gtest/gtest.h>

#include <parcel/parcel.h>

namespace dv = dimval;
using json = ::parcel::json_t;

TEST(Parcel, UnitValueRoundTrip) {
    dv::UnitValueCell<dv::Meter> cell{dv::unit_value<dv::Meter>(42.5)};
    const json j = cell.to_json();
    EXPECT_EQ(j["k"], "uv");
    EXPECT_EQ(j["v"]["u"], "m");
    EXPECT_EQ(j["v"]["v"], 42.5);

    ::parcel::ParcelRegistry reg;
    auto decoded = dv::UnitValueCell<dv::Meter>::from_json(j, reg);
    auto* typed = dynamic_cast<dv::UnitValueCell<dv::Meter>*>(decoded.get());
    ASSERT_NE(typed, nullptr);
    EXPECT_EQ(typed->value.v, 42.5);
}

TEST(Parcel, WireKindsAreShort) {
    EXPECT_EQ(dv::UnitValueCell<dv::Meter>::kind_id, "uv");
    EXPECT_EQ(dv::MeasureValueCell<dv::Distance>::kind_id, "mv");
    EXPECT_EQ(dv::UnitRangeValueCell<dv::Meter>::kind_id, "urv");
    EXPECT_EQ(dv::MeasureRangeValueCell<dv::Distance>::kind_id, "mrv");
}

TEST(Parcel, UnitValueMismatchRejected) {
    json j = {{"k", "uv"}, {"v", {{"u", "kg"}, {"v", 1.0}}}};
    ::parcel::ParcelRegistry reg;
    EXPECT_THROW((void)dv::UnitValueCell<dv::Meter>::from_json(j, reg),
                 ::nlohmann::json::other_error);
}

TEST(Parcel, UnitValueIntT) {
    dv::UnitValueCell<dv::Meter, int> cell{dv::UnitValue<dv::Meter, int>{7}};
    const json j = cell.to_json();
    EXPECT_EQ(j["v"]["v"], 7);

    ::parcel::ParcelRegistry reg;
    auto decoded = dv::UnitValueCell<dv::Meter, int>::from_json(j, reg);
    auto* typed = dynamic_cast<dv::UnitValueCell<dv::Meter, int>*>(decoded.get());
    ASSERT_NE(typed, nullptr);
    EXPECT_EQ(typed->value.v, 7);
}

TEST(Parcel, MeasureValueRoundTrip) {
    dv::MeasureValueCell<dv::Distance> cell{dv::measure_value<dv::Distance>(7.0)};
    const json j = cell.to_json();
    EXPECT_EQ(j["k"], "mv");
    EXPECT_EQ(j["v"]["m"], "distance");
    EXPECT_EQ(j["v"]["u"], "m");
    EXPECT_EQ(j["v"]["v"], 7.0);

    ::parcel::ParcelRegistry reg;
    auto decoded = dv::MeasureValueCell<dv::Distance>::from_json(j, reg);
    auto* typed = dynamic_cast<dv::MeasureValueCell<dv::Distance>*>(decoded.get());
    ASSERT_NE(typed, nullptr);
    EXPECT_EQ(typed->value.v, 7.0);
}

TEST(Parcel, MeasureValueMismatchRejected) {
    json j = {{"k", "mv"}, {"v", {{"m", "frequency"}, {"u", "Hz"}, {"v", 1.0}}}};
    ::parcel::ParcelRegistry reg;
    EXPECT_THROW((void)dv::MeasureValueCell<dv::Distance>::from_json(j, reg),
                 ::nlohmann::json::other_error);
}

TEST(Parcel, UnitRangeRoundTripClosed) {
    auto r = dv::UnitRangeValue<dv::Meter>::closed(dv::unit_value<dv::Meter>(1.0),
                                                   dv::unit_value<dv::Meter>(10.0));
    dv::UnitRangeValueCell<dv::Meter> cell{r};
    const json j = cell.to_json();
    EXPECT_EQ(j["k"], "urv");
    EXPECT_EQ(j["v"]["u"], "m");
    EXPECT_EQ(j["v"]["min"], 1.0);
    EXPECT_EQ(j["v"]["max"], 10.0);
    EXPECT_EQ(j["v"]["mi"], true);
    EXPECT_EQ(j["v"]["xi"], true);

    ::parcel::ParcelRegistry reg;
    auto decoded = dv::UnitRangeValueCell<dv::Meter>::from_json(j, reg);
    auto* typed = dynamic_cast<dv::UnitRangeValueCell<dv::Meter>*>(decoded.get());
    ASSERT_NE(typed, nullptr);
    EXPECT_EQ(typed->value.min().v, 1.0);
    EXPECT_EQ(typed->value.max().v, 10.0);
}

TEST(Parcel, UnitRangeRoundTripLeftOpen) {
    auto r = dv::UnitRangeValue<dv::Meter>::left_open(dv::unit_value<dv::Meter>(1.0),
                                                      dv::unit_value<dv::Meter>(10.0));
    dv::UnitRangeValueCell<dv::Meter> cell{r};
    const json j = cell.to_json();
    EXPECT_EQ(j["v"]["mi"], false);
    EXPECT_EQ(j["v"]["xi"], true);

    ::parcel::ParcelRegistry reg;
    auto decoded = dv::UnitRangeValueCell<dv::Meter>::from_json(j, reg);
    auto* typed = dynamic_cast<dv::UnitRangeValueCell<dv::Meter>*>(decoded.get());
    ASSERT_NE(typed, nullptr);
    EXPECT_EQ(typed->value.inclusion().lower, dv::Bound::Exclusive);
    EXPECT_EQ(typed->value.inclusion().upper, dv::Bound::Inclusive);
}

TEST(Parcel, UnitRangeRejectsInverted) {
    json j = {{"k", "urv"},
              {"v", {{"u", "m"}, {"min", 10.0}, {"max", 1.0}, {"mi", true}, {"xi", true}}}};
    ::parcel::ParcelRegistry reg;
    EXPECT_THROW((void)dv::UnitRangeValueCell<dv::Meter>::from_json(j, reg),
                 ::nlohmann::json::other_error);
}

TEST(Parcel, MeasureRangeRoundTrip) {
    auto r = dv::MeasureRangeValue<dv::Distance>::closed(dv::measure_value<dv::Distance>(0.0),
                                                         dv::measure_value<dv::Distance>(100.0));
    dv::MeasureRangeValueCell<dv::Distance> cell{r};
    const json j = cell.to_json();
    EXPECT_EQ(j["k"], "mrv");
    EXPECT_EQ(j["v"]["m"], "distance");
    EXPECT_EQ(j["v"]["u"], "m");
    EXPECT_EQ(j["v"]["min"], 0.0);
    EXPECT_EQ(j["v"]["max"], 100.0);

    ::parcel::ParcelRegistry reg;
    auto decoded = dv::MeasureRangeValueCell<dv::Distance>::from_json(j, reg);
    auto* typed = dynamic_cast<dv::MeasureRangeValueCell<dv::Distance>*>(decoded.get());
    ASSERT_NE(typed, nullptr);
    EXPECT_EQ(typed->value.min().v, 0.0);
    EXPECT_EQ(typed->value.max().v, 100.0);
}

TEST(Parcel, AllCellDescriptorsCallable) {
    // Each cell exposes a static descriptor() factory. RegistryDispatch
    // exercises them indirectly; this test pins them as part of the public API.
    EXPECT_NE(dv::UnitValueCell<dv::Meter>::descriptor(), nullptr);
    EXPECT_NE(dv::MeasureValueCell<dv::Distance>::descriptor(), nullptr);
    EXPECT_NE(dv::UnitRangeValueCell<dv::Meter>::descriptor(), nullptr);
    EXPECT_NE(dv::MeasureRangeValueCell<dv::Distance>::descriptor(), nullptr);
}

TEST(Parcel, RegistryDispatch) {
    ::parcel::ParcelRegistry reg;
    reg.register_kind(dv::UnitValueCell<dv::Meter>::descriptor());
    reg.register_kind(dv::MeasureValueCell<dv::Distance>::descriptor());
    reg.register_kind(dv::UnitRangeValueCell<dv::Meter>::descriptor());
    reg.register_kind(dv::MeasureRangeValueCell<dv::Distance>::descriptor());

    const auto js = {
        json{{"k", "uv"}, {"v", {{"u", "m"}, {"v", 1.0}}}},
        json{{"k", "mv"}, {"v", {{"m", "distance"}, {"u", "m"}, {"v", 2.0}}}},
        json{{"k", "urv"},
             {"v", {{"u", "m"}, {"min", 0.0}, {"max", 1.0}, {"mi", true}, {"xi", true}}}},
        json{{"k", "mrv"},
             {"v",
              {{"m", "distance"},
               {"u", "m"},
               {"min", 0.0},
               {"max", 1.0},
               {"mi", true},
               {"xi", true}}}},
    };
    const std::array<std::string_view, 4> expected = {"uv", "mv", "urv", "mrv"};
    std::size_t i = 0;
    for (const auto& j : js) {
        auto cell = reg.cell_from_json(j);
        ASSERT_NE(cell, nullptr);
        EXPECT_EQ(cell->kind(), expected[i++]);
    }
}
