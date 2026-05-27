#pragma once

/// @file
/// @brief Optional nlohmann::json integration.
///
/// Define DIMVAL_WITH_NLOHMANN_JSON or simply have <nlohmann/json.hpp>
/// available on the include path; both paths enable this header.
///
/// Schema (compact field names):
///
///     UnitValue           {"u":"m","v":42.5}
///     MeasureValue        {"m":"distance","u":"m","v":42.5}
///     UnitRangeValue      {"u":"m","min":0,"max":10,"mi":true,"xi":true}
///     MeasureRangeValue   {"m":"distance","u":"m","min":0,"max":10,
///                          "mi":true,"xi":true}
///
/// Field-name legend: `u` = unit id, `m` = measure id, `v` = value, `mi` =
/// min_inclusive, `xi` = max_inclusive (x = max convention).
///
/// On parse, the `u` / `m` fields are validated against the tag's descriptor;
/// mismatch throws nlohmann::json::other_error so the failure shows up at the
/// ADL boundary like any other from_json mismatch.

#if !defined(DIMVAL_WITH_NLOHMANN_JSON)
#if __has_include(<nlohmann/json.hpp>)
#define DIMVAL_WITH_NLOHMANN_JSON 1
#else
#define DIMVAL_WITH_NLOHMANN_JSON 0
#endif
#endif

#if DIMVAL_WITH_NLOHMANN_JSON

#include <dimval/measure.hpp>
#include <dimval/range.hpp>
#include <dimval/traits.hpp>
#include <dimval/unit.hpp>

#include <nlohmann/json.hpp>

#include <commons/json.hpp>

#include <string>

