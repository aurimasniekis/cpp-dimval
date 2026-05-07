#pragma once

/// @file
/// @brief UnitRangeValue and MeasureRangeValue — closed/open intervals of dimensional values.

#include <dimval/core.hpp>
#include <dimval/measure.hpp>
#include <dimval/traits.hpp>
#include <dimval/unit.hpp>

#include <expected>
#include <optional>
#include <string>
#include <utility>

namespace dimval {

namespace detail {

template <typename T>
[[nodiscard]] constexpr bool contains_value(T lo, T hi, const RangeInclusion inc, T x) noexcept {
    const bool lo_ok = (inc.lower == Bound::Inclusive) ? (x >= lo) : (x > lo);
    const bool hi_ok = (inc.upper == Bound::Inclusive) ? (x <= hi) : (x < hi);
    return lo_ok && hi_ok;
}

template <typename T>
[[nodiscard]] constexpr std::expected<std::tuple<T, T, RangeInclusion>, RangeError>
validate_range(T lo, T hi, RangeInclusion inc) noexcept {
    if (hi < lo) {
        return std::unexpected{RangeError{RangeErrorCode::MaxLessThanMin,
                                          "range upper bound is less than lower bound"}};
    }
    if (lo == hi && (inc.lower == Bound::Exclusive || inc.upper == Bound::Exclusive)) {
        return std::unexpected{RangeError{RangeErrorCode::EmptyOpenRange,
                                          "single-point range cannot have an exclusive bound"}};
    }
    return std::tuple<T, T, RangeInclusion>{lo, hi, inc};
}

}  // namespace detail

/// Closed/open interval over a UnitValue<U,T>.
template <UnitLike U, NumericValue T = double>
class UnitRangeValue {
public:
    using unit_t = U;
    using value_t = T;
    using bound_t = UnitValue<U, T>;

    constexpr UnitRangeValue() = default;

    /// Unchecked constructor — caller must guarantee min <= max and that an
    /// exclusive single-point range is not constructed.
    constexpr UnitRangeValue(bound_t lo,
                             bound_t hi,
                             const RangeInclusion inc = RangeInclusion::closed()) noexcept
        : min_(std::move(lo)), max_(std::move(hi)), inclusion_(inc) {}

    [[nodiscard]] static std::expected<UnitRangeValue, RangeError>
    make(const bound_t& lo,
         const bound_t& hi,
         RangeInclusion inc = RangeInclusion::closed()) noexcept {
        auto v = detail::validate_range<T>(lo.v, hi.v, inc);
        if (!v) {
            return std::unexpected{v.error()};
        }
        return UnitRangeValue{lo, hi, inc};
    }

    [[nodiscard]] static constexpr UnitRangeValue closed(bound_t lo, bound_t hi) noexcept {
        return UnitRangeValue{std::move(lo), std::move(hi), RangeInclusion::closed()};
    }
    [[nodiscard]] static constexpr UnitRangeValue open(bound_t lo, bound_t hi) noexcept {
        return UnitRangeValue{std::move(lo), std::move(hi), RangeInclusion::open()};
    }
    [[nodiscard]] static constexpr UnitRangeValue left_open(bound_t lo, bound_t hi) noexcept {
        return UnitRangeValue{std::move(lo), std::move(hi), RangeInclusion::left_open()};
    }
    [[nodiscard]] static constexpr UnitRangeValue right_open(bound_t lo, bound_t hi) noexcept {
        return UnitRangeValue{std::move(lo), std::move(hi), RangeInclusion::right_open()};
    }

    [[nodiscard]] constexpr bound_t min() const noexcept {
        return min_;
    }
    [[nodiscard]] constexpr bound_t max() const noexcept {
        return max_;
    }
    [[nodiscard]] constexpr RangeInclusion inclusion() const noexcept {
        return inclusion_;
    }

    [[nodiscard]] constexpr bool contains(const bound_t& x) const noexcept {
        return detail::contains_value<T>(min_.v, max_.v, inclusion_, x.v);
    }

    [[nodiscard]] constexpr bool contains(const UnitRangeValue& other) const noexcept {
        // other.min_ inside this AND other.max_ inside this, accounting for
        // each side's inclusivity vs the outer range's inclusivity.
        const bool lo_ok = bound_inside_lower(other.min_.v, other.inclusion_.lower);
        const bool hi_ok = bound_inside_upper(other.max_.v, other.inclusion_.upper);
        return lo_ok && hi_ok;
    }

    [[nodiscard]] constexpr bool overlaps(const UnitRangeValue& other) const noexcept {
        // Disjoint cases first.
        if (max_.v < other.min_.v || other.max_.v < min_.v) {
            return false;
        }
        if (max_.v == other.min_.v) {
            return inclusion_.upper == Bound::Inclusive &&
                   other.inclusion_.lower == Bound::Inclusive;
        }
        if (other.max_.v == min_.v) {
            return inclusion_.lower == Bound::Inclusive &&
                   other.inclusion_.upper == Bound::Inclusive;
        }
        return true;
    }

