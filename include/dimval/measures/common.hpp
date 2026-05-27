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

DIMVAL_DEFINE_MEASURE(Length,
                      ::dimval::Meter,
                      "length",
                      "Length",
                      ::comms::Icon::from("tabler:ruler"),
                      ::comms::Colors::mui::teal[400])
DIMVAL_DEFINE_MEASURE(Width,
                      ::dimval::Meter,
                      "width",
                      "Width",
                      ::comms::Icon::from("tabler:ruler"),
                      ::comms::Colors::mui::teal[400])
DIMVAL_DEFINE_MEASURE(Height,
                      ::dimval::Meter,
                      "height",
                      "Height",
                      ::comms::Icon::from("tabler:ruler"),
                      ::comms::Colors::mui::teal[400])
DIMVAL_DEFINE_MEASURE(Depth,
                      ::dimval::Meter,
                      "depth",
                      "Depth",
                      ::comms::Icon::from("tabler:ruler"),
                      ::comms::Colors::mui::teal[400])
DIMVAL_DEFINE_MEASURE(Distance,
                      ::dimval::Meter,
                      "distance",
                      "Distance",
                      ::comms::Icon::from("tabler:ruler"),
                      ::comms::Colors::mui::teal[400])

// -----------------------------------------------------------------------------
// Mass / weight
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_MEASURE(Mass,
                      ::dimval::Kilogram,
                      "mass",
                      "Mass",
                      ::comms::Icons::mdi::weight,
                      ::comms::Colors::mui::blue_grey[400])
DIMVAL_DEFINE_MEASURE(Weight,
                      ::dimval::Kilogram,
                      "weight",
                      "Weight",
                      ::comms::Icons::mdi::weight,
                      ::comms::Colors::mui::blue_grey[500])

// -----------------------------------------------------------------------------
// Time
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_MEASURE(Duration,
                      ::dimval::Second,
                      "duration",
                      "Duration",
                      ::comms::Icon::from("ph:clock"),
                      ::comms::Colors::mui::blue[400])
DIMVAL_DEFINE_MEASURE(ElapsedTime,
                      ::dimval::Second,
                      "elapsed_time",
                      "Elapsed time",
                      ::comms::Icons::mdi::clock_outline,
                      ::comms::Colors::mui::blue[400])
DIMVAL_DEFINE_MEASURE(Time,
                      ::dimval::Second,
                      "time",
                      "Time",
                      ::comms::Icon::from("ph:clock"),
                      ::comms::Colors::mui::blue[400])

// -----------------------------------------------------------------------------
// Data size / capacity
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_MEASURE(Size,
                      ::dimval::Byte,
                      "size",
                      "Size",
                      ::comms::Icons::mdi::memory,
                      ::comms::Colors::mui::cyan[500])
DIMVAL_DEFINE_MEASURE(Capacity,
                      ::dimval::Byte,
                      "capacity",
                      "Capacity",
                      ::comms::Icons::mdi::memory,
                      ::comms::Colors::mui::cyan[500])

DIMVAL_DEFINE_MEASURE(Throughput,
                      ::dimval::BytePerSecond,
                      "throughput",
                      "Throughput",
                      ::comms::Icons::mdi::transfer,
                      ::comms::Colors::mui::cyan[500])

// -----------------------------------------------------------------------------
// Frequency / temperature / dimensionless
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_MEASURE(Frequency,
                      ::dimval::Hertz,
                      "frequency",
                      "Frequency",
                      ::comms::Icon::from("ph:wave-sine"),
                      ::comms::Colors::mui::light_blue[400])

DIMVAL_DEFINE_MEASURE(Temperature,
                      ::dimval::Celsius,
                      "temperature",
                      "Temperature",
                      ::comms::Icons::mdi::thermometer_lines,
                      ::comms::Colors::mui::orange[400])
DIMVAL_DEFINE_MEASURE(TemperatureKelvin,
                      ::dimval::Kelvin,
                      "temperature_kelvin",
                      "Thermodynamic Temperature",
                      ::comms::Icon::from("ph:thermometer-light"),
                      ::comms::Colors::mui::orange[400])

DIMVAL_DEFINE_MEASURE(Percentage,
                      ::dimval::Ratio,
                      "percentage",
                      "Percentage",
                      ::comms::Icons::mdi::percent,
                      ::comms::Colors::mui::grey[400])

DIMVAL_DEFINE_MEASURE(CountMeasure,
                      ::dimval::Count,
                      "count",
                      "Count",
                      ::comms::Icons::mdi::counter,
                      ::comms::Colors::mui::grey[400])

DIMVAL_DEFINE_MEASURE(RatioMeasure,
                      ::dimval::Ratio,
                      "ratio",
                      "Ratio",
                      ::comms::Icons::mdi::percent_outline,
                      ::comms::Colors::mui::grey[400])

DIMVAL_DEFINE_MEASURE(Angle,
                      ::dimval::Radian,
                      "angle",
                      "Angle",
                      ::comms::Icons::mdi::angle_obtuse,
                      ::comms::Colors::mui::deep_purple[400])
