#include <dimval/dimval.hpp>
#include <dimval/json_nlohmann.hpp>

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

namespace dv = dimval;
using json = nlohmann::json;

TEST(Json, UnitValueRoundTrip) {
    auto v = dv::unit_value<dv::Meter>(42.5);
    json j = v;
    EXPECT_EQ(j["u"], "m");
    EXPECT_EQ(j["v"], 42.5);

    const auto w = j.get<dv::UnitValue<dv::Meter>>();
    EXPECT_EQ(w.v, 42.5);
}

TEST(Json, UnitValueMismatchThrows) {
    json j = {{"u", "kg"}, {"v", 1.0}};
    EXPECT_THROW(j.get<dv::UnitValue<dv::Meter>>(), nlohmann::json::other_error);
}

TEST(Json, MeasureValueRoundTrip) {
    auto v = dv::measure_value<dv::Distance>(7.0);
    json j = v;
    EXPECT_EQ(j["m"], "distance");
    EXPECT_EQ(j["u"], "m");
    EXPECT_EQ(j["v"], 7.0);

    const auto w = j.get<dv::MeasureValue<dv::Distance>>();
    EXPECT_EQ(w.v, 7.0);
}

TEST(Json, MeasureMismatchThrows) {
    json j = {{"m", "frequency"}, {"u", "Hz"}, {"v", 1.0}};
    EXPECT_THROW(j.get<dv::MeasureValue<dv::Distance>>(), nlohmann::json::other_error);
}

TEST(Json, RangeRoundTrip) {
    auto r = dv::UnitRangeValue<dv::Meter>::closed(dv::unit_value<dv::Meter>(1.0),
                                                   dv::unit_value<dv::Meter>(10.0));
    json j = r;
    EXPECT_EQ(j["u"], "m");
    EXPECT_EQ(j["min"], 1.0);
    EXPECT_EQ(j["max"], 10.0);
    EXPECT_EQ(j["mi"], true);
    EXPECT_EQ(j["xi"], true);

    const auto w = j.get<dv::UnitRangeValue<dv::Meter>>();
    EXPECT_EQ(w.min().v, 1.0);
    EXPECT_EQ(w.max().v, 10.0);
}

TEST(Json, RangeMixedInclusion) {
    auto r = dv::UnitRangeValue<dv::Meter>::left_open(dv::unit_value<dv::Meter>(1.0),
                                                      dv::unit_value<dv::Meter>(10.0));
    json j = r;
    EXPECT_EQ(j["mi"], false);
    EXPECT_EQ(j["xi"], true);
    const auto w = j.get<dv::UnitRangeValue<dv::Meter>>();
    EXPECT_EQ(w.inclusion().lower, dv::Bound::Exclusive);
    EXPECT_EQ(w.inclusion().upper, dv::Bound::Inclusive);
}

TEST(Json, RangeRejectsInverted) {
    json j = {{"u", "m"}, {"min", 10.0}, {"max", 1.0}, {"mi", true}, {"xi", true}};
    EXPECT_THROW(j.get<dv::UnitRangeValue<dv::Meter>>(), nlohmann::json::other_error);
}

// --- coverage-gap fillers ---

TEST(Json, MeasureValueUnitFieldMissing) {
    // The unit field is optional on parse; a payload without "u" still decodes.
    const json j = {{"m", "distance"}, {"v", 42.0}};
    const auto w = j.get<dv::MeasureValue<dv::Distance>>();
    EXPECT_EQ(w.v, 42.0);
}

TEST(Json, MeasureRangeValueUnitMismatch) {
    json j = {
        {"m", "distance"}, {"u", "kg"}, {"min", 0.0}, {"max", 1.0}, {"mi", true}, {"xi", true}};
    EXPECT_THROW((void)j.get<dv::MeasureRangeValue<dv::Distance>>(), nlohmann::json::other_error);
}

TEST(Json, RangeMaxInclusiveDefault) {
    // When "xi" is omitted, the default is true (inclusive).
    const json j = {{"u", "m"}, {"min", 0.0}, {"max", 10.0}};
    const auto r = j.get<dv::UnitRangeValue<dv::Meter>>();
    EXPECT_EQ(r.inclusion().lower, dv::Bound::Inclusive);
    EXPECT_EQ(r.inclusion().upper, dv::Bound::Inclusive);
}

TEST(Json, UnitDescriptorToJson) {
    constexpr auto d = dv::Meter::descriptor();
    json j = d;
    EXPECT_EQ(j["id"], "m");
    EXPECT_EQ(j["kind"], "length");
    EXPECT_EQ(j["long_name"], "meter");
}

TEST(Json, MeasureDescriptorToJson) {
    constexpr auto d = dv::Distance::descriptor();
    json j = d;
    EXPECT_EQ(j["id"], "distance");
    EXPECT_EQ(j["base_unit_id"], "m");
    EXPECT_EQ(j["name"], "Distance");
}
