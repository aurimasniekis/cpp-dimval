#pragma once

/// @file
/// @brief MeasureValue<M,T>: a UnitValue tagged with an additional semantic measure.

#include <dimval/core.hpp>
#include <dimval/interface.hpp>
#include <dimval/traits.hpp>
#include <dimval/unit.hpp>

#include <expected>
#include <memory>
#include <string>
#include <string_view>

namespace dimval {

/// A value carrying both a measure tag and a unit tag.
///
/// The measure refines the meaning of a value beyond its physical unit. For
/// example, `Distance` and `Length` are both stored in meters but have
/// distinct semantics. The measure's base unit is fixed at the type level.
///
/// @tparam M a measure struct that derives from MeasureBase.
/// @tparam T a numeric type. Defaults to `double`.
template <MeasureLike M, NumericValue T = double>
struct MeasureValue : public IMeasureValue {
    using measure_t = M;
    using unit_t = M::base_unit_t;
    using value_t = T;

    T v{};

    constexpr MeasureValue() = default;
    /// Implicit conversion from the numeric type — enables
    /// `DistanceValue d = 1500.0;` style construction. Safe because the
    /// measure tag type already prevents cross-measure assignments.
    constexpr MeasureValue(T value) noexcept : v(value) {}  // NOLINT(google-explicit-constructor)

    /// Heap-allocated shared-owned factory: `auto d = DistanceValue::of(1500.0);`
    /// For a stack value, just construct directly (`DistanceValue d = 1500.0`).
    [[nodiscard]] static std::shared_ptr<MeasureValue> of(T value) {
        return std::make_shared<MeasureValue>(value);
    }

    /// Heap-allocated unique-owned factory.
    [[nodiscard]] static std::unique_ptr<MeasureValue> unique(T value) {
        return std::make_unique<MeasureValue>(value);
    }

    /// Parse "100 m" → MeasureValue<M,T>. Forwards to UnitValue<base_unit_t,T>::parse.
    [[nodiscard]] static std::expected<MeasureValue, ParseError> parse(std::string_view input) {
        auto u = UnitValue<unit_t, T>::parse(input);
        if (!u)
            return std::unexpected{u.error()};
        return MeasureValue{u->v};
    }

    // Compile-time metadata accessors -----------------------------------------
    // Read straight off the measure / unit tag, no descriptor round-trip.
    [[nodiscard]] static constexpr std::string_view id() noexcept {
        return M::id;
    }
    [[nodiscard]] static constexpr std::string_view unit_id() noexcept {
        return unit_t::id;
    }
    [[nodiscard]] static constexpr std::string_view name() noexcept {
        return M::name;
    }
    [[nodiscard]] static constexpr std::string_view symbol() noexcept {
        return unit_t::symbol;
    }
    [[nodiscard]] static constexpr std::string_view kind() noexcept {
        return unit_t::kind;
    }
    [[nodiscard]] static constexpr std::string_view icon() noexcept {
        return M::icon.empty() ? unit_t::icon : M::icon;
    }
    [[nodiscard]] static constexpr std::string_view color() noexcept {
        return M::color.empty() ? unit_t::color : M::color;
    }

    /// Drop the measure tag and expose the underlying UnitValue.
    [[nodiscard]] constexpr UnitValue<unit_t, T> as_unit_value() const noexcept {
        return UnitValue<unit_t, T>{v};
    }

    // IMeasureValue overrides -------------------------------------------------
    // Only the descriptors stay virtual — per-field metadata is reachable via
    // `descriptor().name`, `unit_descriptor().symbol`, ... from a polymorphic
    // handle.
    [[nodiscard]] MeasureDescriptor descriptor() const noexcept override {
        return M::descriptor();
    }
    [[nodiscard]] UnitDescriptor unit_descriptor() const noexcept override {
        return unit_t::descriptor();
    }
    [[nodiscard]] double numeric_as_double() const noexcept override {
        return static_cast<double>(v);
    }

