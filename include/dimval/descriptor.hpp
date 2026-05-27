#pragma once

/// @file
/// @brief Runtime metadata structs for units and measures.

#include <commons/color.hpp>
#include <commons/icon.hpp>

#include <optional>
#include <string_view>

namespace dimval {

namespace detail {
/// Field types for the optional UI metadata. The DIMVAL_DEFINE_* macros refer
/// to these aliases rather than spelling `comms::Icon` / `comms::Color`
/// directly: those macros take parameters literally named `Icon` and `Color`,
/// which would otherwise be token-substituted inside the type name.
using icon_field_t = std::optional<comms::Icon>;
using color_field_t = std::optional<comms::Color>;
}  // namespace detail

/// Runtime metadata for a unit.
///
/// All string_views are expected to refer to storage that outlives any
/// registration. For built-in units this is satisfied because the strings are
/// literals; for runtime-registered descriptors (see UnitRegistry) the caller
/// must guarantee the lifetime.
struct UnitDescriptor {
    std::string_view id;          ///< Stable identifier (e.g. "m"). Unique per registry.
    std::string_view symbol;      ///< Display symbol (e.g. "m"). Often equal to id.
    std::string_view short_name;  ///< Short human-readable name (e.g. "m").
    std::string_view long_name;   ///< Full human-readable name (e.g. "meter").
    std::string_view
        kind;            ///< Compatibility group (e.g. "length"). Two units convert if kinds match.
    double factor{1.0};  ///< Linear conversion: canonical = factor * v + offset.
    double offset{0.0};  ///< Additive offset for affine conversions (e.g. Celsius/Kelvin).
    std::string_view formatter{"default"};  ///< Formatter id; consumed by std::formatter.
    int default_precision{-1};              ///< Default numeric precision; -1 = unset.
    bool no_space_before_symbol{false};     ///< Render flush, e.g. "100%" instead of "100 %".
    // The {} default member initializers silence -Wmissing-designated-field-initializers
    // at aggregate-init sites that omit these optional fields; the NOLINT suppresses the
    // resulting redundant-member-init tidy warning (same trade-off as `formatter` below).
    std::optional<comms::Icon> icon{};  ///< NOLINT(readability-redundant-member-init)
                                        ///< Optional UI icon (Iconify `set:name`); nullopt = unset.
    std::optional<comms::Color> color{};  ///< NOLINT(readability-redundant-member-init)
                                          ///< Optional UI accent (RGBA); nullopt = unset.

    [[nodiscard]] friend constexpr bool operator==(const UnitDescriptor&,
                                                   const UnitDescriptor&) noexcept = default;
};

/// Runtime metadata for a measure (a semantic specialization of a unit).
struct MeasureDescriptor {
    std::string_view id;            ///< Stable identifier (e.g. "distance"). Unique per registry.
    std::string_view base_unit_id;  ///< Id of the unit this measure is defined in (e.g. "m").
    std::string_view name;          ///< Human-readable name (e.g. "Distance").
    std::string_view formatter{};   ///< NOLINT(readability-redundant-member-init)
                                    ///< Empty falls back to the base unit's formatter.
    int default_precision{-1};      ///< Empty falls back to the base unit's precision.
    std::optional<comms::Icon>
        icon{};  ///< NOLINT(readability-redundant-member-init)
                 ///< Optional UI icon; nullopt falls back to the unit's icon.
    std::optional<comms::Color>
        color{};  ///< NOLINT(readability-redundant-member-init)
                  ///< Optional UI accent; nullopt falls back to the unit's color.

    [[nodiscard]] friend constexpr bool operator==(const MeasureDescriptor&,
                                                   const MeasureDescriptor&) noexcept = default;
};

}  // namespace dimval
