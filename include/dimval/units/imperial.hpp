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
                   "tabler:ruler",
                   ::dimval::palette::teal_300,
                   static constexpr int default_precision = 2;)

DIMVAL_DEFINE_UNIT(Foot,
                   "ft",
                   "ft",
                   "ft",
                   "foot",
                   "length",
                   0.3048,
                   "tabler:ruler",
                   ::dimval::palette::teal_400,
                   static constexpr int default_precision = 2;)

DIMVAL_DEFINE_UNIT(Mile,
                   "mi",
                   "mi",
                   "mi",
                   "mile",
                   "length",
                   1609.344,
                   "mdi:map-marker-distance",
                   ::dimval::palette::teal_500,
                   static constexpr int default_precision = 2;)

DIMVAL_DEFINE_UNIT(NauticalMile,
                   "nmi",
                   "nmi",
                   "nmi",
                   "nautical mile",
                   "length",
                   1852.0,
                   "mdi:sail-boat",
                   ::dimval::palette::teal_600,
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
                   "mdi:weight-pound",
                   ::dimval::palette::blue_grey_300,
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
                   "ph:gauge",
                   ::dimval::palette::blue_grey_400,
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
                   "mdi:gas-station",
                   ::dimval::palette::blue_grey_300,
                   static constexpr int default_precision = 2;)