    [[nodiscard]] std::string to_string() const override;
    [[nodiscard]] std::string to_formatted_string() const override;

    [[nodiscard]] std::unique_ptr<IMeasureValue> clone() const override {
        return std::make_unique<MeasureValue>(*this);
    }

    [[nodiscard]] friend constexpr bool operator==(const MeasureValue& a,
                                                   const MeasureValue& b) noexcept {
        return a.v == b.v;
    }
    [[nodiscard]] friend constexpr auto operator<=>(const MeasureValue& a,
                                                    const MeasureValue& b) noexcept {
        return a.v <=> b.v;
    }

    constexpr MeasureValue& operator+=(const MeasureValue& rhs) noexcept {
        v += rhs.v;
        return *this;
    }
    constexpr MeasureValue& operator-=(const MeasureValue& rhs) noexcept {
        v -= rhs.v;
        return *this;
    }
    constexpr MeasureValue& operator*=(T s) noexcept {
        v *= s;
        return *this;
    }
    constexpr MeasureValue& operator/=(T s) noexcept {
        v /= s;
        return *this;
    }
};

template <MeasureLike M, NumericValue T>
[[nodiscard]] constexpr MeasureValue<M, T> operator+(const MeasureValue<M, T>& a,
                                                     const MeasureValue<M, T>& b) noexcept {
    return MeasureValue<M, T>{static_cast<T>(a.v + b.v)};
}

template <MeasureLike M, NumericValue T>
[[nodiscard]] constexpr MeasureValue<M, T> operator-(const MeasureValue<M, T>& a,
                                                     const MeasureValue<M, T>& b) noexcept {
    return MeasureValue<M, T>{static_cast<T>(a.v - b.v)};
}

template <MeasureLike M, NumericValue T>
[[nodiscard]] constexpr MeasureValue<M, T> operator-(const MeasureValue<M, T>& a) noexcept {
    return MeasureValue<M, T>{static_cast<T>(-a.v)};
}

template <MeasureLike M, NumericValue T>
[[nodiscard]] constexpr MeasureValue<M, T> operator+(const MeasureValue<M, T>& a) noexcept {
    return a;
}

template <MeasureLike M, NumericValue T>
[[nodiscard]] constexpr MeasureValue<M, T> operator*(const MeasureValue<M, T>& a, T s) noexcept {
    return MeasureValue<M, T>{static_cast<T>(a.v * s)};
}

template <MeasureLike M, NumericValue T>
[[nodiscard]] constexpr MeasureValue<M, T> operator*(T s, const MeasureValue<M, T>& a) noexcept {
    return MeasureValue<M, T>{static_cast<T>(a.v * s)};
}

template <MeasureLike M, NumericValue T>
[[nodiscard]] constexpr MeasureValue<M, T> operator/(const MeasureValue<M, T>& a, T s) noexcept {
    return MeasureValue<M, T>{static_cast<T>(a.v / s)};
}

template <MeasureLike M, NumericValue T>
[[nodiscard]] constexpr T operator/(const MeasureValue<M, T>& a,
                                    const MeasureValue<M, T>& b) noexcept {
    return static_cast<T>(a.v / b.v);
}

/// Wrap a UnitValue<base_unit_of<M>> as a MeasureValue<M>.
/// Compile error when the UnitValue's unit isn't M's declared base unit.
template <MeasureLike M, NumericValue T>
[[nodiscard]] constexpr MeasureValue<M, T>
from_unit_value(const UnitValue<typename M::base_unit_t, T>& u) noexcept {
    return MeasureValue<M, T>{u.v};
}

/// Sugar: produce a MeasureValue from a scalar literal.
template <MeasureLike M, NumericValue T = double>
[[nodiscard]] constexpr MeasureValue<M, T> measure_value(T v) noexcept {
    return MeasureValue<M, T>{v};
}

}  // namespace dimval