namespace dimval {

template <UnitLike U, NumericValue T>
inline void to_json(::nlohmann::json& j, const UnitValue<U, T>& v) {
    constexpr auto d = U::descriptor();
    j = ::nlohmann::json{{"u", d.id}, {"v", v.v}};
}

template <UnitLike U, NumericValue T>
inline void from_json(const ::nlohmann::json& j, UnitValue<U, T>& v) {
    constexpr auto d = U::descriptor();
    const auto id = j.at("u").get<std::string>();
    if (id != d.id) {
        throw ::nlohmann::detail::other_error::create(
            502,
            std::string{"dimval: unit mismatch: expected '"} + std::string{d.id} + "', got '" + id +
                "'",
            &j);
    }
    v.v = j.at("v").get<T>();
}

template <MeasureLike M, NumericValue T>
inline void to_json(::nlohmann::json& j, const MeasureValue<M, T>& v) {
    constexpr auto md = M::descriptor();
    using unit_t = M::base_unit_t;
    constexpr auto ud = unit_t::descriptor();
    j = ::nlohmann::json{{"m", md.id}, {"u", ud.id}, {"v", v.v}};
}

template <MeasureLike M, NumericValue T>
inline void from_json(const ::nlohmann::json& j, MeasureValue<M, T>& v) {
    constexpr auto md = M::descriptor();
    using unit_t = M::base_unit_t;
    constexpr auto ud = unit_t::descriptor();
    const auto mid = j.at("m").get<std::string>();
    if (mid != md.id) {
        throw ::nlohmann::detail::other_error::create(
            502,
            std::string{"dimval: measure mismatch: expected '"} + std::string{md.id} + "', got '" +
                mid + "'",
            &j);
    }
    if (const auto it = j.find("u"); it != j.end()) {
        const auto uid = it->get<std::string>();
        if (uid != ud.id) {
            throw ::nlohmann::detail::other_error::create(
                502,
                std::string{"dimval: unit mismatch: expected '"} + std::string{ud.id} + "', got '" +
                    uid + "'",
                &j);
        }
    }
    v.v = j.at("v").get<T>();
}

template <UnitLike U, NumericValue T>
inline void to_json(::nlohmann::json& j, const UnitRangeValue<U, T>& r) {
    constexpr auto d = U::descriptor();
    j = ::nlohmann::json{
        {"u", d.id},
        {"min", r.min().v},
        {"max", r.max().v},
        {"mi", r.inclusion().lower == Bound::Inclusive},
        {"xi", r.inclusion().upper == Bound::Inclusive},
    };
}

template <UnitLike U, NumericValue T>
inline void from_json(const ::nlohmann::json& j, UnitRangeValue<U, T>& r) {
    constexpr auto d = U::descriptor();
    const auto id = j.at("u").get<std::string>();
    if (id != d.id) {
        throw ::nlohmann::detail::other_error::create(
            502,
            std::string{"dimval: unit mismatch: expected '"} + std::string{d.id} + "', got '" + id +
                "'",
            &j);
    }
    const auto lo = j.at("min").get<T>();
    const auto hi = j.at("max").get<T>();
    RangeInclusion inc{
        j.value("mi", true) ? Bound::Inclusive : Bound::Exclusive,
        j.value("xi", true) ? Bound::Inclusive : Bound::Exclusive,
    };
    auto built = UnitRangeValue<U, T>::make(UnitValue<U, T>{lo}, UnitValue<U, T>{hi}, inc);
    if (!built) {
        throw ::nlohmann::detail::other_error::create(
            502, std::string{"dimval: invalid range: "} + built.error().message, &j);
    }
    r = *built;
}

template <MeasureLike M, NumericValue T>
inline void to_json(::nlohmann::json& j, const MeasureRangeValue<M, T>& r) {
    constexpr auto md = M::descriptor();
    using unit_t = M::base_unit_t;
    constexpr auto ud = unit_t::descriptor();
    j = ::nlohmann::json{
        {"m", md.id},
        {"u", ud.id},
        {"min", r.min().v},
        {"max", r.max().v},
        {"mi", r.inclusion().lower == Bound::Inclusive},
        {"xi", r.inclusion().upper == Bound::Inclusive},
    };
}

template <MeasureLike M, NumericValue T>
inline void from_json(const ::nlohmann::json& j, MeasureRangeValue<M, T>& r) {
    constexpr auto md = M::descriptor();
    using unit_t = M::base_unit_t;
    constexpr auto ud = unit_t::descriptor();
    const auto mid = j.at("m").get<std::string>();
    if (mid != md.id) {
        throw ::nlohmann::detail::other_error::create(
            502,
            std::string{"dimval: measure mismatch: expected '"} + std::string{md.id} + "', got '" +
                mid + "'",
            &j);
    }
    if (const auto it = j.find("u"); it != j.end()) {
        const auto uid = it->get<std::string>();
        if (uid != ud.id) {
            throw ::nlohmann::detail::other_error::create(
                502,
                std::string{"dimval: unit mismatch: expected '"} + std::string{ud.id} + "', got '" +
                    uid + "'",
                &j);
        }
    }
    const auto lo = j.at("min").get<T>();
    const auto hi = j.at("max").get<T>();
    RangeInclusion inc{
        j.value("mi", true) ? Bound::Inclusive : Bound::Exclusive,
        j.value("xi", true) ? Bound::Inclusive : Bound::Exclusive,
    };
    auto built = MeasureRangeValue<M, T>::make(MeasureValue<M, T>{lo}, MeasureValue<M, T>{hi}, inc);
    if (!built) {
        throw ::nlohmann::detail::other_error::create(
            502, std::string{"dimval: invalid range: "} + built.error().message, &j);
    }
    r = *built;
}

inline void to_json(::nlohmann::json& j, const UnitDescriptor& d) {
    j = ::nlohmann::json{
        {"id", d.id},
        {"symbol", d.symbol},
        {"short_name", d.short_name},
        {"long_name", d.long_name},
        {"kind", d.kind},
        {"factor", d.factor},
        {"offset", d.offset},
        {"formatter", d.formatter},
        {"default_precision", d.default_precision},
    };
    // nlohmann does not serialize std::optional; an unset field emits null.
    j["icon"] = d.icon ? ::nlohmann::json(*d.icon) : ::nlohmann::json(nullptr);
    j["color"] = d.color ? ::nlohmann::json(*d.color) : ::nlohmann::json(nullptr);
}

inline void to_json(::nlohmann::json& j, const MeasureDescriptor& d) {
    j = ::nlohmann::json{
        {"id", d.id},
        {"base_unit_id", d.base_unit_id},
        {"name", d.name},
        {"formatter", d.formatter},
        {"default_precision", d.default_precision},
    };
    // nlohmann does not serialize std::optional; an unset field emits null.
    j["icon"] = d.icon ? ::nlohmann::json(*d.icon) : ::nlohmann::json(nullptr);
    j["color"] = d.color ? ::nlohmann::json(*d.color) : ::nlohmann::json(nullptr);
}

}  // namespace dimval

#endif  // DIMVAL_WITH_NLOHMANN_JSON
