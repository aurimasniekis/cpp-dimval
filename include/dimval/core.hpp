#pragma once

/// @file
/// @brief Common concepts, error types, and small utilities used across dimval.

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <type_traits>

namespace dimval {

/// Concept for value types stored inside a UnitValue / MeasureValue.
/// Built-in arithmetic types are supported by default.
template <typename T>
concept NumericValue = std::is_arithmetic_v<T>;

/// Error codes returned by parse_unit_value / parse_measure_value.
enum class ParseErrorCode {
    Empty,            ///< Input was empty or whitespace-only.
    InvalidNumber,    ///< Numeric portion failed to parse.
    UnknownUnit,      ///< Symbol/id not present in the registry.
    UnitMismatch,     ///< Symbol parsed but doesn't match the requested unit tag.
    MeasureMismatch,  ///< Measure id doesn't match the requested measure tag.
    TrailingGarbage   ///< Unexpected characters after the value.
};

/// Detailed error report from a parse_*_value call.
struct ParseError {
    ParseErrorCode code;
    std::string input;    ///< Copy of the original input for diagnostics.
    std::size_t pos{0};   ///< Byte position where parsing failed.
    std::string message;  ///< Optional human-readable detail.
};

/// Error codes for range construction.
enum class RangeErrorCode {
    MaxLessThanMin,  ///< Upper bound is strictly less than lower bound.
    EmptyOpenRange   ///< Equal bounds with at least one exclusive side.
};

/// Detailed error report from a UnitRangeValue::make / MeasureRangeValue::make call.
struct RangeError {
    RangeErrorCode code;
    std::string message;
};

/// Inclusivity of a single range bound.
enum class Bound : std::uint8_t {
    Inclusive,
    Exclusive,
};

/// Inclusivity of both range bounds together.
struct RangeInclusion {
    Bound lower{Bound::Inclusive};
    Bound upper{Bound::Inclusive};

    [[nodiscard]] static constexpr RangeInclusion closed() noexcept {
        return {Bound::Inclusive, Bound::Inclusive};
    }
    [[nodiscard]] static constexpr RangeInclusion open() noexcept {
        return {Bound::Exclusive, Bound::Exclusive};
    }
    [[nodiscard]] static constexpr RangeInclusion left_open() noexcept {
        return {Bound::Exclusive, Bound::Inclusive};
    }
    [[nodiscard]] static constexpr RangeInclusion right_open() noexcept {
        return {Bound::Inclusive, Bound::Exclusive};
    }

    [[nodiscard]] friend constexpr bool operator==(RangeInclusion,
                                                   RangeInclusion) noexcept = default;
};

/// Result of comparing two values or ranges.
enum class RangeCompareResult : std::int8_t {
    Less = -1,
    Equal = 0,
    Greater = 1,
    Overlapping = 2,
};

namespace detail {

/// Return a span between the first matching token and the trailing decimal/sign characters.
[[nodiscard]] constexpr std::string_view ltrim(std::string_view s) noexcept {
    while (!s.empty() && (s.front() == ' ' || s.front() == '\t')) {
        s.remove_prefix(1);
    }
    return s;
}

[[nodiscard]] constexpr std::string_view rtrim(std::string_view s) noexcept {
    while (!s.empty() && (s.back() == ' ' || s.back() == '\t')) {
        s.remove_suffix(1);
    }
    return s;
}

[[nodiscard]] constexpr std::string_view trim(const std::string_view s) noexcept {
    return rtrim(ltrim(s));
}

}  // namespace detail

}  // namespace dimval
