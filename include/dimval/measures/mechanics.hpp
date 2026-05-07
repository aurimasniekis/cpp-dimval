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
                      "mdi:speedometer",
                      ::dimval::palette::light_green_400)

DIMVAL_DEFINE_MEASURE(Acceleration,
                      ::dimval::MeterPerSecondSquared,
                      "acceleration",
                      "Acceleration",
                      "mdi:axis-arrow",
                      ::dimval::palette::red_400)

DIMVAL_DEFINE_MEASURE(
    Area, ::dimval::SquareMeter, "area", "Area", "mdi:vector-square", ::dimval::palette::green_400)

DIMVAL_DEFINE_MEASURE(Density,
                      ::dimval::KilogramPerCubicMeter,
                      "density",
                      "Density",
                      "mdi:weight-kilogram",
                      ::dimval::palette::brown_400)

DIMVAL_DEFINE_MEASURE(Volume,
                      ::dimval::Litre,
                      "volume",
                      "Volume",
                      "mdi:water-outline",
                      ::dimval::palette::blue_grey_400)

DIMVAL_DEFINE_MEASURE(Pressure,
                      ::dimval::Pascal,
                      "pressure",
                      "Pressure",
                      "ph:gauge",
                      ::dimval::palette::blue_grey_500)

DIMVAL_DEFINE_MEASURE(Force,
                      ::dimval::Newton,
                      "force",
                      "Force",
                      "mdi:arrow-right-bold",
                      ::dimval::palette::blue_grey_500)
