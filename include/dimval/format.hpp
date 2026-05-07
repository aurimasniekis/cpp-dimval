#pragma once

/// @file
/// @brief std::formatter specializations for UnitValue, MeasureValue, ranges, and descriptors.
///
/// Supported format spec grammar:
///
///     [style][.precision]
///
/// where `style` is one of: "" (default), "short", "full", "json".
///
/// Examples:
///
///     std::format("{}",        v)   // 42.5 m
///     std::format("{:short}",  v)   // 42.5m
///     std::format("{:full}",   v)   // 42.5 meter
///     std::format("{:json}",   v)   // {"unit":"m","value":42.5}
///     std::format("{:.2}",     v)   // 42.50 m
///     std::format("{:full.3}", v)   // 42.500 meter

#include <dimval/core.hpp>
#include <dimval/descriptor.hpp>
#include <dimval/measure.hpp>
#include <dimval/range.hpp>
#include <dimval/traits.hpp>
#include <dimval/unit.hpp>

#include <cstddef>
#include <cstdint>
#include <format>
#include <string>
#include <string_view>

namespace dimval::detail {

enum class FormatStyle : std::uint8_t {
    Default,
    Short,
    Full,
    Json,
};

struct ValueFormatSpec {
    FormatStyle style{FormatStyle::Default};
    int precision{-1};  // -1 = descriptor default
};

template <typename It>
constexpr It parse_value_format_spec(It it, It end, ValueFormatSpec& spec) {
    // Parse style token first (optional).
    auto remaining_size = static_cast<std::size_t>(end - it);
    std::string_view rest{it, remaining_size};

    auto consume = [&](const std::string_view tok, const FormatStyle s) {
        if (rest.starts_with(tok)) {
            spec.style = s;
            it += static_cast<std::ptrdiff_t>(tok.size());
            rest.remove_prefix(tok.size());
            return true;
        }
        return false;
    };
    consume("default", FormatStyle::Default) || consume("short", FormatStyle::Short) ||
        consume("full", FormatStyle::Full) || consume("json", FormatStyle::Json);
    // Optional precision: ".N"
    if (it != end && *it == '.') {
        ++it;
        int p = 0;
        bool any = false;
        while (it != end && *it >= '0' && *it <= '9') {
            p = p * 10 + (*it - '0');
            any = true;
            ++it;
        }
        if (any) {
            spec.precision = p;
        }
    }
    return it;
}

template <typename T>
[[nodiscard]] std::string format_numeric(T v, int precision) {
    if (precision >= 0) {
        return std::format("{:.{}f}", static_cast<double>(v), precision);
    }
    return std::format("{}", v);
}

[[nodiscard]] inline std::string render_unit_value(const double v,
                                                   const int precision,
                                                   const UnitDescriptor& d,
                                                   const FormatStyle style) {
    const int eff_precision = precision >= 0 ? precision : d.default_precision;
    std::string num = format_numeric<double>(v, eff_precision);
    switch (style) {
    case FormatStyle::Json:
        return std::format(R"({{"unit":"{}","value":{}}})", d.id, num);
    case FormatStyle::Full:
        return std::format("{} {}", num, d.long_name);
    case FormatStyle::Short: {
        const std::string_view sym = d.short_name.empty() ? d.symbol : d.short_name;
        if (sym.empty()) {
            return num;
        }
        return std::format("{}{}", num, sym);
    }
    case FormatStyle::Default:
    default: {
        if (d.symbol.empty()) {
            return num;
        }
        if (d.no_space_before_symbol) {
            return std::format("{}{}", num, d.symbol);
        }
        return std::format("{} {}", num, d.symbol);
    }
    }
}

[[nodiscard]] inline std::string render_measure_value(const double v,
                                                      const int precision,
                                                      const MeasureDescriptor& md,
                                                      const UnitDescriptor& ud,
                                                      const FormatStyle style) {
    int eff_precision = precision;
    if (eff_precision < 0)
        eff_precision = md.default_precision;
    if (eff_precision < 0)
        eff_precision = ud.default_precision;
    std::string num = format_numeric<double>(v, eff_precision);
    switch (style) {
    case FormatStyle::Json:
        return std::format(R"({{"measure":"{}","unit":"{}","value":{}}})", md.id, ud.id, num);
    case FormatStyle::Full:
        return std::format("{} {} ({})", num, md.name, ud.long_name);
    case FormatStyle::Short: {
        const std::string_view sym = ud.short_name.empty() ? ud.symbol : ud.short_name;
        if (sym.empty()) {
            return num;
        }
        return std::format("{}{}", num, sym);
    }
    case FormatStyle::Default:
    default: {
        if (ud.symbol.empty()) {
            return num;
        }
        if (ud.no_space_before_symbol) {
            return std::format("{}{}", num, ud.symbol);
        }
        return std::format("{} {}", num, ud.symbol);
    }
    }
}

[[nodiscard]] inline char open_bracket(const Bound b) noexcept {
    return b == Bound::Inclusive ? '[' : '(';
}

[[nodiscard]] inline char close_bracket(const Bound b) noexcept {
    return b == Bound::Inclusive ? ']' : ')';
}

}  // namespace dimval::detail