    [[nodiscard]] constexpr std::optional<UnitRangeValue>
    intersect(const UnitRangeValue& other) const noexcept {
        if (!overlaps(other)) {
            return std::nullopt;
        }
        bound_t lo;
        Bound lo_inc{};
        if (min_.v > other.min_.v) {
            lo = min_;
            lo_inc = inclusion_.lower;
        } else if (min_.v < other.min_.v) {
            lo = other.min_;
            lo_inc = other.inclusion_.lower;
        } else {
            lo = min_;
            lo_inc =
                (inclusion_.lower == Bound::Exclusive || other.inclusion_.lower == Bound::Exclusive)
                    ? Bound::Exclusive
                    : Bound::Inclusive;
        }
        bound_t hi;
        Bound hi_inc{};
        if (max_.v < other.max_.v) {
            hi = max_;
            hi_inc = inclusion_.upper;
        } else if (max_.v > other.max_.v) {
            hi = other.max_;
            hi_inc = other.inclusion_.upper;
        } else {
            hi = max_;
            hi_inc =
                (inclusion_.upper == Bound::Exclusive || other.inclusion_.upper == Bound::Exclusive)
                    ? Bound::Exclusive
                    : Bound::Inclusive;
        }
        return UnitRangeValue{lo, hi, RangeInclusion{lo_inc, hi_inc}};
    }

    [[nodiscard]] std::string to_string() const;
    [[nodiscard]] std::string to_formatted_string() const;

    [[nodiscard]] friend constexpr bool operator==(const UnitRangeValue&,
                                                   const UnitRangeValue&) = default;

private:
    [[nodiscard]] constexpr bool bound_inside_lower(T other_v,
                                                    const Bound other_lower) const noexcept {
        if (inclusion_.lower == Bound::Inclusive) {
            return other_v >= min_.v;
        }
        if (other_lower == Bound::Exclusive) {
            return other_v >= min_.v;
        }
        return other_v > min_.v;
    }

    [[nodiscard]] constexpr bool bound_inside_upper(T other_v,
                                                    const Bound other_upper) const noexcept {
        if (inclusion_.upper == Bound::Inclusive) {
            return other_v <= max_.v;
        }
        if (other_upper == Bound::Exclusive) {
            return other_v <= max_.v;
        }
        return other_v < max_.v;
    }

    bound_t min_{};
    bound_t max_{};
    RangeInclusion inclusion_{RangeInclusion::closed()};
};

/// Closed/open interval over a MeasureValue<M,T>.
template <MeasureLike M, NumericValue T = double>
class MeasureRangeValue {
public:
    using measure_t = M;
    using unit_t = M::base_unit_t;
    using value_t = T;
    using bound_t = MeasureValue<M, T>;

    constexpr MeasureRangeValue() = default;
    constexpr MeasureRangeValue(bound_t lo,
                                bound_t hi,
                                const RangeInclusion inc = RangeInclusion::closed()) noexcept
        : min_(std::move(lo)), max_(std::move(hi)), inclusion_(inc) {}

    [[nodiscard]] static std::expected<MeasureRangeValue, RangeError>
    make(const bound_t& lo,
         const bound_t& hi,
         RangeInclusion inc = RangeInclusion::closed()) noexcept {
        auto v = detail::validate_range<T>(lo.v, hi.v, inc);
        if (!v) {
            return std::unexpected{v.error()};
        }
        return MeasureRangeValue{lo, hi, inc};
    }

    [[nodiscard]] static constexpr MeasureRangeValue closed(bound_t lo, bound_t hi) noexcept {
        return MeasureRangeValue{std::move(lo), std::move(hi), RangeInclusion::closed()};
    }
    [[nodiscard]] static constexpr MeasureRangeValue open(bound_t lo, bound_t hi) noexcept {
        return MeasureRangeValue{std::move(lo), std::move(hi), RangeInclusion::open()};
    }
    [[nodiscard]] static constexpr MeasureRangeValue left_open(bound_t lo, bound_t hi) noexcept {
        return MeasureRangeValue{std::move(lo), std::move(hi), RangeInclusion::left_open()};
    }
    [[nodiscard]] static constexpr MeasureRangeValue right_open(bound_t lo, bound_t hi) noexcept {
        return MeasureRangeValue{std::move(lo), std::move(hi), RangeInclusion::right_open()};
    }

    [[nodiscard]] constexpr bound_t min() const noexcept {
        return min_;
    }
    [[nodiscard]] constexpr bound_t max() const noexcept {
        return max_;
    }
    [[nodiscard]] constexpr RangeInclusion inclusion() const noexcept {
        return inclusion_;
    }

    [[nodiscard]] constexpr bool contains(const bound_t& x) const noexcept {
        return detail::contains_value<T>(min_.v, max_.v, inclusion_, x.v);
    }

    [[nodiscard]] constexpr bool contains(const MeasureRangeValue& other) const noexcept {
        return as_unit_range().contains(other.as_unit_range());
    }

    [[nodiscard]] constexpr bool overlaps(const MeasureRangeValue& other) const noexcept {
        return as_unit_range().overlaps(other.as_unit_range());
    }

    [[nodiscard]] constexpr std::optional<MeasureRangeValue>
    intersect(const MeasureRangeValue& other) const noexcept {
        if (auto r = as_unit_range().intersect(other.as_unit_range())) {
            return MeasureRangeValue{
                MeasureValue<M, T>{r->min().v}, MeasureValue<M, T>{r->max().v}, r->inclusion()};
        }
        return std::nullopt;
    }

    [[nodiscard]] std::string to_string() const;
    [[nodiscard]] std::string to_formatted_string() const;

    [[nodiscard]] friend constexpr bool operator==(const MeasureRangeValue&,
                                                   const MeasureRangeValue&) = default;

private:
    [[nodiscard]] constexpr UnitRangeValue<unit_t, T> as_unit_range() const noexcept {
        return UnitRangeValue<unit_t, T>{min_.as_unit_value(), max_.as_unit_value(), inclusion_};
    }

    bound_t min_{};
    bound_t max_{};
    RangeInclusion inclusion_{RangeInclusion::closed()};
};

}  // namespace dimval
