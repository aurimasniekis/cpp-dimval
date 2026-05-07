#pragma once

/// @file
/// @brief Common, domain-agnostic measures.

#include <dimval/define.hpp>
#include <dimval/units/data.hpp>
#include <dimval/units/dimensionless.hpp>
#include <dimval/units/rate.hpp>
#include <dimval/units/si.hpp>

// -----------------------------------------------------------------------------
// Geometry / dimensions
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_MEASURE(
    Length, ::dimval::Meter, "length", "Length", "tabler:ruler", ::dimval::palette::teal_400)
DIMVAL_DEFINE_MEASURE(
    Width, ::dimval::Meter, "width", "Width", "tabler:ruler", ::dimval::palette::teal_400)
DIMVAL_DEFINE_MEASURE(
    Height, ::dimval::Meter, "height", "Height", "tabler:ruler", ::dimval::palette::teal_400)
DIMVAL_DEFINE_MEASURE(
    Depth, ::dimval::Meter, "depth", "Depth", "tabler:ruler", ::dimval::palette::teal_400)
DIMVAL_DEFINE_MEASURE(
    Distance, ::dimval::Meter, "distance", "Distance", "tabler:ruler", ::dimval::palette::teal_400)

// -----------------------------------------------------------------------------
// Mass / weight
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_MEASURE(
    Mass, ::dimval::Kilogram, "mass", "Mass", "mdi:weight", ::dimval::palette::blue_grey_400)
DIMVAL_DEFINE_MEASURE(
    Weight, ::dimval::Kilogram, "weight", "Weight", "mdi:weight", ::dimval::palette::blue_grey_500)

// -----------------------------------------------------------------------------
// Time
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_MEASURE(
    Duration, ::dimval::Second, "duration", "Duration", "ph:clock", ::dimval::palette::blue_400)
DIMVAL_DEFINE_MEASURE(ElapsedTime,
                      ::dimval::Second,
                      "elapsed_time",
                      "Elapsed time",
                      "mdi:clock-outline",
                      ::dimval::palette::blue_400)
DIMVAL_DEFINE_MEASURE(
    Time, ::dimval::Second, "time", "Time", "ph:clock", ::dimval::palette::blue_400)

// -----------------------------------------------------------------------------
// Data size / capacity
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_MEASURE(
    Size, ::dimval::Byte, "size", "Size", "mdi:memory", ::dimval::palette::cyan_500)
DIMVAL_DEFINE_MEASURE(
    Capacity, ::dimval::Byte, "capacity", "Capacity", "mdi:memory", ::dimval::palette::cyan_500)

DIMVAL_DEFINE_MEASURE(Throughput,
                      ::dimval::BytePerSecond,
                      "throughput",
                      "Throughput",
                      "mdi:transfer",
                      ::dimval::palette::cyan_500)

// -----------------------------------------------------------------------------
// Frequency / temperature / dimensionless
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_MEASURE(Frequency,
                      ::dimval::Hertz,
                      "frequency",
                      "Frequency",
                      "ph:wave-sine",
                      ::dimval::palette::light_blue_400)

DIMVAL_DEFINE_MEASURE(Temperature,
                      ::dimval::Celsius,
                      "temperature",
                      "Temperature",
                      "mdi:thermometer-lines",
                      ::dimval::palette::orange_400)
DIMVAL_DEFINE_MEASURE(TemperatureKelvin,
                      ::dimval::Kelvin,
                      "temperature_kelvin",
                      "Thermodynamic Temperature",
                      "ph:thermometer-light",
                      ::dimval::palette::orange_400)

DIMVAL_DEFINE_MEASURE(Percentage,
                      ::dimval::Ratio,
                      "percentage",
                      "Percentage",
                      "mdi:percent",
                      ::dimval::palette::grey_400)

DIMVAL_DEFINE_MEASURE(
    CountMeasure, ::dimval::Count, "count", "Count", "mdi:counter", ::dimval::palette::grey_400)

DIMVAL_DEFINE_MEASURE(RatioMeasure,
                      ::dimval::Ratio,
                      "ratio",
                      "Ratio",
                      "mdi:percent-outline",
                      ::dimval::palette::grey_400)

DIMVAL_DEFINE_MEASURE(Angle,
                      ::dimval::Radian,
                      "angle",
                      "Angle",
                      "mdi:angle-obtuse",
                      ::dimval::palette::deep_purple_400)