template <dimval::UnitLike U, dimval::NumericValue T>
struct std::formatter<dimval::UnitValue<U, T>> {
    dimval::detail::ValueFormatSpec spec_{};

    constexpr auto parse(const std::format_parse_context& ctx) {
        const auto* it = dimval::detail::parse_value_format_spec(ctx.begin(), ctx.end(), spec_);
        if (it != ctx.end() && *it != '}') {
            throw std::format_error{"dimval::UnitValue: invalid format spec"};
        }
        return it;
    }

    template <typename FormatContext>
    auto format(const dimval::UnitValue<U, T>& v, FormatContext& ctx) const {
        const auto d = U::descriptor();
        const auto s = dimval::detail::render_unit_value(
            static_cast<double>(v.v), spec_.precision, d, spec_.style);
        return std::ranges::copy(s, ctx.out()).out;
    }
};

template <dimval::MeasureLike M, dimval::NumericValue T>
struct std::formatter<dimval::MeasureValue<M, T>> {
    dimval::detail::ValueFormatSpec spec_{};

    constexpr auto parse(const std::format_parse_context& ctx) {
        const auto* it = dimval::detail::parse_value_format_spec(ctx.begin(), ctx.end(), spec_);
        if (it != ctx.end() && *it != '}') {
            throw std::format_error{"dimval::MeasureValue: invalid format spec"};
        }
        return it;
    }

    template <typename FormatContext>
    auto format(const dimval::MeasureValue<M, T>& v, FormatContext& ctx) const {
        const auto md = M::descriptor();
        using unit_t = M::base_unit_t;
        const auto ud = unit_t::descriptor();
        const auto s = dimval::detail::render_measure_value(
            static_cast<double>(v.v), spec_.precision, md, ud, spec_.style);
        return std::ranges::copy(s, ctx.out()).out;
    }
};

template <dimval::UnitLike U, dimval::NumericValue T>
struct std::formatter<dimval::UnitRangeValue<U, T>> {
    dimval::detail::ValueFormatSpec spec_{};

    constexpr auto parse(const std::format_parse_context& ctx) {
        const auto* it = dimval::detail::parse_value_format_spec(ctx.begin(), ctx.end(), spec_);
        if (it != ctx.end() && *it != '}') {
            throw std::format_error{"dimval::UnitRangeValue: invalid format spec"};
        }
        return it;
    }

    template <typename FormatContext>
    auto format(const dimval::UnitRangeValue<U, T>& r, FormatContext& ctx) const {
        const auto d = U::descriptor();
        if (spec_.style == dimval::detail::FormatStyle::Json) {
            const auto out = std::format(
                R"({{"unit":"{}","min":{},"max":{},"min_inclusive":{},"max_inclusive":{}}})",
                d.id,
                dimval::detail::format_numeric<double>(static_cast<double>(r.min().v),
                                                       spec_.precision),
                dimval::detail::format_numeric<double>(static_cast<double>(r.max().v),
                                                       spec_.precision),
                r.inclusion().lower == dimval::Bound::Inclusive ? "true" : "false",
                r.inclusion().upper == dimval::Bound::Inclusive ? "true" : "false");
            return std::ranges::copy(out, ctx.out()).out;
        }
        const auto lo = dimval::detail::render_unit_value(
            static_cast<double>(r.min().v), spec_.precision, d, spec_.style);
        const auto hi = dimval::detail::render_unit_value(
            static_cast<double>(r.max().v), spec_.precision, d, spec_.style);
        const auto out = std::format("{}{}, {}{}",
                                     dimval::detail::open_bracket(r.inclusion().lower),
                                     lo,
                                     hi,
                                     dimval::detail::close_bracket(r.inclusion().upper));
        return std::ranges::copy(out, ctx.out()).out;
    }
};

template <dimval::MeasureLike M, dimval::NumericValue T>
struct std::formatter<dimval::MeasureRangeValue<M, T>> {
    dimval::detail::ValueFormatSpec spec_{};

