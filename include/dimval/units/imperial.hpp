#pragma once

/// @file
/// @brief Imperial / US customary units that interconvert with SI through
///        a non-trivial factor.
///
/// All units share the SI canonical kind (`length`, `mass`, `pressure`,
/// `volume`), so e.g. `convert<Inch>(MeterValue{1})` works out of the box
/// via the existing kind-match rule in `units_compatible<>`. Where a name
/// is ambiguous (e.g. `Gallon`), this file declares the US variant; UK
/// imperial counterparts are deferred to a future release.

#include <dimval/define.hpp>

// -----------------------------------------------------------------------------
// Length
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_UNIT(Inch,
                   "in",
                   "in",
                   "in",
                   "inch",
                   "length",
                   0.0254,
                   ::comms::Icon::from("tabler:ruler"),
                   ::comms::Colors::mui::teal[300],
                   static constexpr int default_precision = 2;)

DIMVAL_DEFINE_UNIT(Foot,
                   "ft",
                   "ft",
                   "ft",
                   "foot",
                   "length",
                   0.3048,
                   ::comms::Icon::from("tabler:ruler"),
                   ::comms::Colors::mui::teal[400],
                   static constexpr int default_precision = 2;)

DIMVAL_DEFINE_UNIT(Mile,
                   "mi",
                   "mi",
                   "mi",
                   "mile",
                   "length",
                   1609.344,
                   ::comms::Icons::mdi::map_marker_distance,
                   ::comms::Colors::mui::teal[500],
                   static constexpr int default_precision = 2;)

DIMVAL_DEFINE_UNIT(NauticalMile,
                   "nmi",
                   "nmi",
                   "nmi",
                   "nautical mile",
                   "length",
                   1852.0,
                   ::comms::Icons::mdi::sail_boat,
                   ::comms::Colors::mui::teal[600],
                   static constexpr int default_precision = 2;)

// -----------------------------------------------------------------------------
// Mass
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_UNIT(Pound,
                   "lb",
                   "lb",
                   "lb",
                   "pound",
                   "mass",
                   0.45359237,
                   ::comms::Icons::mdi::weight_pound,
                   ::comms::Colors::mui::blue_grey[300],
                   static constexpr int default_precision = 2;)

// -----------------------------------------------------------------------------
// Pressure
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_UNIT(PoundsPerSquareInch,
                   "psi",
                   "psi",
                   "psi",
                   "pound per square inch",
                   "pressure",
                   6894.757293168,
                   ::comms::Icon::from("ph:gauge"),
                   ::comms::Colors::mui::blue_grey[400],
                   static constexpr int default_precision = 2;)

// -----------------------------------------------------------------------------
// Volume
// -----------------------------------------------------------------------------

// US liquid gallon (3.785411784 L exactly). UK imperial gallon is a different
// 4.54609 L unit; that variant is intentionally postponed to v0.2.
DIMVAL_DEFINE_UNIT(Gallon,
                   "gal",
                   "gal",
                   "gal",
                   "US liquid gallon",
                   "volume",
                   3.785411784,
                   ::comms::Icons::mdi::gas_station,
                   ::comms::Colors::mui::blue_grey[300],
                   static constexpr int default_precision = 2;)
