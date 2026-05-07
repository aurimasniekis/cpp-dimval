#pragma once

/// @file
/// @brief Macros that expand into a CRTP unit/measure struct and a runtime
///        auto-registration for it.
///
/// Each unit/measure is its own struct that derives from UnitBase /
/// MeasureBase and publishes its metadata as static constexpr members. The
/// macro arguments fill in those members; optional fields fall through to
/// the defaults declared on UnitBase / MeasureBase unless overridden via
/// __VA_ARGS__.
///
/// Usage from outside the library (custom user units):
/// @code
///   #include <dimval/dimval.hpp>
///
///   DIMVAL_DEFINE_UNIT(Frame, "frame", "frm", "frm", "frame", "count", 1.0,
///                      "mdi:movie-roll", ::dimval::palette::blue_400)
///
///   DIMVAL_DEFINE_MEASURE(FrameCount, ::dimval::Frame,
///                         "frame_count", "Frame count",
///                         "mdi:movie-roll", ::dimval::palette::blue_400)
/// @endcode
///
/// Optional fields (offset, formatter, default_precision, no_space_before_symbol)
/// can be supplied as additional macro arguments after the required ones —
/// each one is a `static constexpr` member declaration that shadows the
/// inherited default:
/// @code
///   DIMVAL_DEFINE_UNIT(Celsius, "degC", "°C", "°C", "degree Celsius",
///                      "temperature", 1.0,
///                      "mdi:thermometer-lines", ::dimval::palette::orange_400,
///                      static constexpr double offset = 273.15;
///                      static constexpr int default_precision = 1;)
/// @endcode
///
/// All macros open `namespace dimval` internally. The structs they produce
/// therefore live in `::dimval`.

#include <dimval/base.hpp>
#include <dimval/measure.hpp>
#include <dimval/palette.hpp>
#include <dimval/registry.hpp>
#include <dimval/unit.hpp>

#define DIMVAL_DETAIL_CAT2(a, b) a##b
#define DIMVAL_DETAIL_CAT(a, b) DIMVAL_DETAIL_CAT2(a, b)

/// Define a unit struct in ::dimval and auto-register its descriptor at
/// static-init time. `Tag` is the unqualified identifier (also used to name
/// the auto-registrar). `Id`, `Symbol`, `ShortName`, `LongName`, `Kind`, `Icon`,
/// `Color` are string literals (or palette constants); `Factor` is a double.
/// `__VA_ARGS__` is an optional list of `static constexpr` member declarations
/// that shadow the defaults declared on UnitBase.
#define DIMVAL_DEFINE_UNIT(Tag, Id, Symbol, ShortName, LongName, Kind, Factor, Icon, Color, ...)   \
    namespace dimval {                                                                             \
    struct Tag : ::dimval::UnitBase<Tag> {                                                         \
        static constexpr ::std::string_view id = Id;                                               \
        static constexpr ::std::string_view symbol = Symbol;                                       \
        static constexpr ::std::string_view short_name = ShortName;                                \
        static constexpr ::std::string_view long_name = LongName;                                  \
        static constexpr ::std::string_view kind = Kind;                                           \
        static constexpr double factor = Factor;                                                   \
        static constexpr ::std::string_view icon = Icon;                                           \
        static constexpr ::std::string_view color = Color;                                         \
        __VA_ARGS__                                                                                \
    };                                                                                             \
    using DIMVAL_DETAIL_CAT(Tag, Value) = ::dimval::UnitValue<Tag>;                                \
    using DIMVAL_DETAIL_CAT(Tag, ValueUnique) = ::std::unique_ptr<DIMVAL_DETAIL_CAT(Tag, Value)>;  \
    using DIMVAL_DETAIL_CAT(Tag, ValueShared) = ::std::shared_ptr<DIMVAL_DETAIL_CAT(Tag, Value)>;  \
    using DIMVAL_DETAIL_CAT(Tag, RangeValue) = ::dimval::UnitRangeValue<Tag>;                      \
    }                                                                                              \
    namespace dimval::detail {                                                                     \
    [[maybe_unused]] inline const int DIMVAL_DETAIL_CAT(_dimval_unit_reg_, Tag) =                  \
        ::dimval::detail::register_unit_tag<::dimval::Tag>();                                      \
    }

/// Define a measure struct in ::dimval and auto-register its descriptor.
/// `BaseUnit` is the underlying unit type (must be UnitLike).
/// `Icon` and `Color` shadow the unit's defaults; leave empty (`""`) to
/// inherit from the base unit.
/// `__VA_ARGS__` is an optional list of `static constexpr` member declarations
/// that shadow the defaults declared on MeasureBase (e.g. `default_precision`,
/// `formatter`).
#define DIMVAL_DEFINE_MEASURE(Tag, BaseUnit, Id, Name, Icon, Color, ...)                           \
    namespace dimval {                                                                             \
    struct Tag : ::dimval::MeasureBase<Tag, BaseUnit> {                                            \
        static constexpr ::std::string_view id = Id;                                               \
        static constexpr ::std::string_view name = Name;                                           \
        static constexpr ::std::string_view icon = Icon;                                           \
        static constexpr ::std::string_view color = Color;                                         \
        __VA_ARGS__                                                                                \
    };                                                                                             \
    using DIMVAL_DETAIL_CAT(Tag, Value) = ::dimval::MeasureValue<Tag>;                             \
    using DIMVAL_DETAIL_CAT(Tag, ValueUnique) = ::std::unique_ptr<DIMVAL_DETAIL_CAT(Tag, Value)>;  \
    using DIMVAL_DETAIL_CAT(Tag, ValueShared) = ::std::shared_ptr<DIMVAL_DETAIL_CAT(Tag, Value)>;  \
    using DIMVAL_DETAIL_CAT(Tag, RangeValue) = ::dimval::MeasureRangeValue<Tag>;                   \
    }                                                                                              \
    namespace dimval::detail {                                                                     \
    [[maybe_unused]] inline const int DIMVAL_DETAIL_CAT(_dimval_measure_reg_, Tag) =               \
        ::dimval::detail::register_measure_tag<::dimval::Tag>();                                   \
    }