    constexpr auto parse(const std::format_parse_context& ctx) {
        const auto* it = dimval::detail::parse_value_format_spec(ctx.begin(), ctx.end(), spec_);
        if (it != ctx.end() && *it != '}') {
            throw std::format_error{"dimval::MeasureRangeValue: invalid format spec"};
        }
        return it;
    }

    template <typename FormatContext>
    auto format(const dimval::MeasureRangeValue<M, T>& r, FormatContext& ctx) const {
        const auto md = M::descriptor();
        using unit_t = M::base_unit_t;
        const auto ud = unit_t::descriptor();
        if (spec_.style == dimval::detail::FormatStyle::Json) {
            const auto out =
                std::format(R"({{"measure":"{}","unit":"{}","min":{},"max":{},)"
                            R"("min_inclusive":{},"max_inclusive":{}}})",
                            md.id,
                            ud.id,
                            dimval::detail::format_numeric<double>(static_cast<double>(r.min().v),
                                                                   spec_.precision),
                            dimval::detail::format_numeric<double>(static_cast<double>(r.max().v),
                                                                   spec_.precision),
                            r.inclusion().lower == dimval::Bound::Inclusive ? "true" : "false",
                            r.inclusion().upper == dimval::Bound::Inclusive ? "true" : "false");
            return std::ranges::copy(out, ctx.out()).out;
        }
        const auto lo = dimval::detail::render_measure_value(
            static_cast<double>(r.min().v), spec_.precision, md, ud, spec_.style);
        const auto hi = dimval::detail::render_measure_value(
            static_cast<double>(r.max().v), spec_.precision, md, ud, spec_.style);
        const auto out = std::format("{}{}, {}{}",
                                     dimval::detail::open_bracket(r.inclusion().lower),
                                     lo,
                                     hi,
                                     dimval::detail::close_bracket(r.inclusion().upper));
        return std::ranges::copy(out, ctx.out()).out;
    }
};

template <>
struct std::formatter<dimval::UnitDescriptor> {
    static constexpr auto parse(const std::format_parse_context& ctx) {
        const auto* it = ctx.begin();
        if (it != ctx.end() && *it != '}') {
            throw std::format_error{"dimval::UnitDescriptor: invalid format spec"};
        }
        return it;
    }
    template <typename FormatContext>
    static auto format(const dimval::UnitDescriptor& d, FormatContext& ctx) {
        const auto out =
            std::format("UnitDescriptor{{id={}, symbol={}, kind={}, factor={}, offset={}}}",
                        d.id,
                        d.symbol,
                        d.kind,
                        d.factor,
                        d.offset);
        return std::ranges::copy(out, ctx.out()).out;
    }
};

template <>
struct std::formatter<dimval::MeasureDescriptor> {
    static constexpr auto parse(const std::format_parse_context& ctx) {
        const auto* it = ctx.begin();
        if (it != ctx.end() && *it != '}') {
            throw std::format_error{"dimval::MeasureDescriptor: invalid format spec"};
        }
        return it;
    }
    template <typename FormatContext>
    static auto format(const dimval::MeasureDescriptor& d, FormatContext& ctx) {
        const auto out = std::format(
            "MeasureDescriptor{{id={}, base_unit={}, name={}}}", d.id, d.base_unit_id, d.name);
        return std::ranges::copy(out, ctx.out()).out;
    }
};

// Out-of-line implementations of the IUnitValue / IMeasureValue overrides that
// need to call std::format. Defining them here breaks the otherwise circular
// dependency between unit.hpp / measure.hpp and the formatter specs above.
namespace dimval {

template <UnitLike U, NumericValue T>
inline std::string UnitValue<U, T>::to_string() const {
    return std::format("{}", *this);
}

template <UnitLike U, NumericValue T>
inline std::string UnitValue<U, T>::to_formatted_string() const {
    return std::format("{}", *this);
}

template <MeasureLike M, NumericValue T>
inline std::string MeasureValue<M, T>::to_string() const {
    return std::format("{}", *this);
}

template <MeasureLike M, NumericValue T>
inline std::string MeasureValue<M, T>::to_formatted_string() const {
    return std::format("{}", *this);
}

template <UnitLike U, NumericValue T>
inline std::string UnitRangeValue<U, T>::to_string() const {
    return std::format("{}", *this);
}

template <UnitLike U, NumericValue T>
inline std::string UnitRangeValue<U, T>::to_formatted_string() const {
    return std::format("{}", *this);
}

template <MeasureLike M, NumericValue T>
inline std::string MeasureRangeValue<M, T>::to_string() const {
    return std::format("{}", *this);
}

template <MeasureLike M, NumericValue T>
inline std::string MeasureRangeValue<M, T>::to_formatted_string() const {
    return std::format("{}", *this);
}

}  // namespace dimval
