#pragma once

/// @file
/// @brief std::hash specializations for all dimval value types.

#include <dimval/measure.hpp>
#include <dimval/range.hpp>
#include <dimval/traits.hpp>
#include <dimval/unit.hpp>

#include <cstddef>
#include <functional>
#include <string_view>

namespace dimval::detail {

[[nodiscard]] inline std::size_t hash_combine(std::size_t seed, const std::size_t v) noexcept {
    // boost::hash_combine constants — well-distributed mixing for 64-bit seeds.
    seed ^= v + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
    return seed;
}

}  // namespace dimval::detail

template <dimval::UnitLike U, dimval::NumericValue T>
struct std::hash<dimval::UnitValue<U, T>> {
    [[nodiscard]] std::size_t operator()(const dimval::UnitValue<U, T>& v) const noexcept {
        std::size_t s = std::hash<std::string_view>{}(U::id);
        s = dimval::detail::hash_combine(s, std::hash<T>{}(v.v));
        return s;
    }
};

template <dimval::MeasureLike M, dimval::NumericValue T>
struct std::hash<dimval::MeasureValue<M, T>> {
    [[nodiscard]] std::size_t operator()(const dimval::MeasureValue<M, T>& v) const noexcept {
        std::size_t s = std::hash<std::string_view>{}(M::id);
        s = dimval::detail::hash_combine(s, std::hash<T>{}(v.v));
        return s;
    }
};

template <dimval::UnitLike U, dimval::NumericValue T>
struct std::hash<dimval::UnitRangeValue<U, T>> {
    [[nodiscard]] std::size_t operator()(const dimval::UnitRangeValue<U, T>& r) const noexcept {
        std::size_t s = std::hash<std::string_view>{}(U::id);
        s = dimval::detail::hash_combine(s, std::hash<T>{}(r.min().v));
        s = dimval::detail::hash_combine(s, std::hash<T>{}(r.max().v));
        s = dimval::detail::hash_combine(s, static_cast<std::size_t>(r.inclusion().lower));
        s = dimval::detail::hash_combine(s, static_cast<std::size_t>(r.inclusion().upper));
        return s;
    }
};

template <dimval::MeasureLike M, dimval::NumericValue T>
struct std::hash<dimval::MeasureRangeValue<M, T>> {
    [[nodiscard]] std::size_t operator()(const dimval::MeasureRangeValue<M, T>& r) const noexcept {
        std::size_t s = std::hash<std::string_view>{}(M::id);
        s = dimval::detail::hash_combine(s, std::hash<T>{}(r.min().v));
        s = dimval::detail::hash_combine(s, std::hash<T>{}(r.max().v));
        s = dimval::detail::hash_combine(s, static_cast<std::size_t>(r.inclusion().lower));
        s = dimval::detail::hash_combine(s, static_cast<std::size_t>(r.inclusion().upper));
        return s;
    }
};
