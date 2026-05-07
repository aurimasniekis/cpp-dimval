#pragma once

/// @file
/// @brief CRTP bases that turn unit/measure tag structs into self-describing
///        types. Each unit/measure struct inherits from UnitBase / MeasureBase
///        and publishes its metadata as `static constexpr` members; the base
///        synthesises the runtime descriptor from those members.

#include <dimval/descriptor.hpp>

#include <string_view>

namespace dimval {

/// Marker base — concept detection picks up any type that derives from this.
struct UnitTag {};

/// Marker base — concept detection picks up any type that derives from this.
struct MeasureTag {};

/// CRTP base for unit tags. `Self` must publish at least:
///     id, symbol, short_name, long_name, kind, factor
/// (as static constexpr members). Optional fields default to the values
/// declared here and may be overridden by shadowing in `Self`.
template <typename Self>
struct UnitBase : UnitTag {
    using self_t = Self;

    static constexpr double offset = 0.0;
    static constexpr std::string_view formatter = "default";
    static constexpr int default_precision = -1;
    static constexpr bool no_space_before_symbol = false;
    static constexpr std::string_view icon = {};
    static constexpr std::string_view color = {};

    [[nodiscard]] static constexpr UnitDescriptor descriptor() noexcept {
        return UnitDescriptor{
            .id = Self::id,
            .symbol = Self::symbol,
            .short_name = Self::short_name,
            .long_name = Self::long_name,
            .kind = Self::kind,
            .factor = Self::factor,
            .offset = Self::offset,
            .formatter = Self::formatter,
            .default_precision = Self::default_precision,
            .no_space_before_symbol = Self::no_space_before_symbol,
            .icon = Self::icon,
            .color = Self::color,
        };
    }
};

/// CRTP base for measure tags. `Self` must publish at least:
///     id, name
/// `BaseUnit` is the underlying unit type — its `id` becomes the measure's
/// `base_unit_id`, eliminating the duplication of the previous trait form.
template <typename Self, typename BaseUnit>
struct MeasureBase : MeasureTag {
    using self_t = Self;
    using base_unit_t = BaseUnit;

    /// Derived from the unit type — the redundant call-site string is gone.
    static constexpr std::string_view base_unit_id = BaseUnit::id;

    static constexpr std::string_view formatter = {};
    static constexpr int default_precision = -1;
    static constexpr std::string_view icon = {};
    static constexpr std::string_view color = {};

    [[nodiscard]] static constexpr MeasureDescriptor descriptor() noexcept {
        return MeasureDescriptor{
            .id = Self::id,
            .base_unit_id = BaseUnit::id,
            .name = Self::name,
            .formatter = Self::formatter,
            .default_precision = Self::default_precision,
            .icon = Self::icon,
            .color = Self::color,
        };
    }
};

}  // namespace dimval
