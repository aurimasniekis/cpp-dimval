#pragma once

/// @file
/// @brief Mechanics measures: speed, acceleration, area, density, plus
///        re-anchored measures over canonical SI base units (volume,
///        pressure, force).

#include <dimval/define.hpp>
#include <dimval/units/mechanics.hpp>
#include <dimval/units/practical.hpp>
#include <dimval/units/si.hpp>

DIMVAL_DEFINE_MEASURE(Speed,
                      ::dimval::MeterPerSecond,
                      "speed",
                      "Speed",
                      ::comms::Icons::mdi::speedometer,
                      ::comms::Colors::mui::light_green[400])

DIMVAL_DEFINE_MEASURE(Acceleration,
                      ::dimval::MeterPerSecondSquared,
                      "acceleration",
                      "Acceleration",
                      ::comms::Icons::mdi::axis_arrow,
                      ::comms::Colors::mui::red[400])

DIMVAL_DEFINE_MEASURE(Area,
                      ::dimval::SquareMeter,
                      "area",
                      "Area",
                      ::comms::Icons::mdi::vector_square,
                      ::comms::Colors::mui::green[400])

DIMVAL_DEFINE_MEASURE(Density,
                      ::dimval::KilogramPerCubicMeter,
                      "density",
                      "Density",
                      ::comms::Icons::mdi::weight_kilogram,
                      ::comms::Colors::mui::brown[400])

DIMVAL_DEFINE_MEASURE(Volume,
                      ::dimval::Litre,
                      "volume",
                      "Volume",
                      ::comms::Icons::mdi::water_outline,
                      ::comms::Colors::mui::blue_grey[400])

DIMVAL_DEFINE_MEASURE(Pressure,
                      ::dimval::Pascal,
                      "pressure",
                      "Pressure",
                      ::comms::Icon::from("ph:gauge"),
                      ::comms::Colors::mui::blue_grey[500])

DIMVAL_DEFINE_MEASURE(Force,
                      ::dimval::Newton,
                      "force",
                      "Force",
                      ::comms::Icons::mdi::arrow_right_bold,
                      ::comms::Colors::mui::blue_grey[500])
