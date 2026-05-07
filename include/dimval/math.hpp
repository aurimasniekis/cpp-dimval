#pragma once

/// @file
/// @brief Free-function helpers that preserve unit/measure tags.
///
/// `abs`, `min`, `max`, `clamp` for `UnitValue<U,T>` and `MeasureValue<M,T>`,
/// plus a `midpoint` helper for ranges. Without these, the natural reach is
/// `.v` — which strips the tag and is the very escape hatch we want to
/// avoid. This header is *not* in the umbrella; pull it in explicitly.

#include <dimval/measure.hpp>
#include <dimval/range.hpp>
#include <dimval/traits.hpp>
#include <dimval/unit.hpp>

namespace dimval {

template <UnitLike U, NumericValue T>
[[nodiscard]] constexpr UnitValue<U, T> abs(const UnitValue<U, T>& v) noexcept {
    return UnitValue<U, T>{v.v < T{} ? static_cast<T>(-v.v) : v.v};
}

template <UnitLike U, NumericValue T>
[[nodiscard]] constexpr UnitValue<U, T> min(const UnitValue<U, T>& a,
                                            const UnitValue<U, T>& b) noexcept {
    return a.v < b.v ? a : b;
}

template <UnitLike U, NumericValue T>
[[nodiscard]] constexpr UnitValue<U, T> max(const UnitValue<U, T>& a,
                                            const UnitValue<U, T>& b) noexcept {
    return a.v < b.v ? b : a;
}

template <UnitLike U, NumericValue T>
[[nodiscard]] constexpr UnitValue<U, T>
clamp(const UnitValue<U, T>& v, const UnitValue<U, T>& lo, const UnitValue<U, T>& hi) noexcept {
    if (v.v < lo.v)
        return lo;
    if (hi.v < v.v)
        return hi;
    return v;
}

template <MeasureLike M, NumericValue T>
[[nodiscard]] constexpr MeasureValue<M, T> abs(const MeasureValue<M, T>& v) noexcept {
    return MeasureValue<M, T>{v.v < T{} ? static_cast<T>(-v.v) : v.v};
}

template <MeasureLike M, NumericValue T>
[[nodiscard]] constexpr MeasureValue<M, T> min(const MeasureValue<M, T>& a,
                                               const MeasureValue<M, T>& b) noexcept {
    return a.v < b.v ? a : b;
}

template <MeasureLike M, NumericValue T>
[[nodiscard]] constexpr MeasureValue<M, T> max(const MeasureValue<M, T>& a,
                                               const MeasureValue<M, T>& b) noexcept {
    return a.v < b.v ? b : a;
}

template <MeasureLike M, NumericValue T>
[[nodiscard]] constexpr MeasureValue<M, T> clamp(const MeasureValue<M, T>& v,
                                                 const MeasureValue<M, T>& lo,
                                                 const MeasureValue<M, T>& hi) noexcept {
    if (v.v < lo.v)
        return lo;
    if (hi.v < v.v)
        return hi;
    return v;
}

/// Midpoint of a range's bounds. Inclusion is irrelevant — only the bound
/// values matter.
template <UnitLike U, NumericValue T>
[[nodiscard]] constexpr UnitValue<U, T> midpoint(const UnitRangeValue<U, T>& r) noexcept {
    return UnitValue<U, T>{static_cast<T>((r.min().v + r.max().v) / T{2})};
}

template <MeasureLike M, NumericValue T>
[[nodiscard]] constexpr MeasureValue<M, T> midpoint(const MeasureRangeValue<M, T>& r) noexcept {
    return MeasureValue<M, T>{static_cast<T>((r.min().v + r.max().v) / T{2})};
}

}  // namespace dimval
