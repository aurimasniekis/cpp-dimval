#pragma once

/// @file
/// @brief Optional cpp-parcel integration. Activates when parcel is on the
///        include path (or when DIMVAL_WITH_PARCEL=1 is defined by CMake).
///
/// Wire envelope (parcel framing of dimval's JSON adapter shape):
///
///     UnitValue<U,T>          {"k":"uv",  "v":{"u":"m","v":42.5}}
///     MeasureValue<M,T>       {"k":"mv",  "v":{"m":"distance","u":"m","v":42.5}}
///     UnitRangeValue<U,T>     {"k":"urv", "v":{"u":"m","min":0,"max":10,
///                                              "mi":true,"xi":true}}
///     MeasureRangeValue<M,T>  {"k":"mrv", "v":{"m":"distance","u":"m",
///                                              "min":0,"max":10,
///                                              "mi":true,"xi":true}}
///
/// Inner field-name legend (from dimval's JSON adapter): `u` = unit id,
/// `m` = measure id, `v` = value, `mi` = min_inclusive, `xi` = max_inclusive.
///
/// Limitation: every UnitValueCell<U,T> instantiation shares kind_id="uv" (and
/// likewise for the other three cells), so a single ParcelRegistry cannot hold
/// dispatchers for multiple unit-tag variants simultaneously — the last
/// register_kind() wins. dimval users typically decode at sites that already
/// know the C++ type, and the inner JSON-adapter from_json validates the
/// `unit`/`measure` field, so cross-tag mismatches still surface as exceptions.

#if !defined(DIMVAL_WITH_PARCEL)
#if __has_include(<parcel/parcel.h>)
#define DIMVAL_WITH_PARCEL 1
#else
#define DIMVAL_WITH_PARCEL 0
#endif
#endif

#if DIMVAL_WITH_PARCEL

#include <dimval/format.hpp>
#include <dimval/json_nlohmann.hpp>
#include <dimval/measure.hpp>
#include <dimval/range.hpp>
#include <dimval/traits.hpp>
#include <dimval/unit.hpp>

#include <memory>
#include <string>
#include <string_view>

#include <parcel/parcel.h>

namespace dimval {

template <UnitLike U, NumericValue T = double>
class UnitValueCell : public ::parcel::BaseCell<UnitValueCell<U, T>, UnitValue<U, T>> {
    using base_t = ::parcel::BaseCell<UnitValueCell<U, T>, UnitValue<U, T>>;

public:
    using base_t::base_t;
    using base_t::operator=;

    static constexpr std::string_view kind_id = "uv";

    [[nodiscard]] std::string to_string() const override {
        return this->value.to_string();
    }

    [[nodiscard]] std::string to_formatted_string() const override {
        return this->value.to_formatted_string();
    }

    static ::parcel::cell_t from_json(::parcel::json_t const& j, ::parcel::ParcelRegistry const&) {
        auto v = base_t::template cell_from_json<UnitValue<U, T>>(j, kind_id);
        auto cell = std::make_shared<UnitValueCell>(v);
        base_t::absorb_meta(j, cell);
        return cell;
    }

    static ::parcel::cell_type_descriptor_t descriptor() {
        static const auto d = std::make_shared<::parcel::SimpleCellTypeDescriptor<UnitValueCell>>(
            ::parcel::descriptor::MetaInfo{.name = "dimval::UnitValue"});
        return d;
    }
};

template <MeasureLike M, NumericValue T = double>
class MeasureValueCell : public ::parcel::BaseCell<MeasureValueCell<M, T>, MeasureValue<M, T>> {
    using base_t = ::parcel::BaseCell<MeasureValueCell<M, T>, MeasureValue<M, T>>;

public:
    using base_t::base_t;
    using base_t::operator=;

    static constexpr std::string_view kind_id = "mv";

    [[nodiscard]] std::string to_string() const override {
        return this->value.to_string();
    }

    [[nodiscard]] std::string to_formatted_string() const override {
        return this->value.to_formatted_string();
    }

    static ::parcel::cell_t from_json(::parcel::json_t const& j, ::parcel::ParcelRegistry const&) {
        auto v = base_t::template cell_from_json<MeasureValue<M, T>>(j, kind_id);
        auto cell = std::make_shared<MeasureValueCell>(v);
        base_t::absorb_meta(j, cell);
        return cell;
    }

    static ::parcel::cell_type_descriptor_t descriptor() {
        static const auto d =
            std::make_shared<::parcel::SimpleCellTypeDescriptor<MeasureValueCell>>(
                ::parcel::descriptor::MetaInfo{.name = "dimval::MeasureValue"});
        return d;
    }
};

template <UnitLike U, NumericValue T = double>
class UnitRangeValueCell
    : public ::parcel::BaseCell<UnitRangeValueCell<U, T>, UnitRangeValue<U, T>> {
    using base_t = ::parcel::BaseCell<UnitRangeValueCell<U, T>, UnitRangeValue<U, T>>;

public:
    using base_t::base_t;
    using base_t::operator=;

    static constexpr std::string_view kind_id = "urv";

    [[nodiscard]] std::string to_string() const override {
        return this->value.to_string();
    }

    [[nodiscard]] std::string to_formatted_string() const override {
        return this->value.to_formatted_string();
    }

    static ::parcel::cell_t from_json(::parcel::json_t const& j, ::parcel::ParcelRegistry const&) {
        auto v = base_t::template cell_from_json<UnitRangeValue<U, T>>(j, kind_id);
        auto cell = std::make_shared<UnitRangeValueCell>(v);
        base_t::absorb_meta(j, cell);
        return cell;
    }

    static ::parcel::cell_type_descriptor_t descriptor() {
        static const auto d =
            std::make_shared<::parcel::SimpleCellTypeDescriptor<UnitRangeValueCell>>(
                ::parcel::descriptor::MetaInfo{.name = "dimval::UnitRangeValue"});
        return d;
    }
};

template <MeasureLike M, NumericValue T = double>
class MeasureRangeValueCell
    : public ::parcel::BaseCell<MeasureRangeValueCell<M, T>, MeasureRangeValue<M, T>> {
    using base_t = ::parcel::BaseCell<MeasureRangeValueCell<M, T>, MeasureRangeValue<M, T>>;

public:
    using base_t::base_t;
    using base_t::operator=;

    static constexpr std::string_view kind_id = "mrv";

    [[nodiscard]] std::string to_string() const override {
        return this->value.to_string();
    }

    [[nodiscard]] std::string to_formatted_string() const override {
        return this->value.to_formatted_string();
    }

    static ::parcel::cell_t from_json(::parcel::json_t const& j, ::parcel::ParcelRegistry const&) {
        auto v = base_t::template cell_from_json<MeasureRangeValue<M, T>>(j, kind_id);
        auto cell = std::make_shared<MeasureRangeValueCell>(v);
        base_t::absorb_meta(j, cell);
        return cell;
    }

    static ::parcel::cell_type_descriptor_t descriptor() {
        static const auto d =
            std::make_shared<::parcel::SimpleCellTypeDescriptor<MeasureRangeValueCell>>(
                ::parcel::descriptor::MetaInfo{.name = "dimval::MeasureRangeValue"});
        return d;
    }
};

}  // namespace dimval

#endif  // DIMVAL_WITH_PARCEL
