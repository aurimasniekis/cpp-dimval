#pragma once

/// @file
/// @brief UnitValue<U,T>: a strongly-typed value carrying a compile-time unit tag.
///
/// `UnitValue<U,T>` inherits from `IUnitValue` so it can be stored in a
/// polymorphic container (`std::unique_ptr<IUnitValue>`, etc.). The vtable
/// adds 8 bytes per instance; arithmetic itself remains constexpr.

#include <dimval/core.hpp>
#include <dimval/interface.hpp>
#include <dimval/parse_detail.hpp>
#include <dimval/traits.hpp>

#include <expected>
#include <memory>
#include <string>
#include <string_view>
#include <type_traits>

namespace dimval {

/// A value paired at the type level with a unit tag.
///
/// @tparam U a unit struct that derives from UnitBase (see DIMVAL_DEFINE_UNIT).
/// @tparam T a numeric type. Defaults to `double`.
///
/// Operators are restricted to same-unit + scalar to prevent silent mixing of
/// incompatible quantities. Use `dimval::convert<ToUnit>(v)` to bridge between
/// units of the same kind.
template <UnitLike U, NumericValue T = double>
struct UnitValue : public IUnitValue {
    using unit_t = U;
    using value_t = T;

    T v{};

    constexpr UnitValue() = default;
    /// Implicit conversion from the numeric type — enables
    /// `MeterValue distance = 1.78;` style construction. Safe because the
    /// unit tag type already prevents cross-unit assignments.
    constexpr UnitValue(T value) noexcept : v(value) {}  // NOLINT(google-explicit-constructor)

    /// Heap-allocated shared-owned factory: `auto p = MeterValue::of(1.78);`
    /// For a stack value, just construct directly (`MeterValue v = 1.78`).
    [[nodiscard]] static std::shared_ptr<UnitValue> of(T value) {
        return std::make_shared<UnitValue>(value);
    }

    /// Heap-allocated unique-owned factory: `auto p = MeterValue::unique(1.78);`
    [[nodiscard]] static std::unique_ptr<UnitValue> unique(T value) {
        return std::make_unique<UnitValue>(value);
    }

    /// Parse "42.5 m" → UnitValue<U,T>. The trailing symbol must match the
    /// unit's id, symbol, or short_name; otherwise returns
    /// ParseErrorCode::UnitMismatch. Mirrors `dimval::parse_unit_value<U,T>`.
    [[nodiscard]] static std::expected<UnitValue, ParseError> parse(const std::string_view input) {
        auto split = detail::split_number_and_tail(input);
        if (!split)
            return std::unexpected{split.error()};
        auto num = detail::parse_number<T>(split->number, input);
        if (!num)
            return std::unexpected{num.error()};
        constexpr auto d = U::descriptor();
        const std::string_view tail = split->tail;
        if (tail.empty() && d.symbol.empty())
            return UnitValue{*num};
        if (tail == d.id || tail == d.symbol || tail == d.short_name)
            return UnitValue{*num};
        return std::unexpected{ParseError{ParseErrorCode::UnitMismatch,
                                          std::string{input},
                                          split->number_end,
                                          std::string{"expected '"} + std::string{d.symbol} +
                                              "', got '" + std::string{tail} + "'"}};
    }

    // Compile-time metadata accessors -----------------------------------------
    // Read straight off the unit tag, no descriptor round-trip. Callable as
    // `MeterValue::id()` (zero-cost, constexpr) or `v.id()` on a concrete
    // instance — both reach the same static.
    [[nodiscard]] static constexpr std::string_view id() noexcept {
        return U::id;
    }
    [[nodiscard]] static constexpr std::string_view symbol() noexcept {
        return U::symbol;
    }
    [[nodiscard]] static constexpr std::string_view short_name() noexcept {
        return U::short_name;
    }
    [[nodiscard]] static constexpr std::string_view kind() noexcept {
        return U::kind;
    }
    [[nodiscard]] static constexpr std::string_view long_name() noexcept {
        return U::long_name;
    }
    [[nodiscard]] static constexpr std::string_view icon() noexcept {
        return U::icon;
    }
    [[nodiscard]] static constexpr std::string_view color() noexcept {
        return U::color;
    }

    // IUnitValue overrides ----------------------------------------------------
    // The descriptor is the only metadata accessor that must be virtual (so
    // polymorphic readers can introspect a `unique_ptr<IUnitValue>`). Per-field
    // metadata is reachable via `descriptor().id`, `descriptor().symbol`, ....
    [[nodiscard]] UnitDescriptor descriptor() const noexcept override {
        return U::descriptor();
    }
    [[nodiscard]] double numeric_as_double() const noexcept override {
        return static_cast<double>(v);
    }

