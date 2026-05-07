#pragma once

/// @file
/// @brief std::ostream operator<< for all value types — delegates to std::format.

#include <dimval/format.hpp>
#include <dimval/measure.hpp>
#include <dimval/range.hpp>
#include <dimval/traits.hpp>
#include <dimval/unit.hpp>

#include <format>
#include <ostream>

namespace dimval {

template <UnitLike U, NumericValue T>
inline std::ostream& operator<<(std::ostream& os, const UnitValue<U, T>& v) {
    return os << std::format("{}", v);
}

template <MeasureLike M, NumericValue T>
inline std::ostream& operator<<(std::ostream& os, const MeasureValue<M, T>& v) {
    return os << std::format("{}", v);
}

template <UnitLike U, NumericValue T>
inline std::ostream& operator<<(std::ostream& os, const UnitRangeValue<U, T>& r) {
    return os << std::format("{}", r);
}

template <MeasureLike M, NumericValue T>
inline std::ostream& operator<<(std::ostream& os, const MeasureRangeValue<M, T>& r) {
    return os << std::format("{}", r);
}

inline std::ostream& operator<<(std::ostream& os, const UnitDescriptor& d) {
    return os << std::format("{}", d);
}

inline std::ostream& operator<<(std::ostream& os, const MeasureDescriptor& d) {
    return os << std::format("{}", d);
}

}  // namespace dimval
