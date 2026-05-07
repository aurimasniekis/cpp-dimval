#pragma once

/// @file
/// @brief Parse string literals like "42.5 m" into UnitValue / MeasureValue.

#include <dimval/core.hpp>
#include <dimval/measure.hpp>
#include <dimval/parse_detail.hpp>
#include <dimval/registry.hpp>
#include <dimval/traits.hpp>
#include <dimval/unit.hpp>

#include <expected>
#include <string>
#include <string_view>

namespace dimval {

/// Type-erased dynamic parse result. Use parse_unit_value when the unit is
/// known at compile time.
struct DynamicUnitValue {
    const UnitDescriptor* desc{};
    double value{};
};

/// Parse a string of the form `"42.5 m"` into a UnitValue<U,T>. Thin forward
/// to `UnitValue<U,T>::parse` so this free-function form stays available.
template <UnitLike U, NumericValue T = double>
[[nodiscard]] std::expected<UnitValue<U, T>, ParseError> parse_unit_value(std::string_view input) {
    return UnitValue<U, T>::parse(input);
}

/// Parse a string of the form `"42.5 m"` into a MeasureValue<M,T>. Thin
/// forward to `MeasureValue<M,T>::parse`.
template <MeasureLike M, NumericValue T = double>
[[nodiscard]] std::expected<MeasureValue<M, T>, ParseError>
parse_measure_value(std::string_view input) {
    return MeasureValue<M, T>::parse(input);
}

/// Parse a string of the form `"42.5 m"` against the runtime registry. Returns
/// a `(descriptor*, value)` pair. Useful when the target unit isn't known at
/// compile time (e.g. parsing config files with arbitrary user units).
[[nodiscard]] inline std::expected<DynamicUnitValue, ParseError>
parse_dynamic_unit_value(std::string_view input) {
    auto split = detail::split_number_and_tail(input);
    if (!split) {
        return std::unexpected{split.error()};
    }
    auto num = detail::parse_number<double>(split->number, input);
    if (!num) {
        return std::unexpected{num.error()};
    }
    if (split->tail.empty()) {
        // Interpret as dimensionless.
        const auto* d = UnitRegistry::global().find("dimensionless");
        if (d == nullptr) {
            return std::unexpected{
                ParseError{ParseErrorCode::UnknownUnit,
                           std::string{input},
                           split->number_end,
                           "no symbol given and 'dimensionless' is not registered"}};
        }
        return DynamicUnitValue{d, *num};
    }
    const auto* d = UnitRegistry::global().find(split->tail);
    if (d == nullptr) {
        return std::unexpected{
            ParseError{ParseErrorCode::UnknownUnit,
                       std::string{input},
                       split->number_end,
                       std::string{"unknown unit symbol: "} + std::string{split->tail}}};
    }
    return DynamicUnitValue{d, *num};
}

}  // namespace dimval