    // Out-of-line definitions live in <dimval/format.hpp>.
    [[nodiscard]] std::string to_string() const override;
    [[nodiscard]] std::string to_formatted_string() const override;

    [[nodiscard]] std::unique_ptr<IUnitValue> clone() const override {
        return std::make_unique<UnitValue>(*this);
    }

    // Comparison: empty IUnitValue base + value member ------------------------
    [[nodiscard]] friend constexpr bool operator==(const UnitValue& a,
                                                   const UnitValue& b) noexcept {
        return a.v == b.v;
    }
    [[nodiscard]] friend constexpr auto operator<=>(const UnitValue& a,
                                                    const UnitValue& b) noexcept {
        return a.v <=> b.v;
    }

    constexpr UnitValue& operator+=(const UnitValue& rhs) noexcept {
        v += rhs.v;
        return *this;
    }
    constexpr UnitValue& operator-=(const UnitValue& rhs) noexcept {
        v -= rhs.v;
        return *this;
    }
    constexpr UnitValue& operator*=(T s) noexcept {
        v *= s;
        return *this;
    }
    constexpr UnitValue& operator/=(T s) noexcept {
        v /= s;
        return *this;
    }
};

template <UnitLike U, NumericValue T>
[[nodiscard]] constexpr UnitValue<U, T> operator+(const UnitValue<U, T>& a,
                                                  const UnitValue<U, T>& b) noexcept {
    return UnitValue<U, T>{static_cast<T>(a.v + b.v)};
}

template <UnitLike U, NumericValue T>
[[nodiscard]] constexpr UnitValue<U, T> operator-(const UnitValue<U, T>& a,
                                                  const UnitValue<U, T>& b) noexcept {
    return UnitValue<U, T>{static_cast<T>(a.v - b.v)};
}

template <UnitLike U, NumericValue T>
[[nodiscard]] constexpr UnitValue<U, T> operator-(const UnitValue<U, T>& a) noexcept {
    return UnitValue<U, T>{static_cast<T>(-a.v)};
}

template <UnitLike U, NumericValue T>
[[nodiscard]] constexpr UnitValue<U, T> operator+(const UnitValue<U, T>& a) noexcept {
    return a;
}

template <UnitLike U, NumericValue T>
[[nodiscard]] constexpr UnitValue<U, T> operator*(const UnitValue<U, T>& a, T s) noexcept {
    return UnitValue<U, T>{static_cast<T>(a.v * s)};
}

template <UnitLike U, NumericValue T>
[[nodiscard]] constexpr UnitValue<U, T> operator*(T s, const UnitValue<U, T>& a) noexcept {
    return UnitValue<U, T>{static_cast<T>(a.v * s)};
}

template <UnitLike U, NumericValue T>
[[nodiscard]] constexpr UnitValue<U, T> operator/(const UnitValue<U, T>& a, T s) noexcept {
    return UnitValue<U, T>{static_cast<T>(a.v / s)};
}

/// Dimensionless ratio of two same-unit values.
template <UnitLike U, NumericValue T>
[[nodiscard]] constexpr T operator/(const UnitValue<U, T>& a, const UnitValue<U, T>& b) noexcept {
    return static_cast<T>(a.v / b.v);
}

/// Convert a UnitValue between units of the same kind.
/// Compile error when From and To live in different kinds.
template <UnitLike To, UnitLike From, NumericValue T>
[[nodiscard]] constexpr UnitValue<To, T> convert(const UnitValue<From, T>& v) noexcept {
    static_assert(units_compatible<From, To>(),
                  "dimval::convert: source and destination units have different kinds");
    constexpr auto from_d = From::descriptor();
    constexpr auto to_d = To::descriptor();
    if constexpr (std::is_same_v<From, To>) {
        return v;
    } else {
        // canonical = factor * v + offset; v_to = (canonical - offset_to) / factor_to.
        const auto canonical = static_cast<double>(v.v) * from_d.factor + from_d.offset;
        const auto out = (canonical - to_d.offset) / to_d.factor;
        return UnitValue<To, T>{static_cast<T>(out)};
    }
}

/// Sugar: produce a UnitValue from a scalar literal.
template <UnitLike U, NumericValue T = double>
[[nodiscard]] constexpr UnitValue<U, T> unit_value(T v) noexcept {
    return UnitValue<U, T>{v};
}

}  // namespace dimval
