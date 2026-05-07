#pragma once

/// @file
/// @brief Low-level parsing primitives shared by parse.hpp and the inline
///        UnitValue::parse / MeasureValue::parse static methods.

#include <dimval/core.hpp>

#include <cerrno>
#include <charconv>
#include <expected>
#include <string>
#include <string_view>
#include <system_error>
#include <type_traits>

namespace dimval::detail {

/// Split "<number><whitespace><tail>" into (number string, tail).
struct SplitResult {
    std::string_view number;
    std::string_view tail;
    std::size_t number_end{0};  ///< index in original input where the number ended
};

[[nodiscard]] inline std::expected<SplitResult, ParseError>
split_number_and_tail(std::string_view s) {
    const auto orig = s;
    s = trim(s);
    if (s.empty()) {
        return std::unexpected{
            ParseError{ParseErrorCode::Empty, std::string{orig}, 0, "empty input"}};
    }
    // Find the end of the numeric portion. Allow sign, digits, '.', exponent.
    std::size_t i = 0;
    if (i < s.size() && (s[i] == '+' || s[i] == '-')) {
        ++i;
    }
    bool seen_digit = false;
    while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
        ++i;
        seen_digit = true;
    }
    if (i < s.size() && s[i] == '.') {
        ++i;
        while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
            ++i;
            seen_digit = true;
        }
    }
    if (i < s.size() && (s[i] == 'e' || s[i] == 'E')) {
        ++i;
        if (i < s.size() && (s[i] == '+' || s[i] == '-')) {
            ++i;
        }
        while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
            ++i;
        }
    }
    if (!seen_digit) {
        return std::unexpected{
            ParseError{ParseErrorCode::InvalidNumber, std::string{orig}, 0, "no digits in input"}};
    }
    SplitResult out;
    out.number = s.substr(0, i);
    out.tail = trim(s.substr(i));
    out.number_end = i;
    return out;
}

template <typename T>
[[nodiscard]] inline std::expected<T, ParseError> parse_number(const std::string_view num,
                                                               const std::string_view orig_input) {
    if constexpr (std::is_integral_v<T>) {
        T out{};
        const auto* const first = num.data();
        const auto* const last = first + num.size();
        if (auto res = std::from_chars(first, last, out);
            res.ec != std::errc{} || res.ptr != last) {
            return std::unexpected{ParseError{ParseErrorCode::InvalidNumber,
                                              std::string{orig_input},
                                              0,
                                              "failed to parse number"}};
        }
        return out;
    } else {
        // libc++ on macOS gates std::from_chars for floating-point on
        // macOS 26.0+; fall back to strtod for portability. Copy into a
        // null-terminated buffer so strtod sees a clean boundary.
        const std::string buf{num};
        char* endp = nullptr;
        errno = 0;
        const double d = std::strtod(buf.c_str(), &endp);
        if (endp != buf.c_str() + buf.size() || errno != 0) {
            return std::unexpected{ParseError{ParseErrorCode::InvalidNumber,
                                              std::string{orig_input},
                                              0,
                                              "failed to parse number"}};
        }
        return static_cast<T>(d);
    }
}

}  // namespace dimval::detail
