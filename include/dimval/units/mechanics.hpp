#pragma once

/// @file
/// @brief Mechanics units: acceleration, area, density.
///
/// Canonical SI base units per kind (`m/s²`, `m²`, `kg/m³`); plus a few
/// commonly-cited alt units that convert with a non-trivial factor.

#include <dimval/define.hpp>

// -----------------------------------------------------------------------------
// Acceleration
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_UNIT(MeterPerSecondSquared,
                   "m_per_s2",
                   "m/s²",
                   "m/s²",
                   "meter per second squared",
                   "acceleration",
                   1.0,
                   "mdi:axis-arrow",
                   ::dimval::palette::red_400,
                   static constexpr int default_precision = 3;)

// 1 g₀ = 9.80665 m/s² exactly (CGPM 1901). The id is "g0" so the bare symbol
// "g" stays free for a future Gram unit if mass-prefix aliases ever land.
DIMVAL_DEFINE_UNIT(StandardGravity,
                   "g0",
                   "g₀",
                   "g₀",
                   "standard gravity",
                   "acceleration",
                   9.80665,
                   "mdi:arrow-down-bold",
                   ::dimval::palette::red_500,
                   static constexpr int default_precision = 3;)

// -----------------------------------------------------------------------------
// Area
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_UNIT(SquareMeter,
                   "m2",
                   "m²",
                   "m²",
                   "square meter",
                   "area",
                   1.0,
                   "mdi:vector-square",
                   ::dimval::palette::green_400,
                   static constexpr int default_precision = 2;)

DIMVAL_DEFINE_UNIT(Hectare,
                   "ha",
                   "ha",
                   "ha",
                   "hectare",
                   "area",
                   1e4,
                   "mdi:vector-square",
                   ::dimval::palette::green_500,
                   static constexpr int default_precision = 2;)

// -----------------------------------------------------------------------------
// Density (mass per volume)
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_UNIT(KilogramPerCubicMeter,
                   "kg_per_m3",
                   "kg/m³",
                   "kg/m³",
                   "kilogram per cubic meter",
                   "density",
                   1.0,
                   "mdi:weight-kilogram",
                   ::dimval::palette::brown_400,
                   static constexpr int default_precision = 2;)

DIMVAL_DEFINE_UNIT(GramPerCubicCentimeter,
                   "g_per_cm3",
                   "g/cm³",
                   "g/cm³",
                   "gram per cubic centimeter",
                   "density",
                   1000.0,
                   "mdi:weight-gram",
                   ::dimval::palette::brown_500,
                   static constexpr int default_precision = 3;)
