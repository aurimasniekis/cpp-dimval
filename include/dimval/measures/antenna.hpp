#pragma once

/// @file
/// @brief Antenna / propagation measures.

#include <dimval/define.hpp>
#include <dimval/units/dimensionless.hpp>
#include <dimval/units/practical.hpp>
#include <dimval/units/rf.hpp>
#include <dimval/units/si.hpp>

DIMVAL_DEFINE_MEASURE(AntennaGain,
                      ::dimval::Decibel,
                      "antenna_gain",
                      "Antenna Gain",
                      "mdi:antenna",
                      ::dimval::palette::green_400)

DIMVAL_DEFINE_MEASURE(Azimuth,
                      ::dimval::Degree,
                      "azimuth",
                      "Azimuth",
                      "mdi:compass",
                      ::dimval::palette::deep_purple_400)

DIMVAL_DEFINE_MEASURE(Elevation,
                      ::dimval::Degree,
                      "elevation",
                      "Elevation",
                      "mdi:angle-acute",
                      ::dimval::palette::deep_purple_400)

DIMVAL_DEFINE_MEASURE(PolarizationAngle,
                      ::dimval::Degree,
                      "polarization_angle",
                      "Polarization Angle",
                      "mdi:angle-acute",
                      ::dimval::palette::deep_purple_500)

DIMVAL_DEFINE_MEASURE(WavelengthMeasure,
                      ::dimval::Wavelength,
                      "wavelength",
                      "Wavelength",
                      "ph:wave-sine",
                      ::dimval::palette::teal_500)

DIMVAL_DEFINE_MEASURE(Vswr,
                      ::dimval::Percent,
                      "vswr",
                      "Voltage Standing Wave Ratio",
                      "mdi:sine-wave",
                      ::dimval::palette::red_400,
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(ReturnLoss,
                      ::dimval::Decibel,
                      "return_loss",
                      "Return Loss",
                      "mdi:chart-bell-curve",
                      ::dimval::palette::red_400)

DIMVAL_DEFINE_MEASURE(SheetResistance,
                      ::dimval::OhmSquare,
                      "sheet_resistance",
                      "Sheet Resistance",
                      "mdi:grid",
                      ::dimval::palette::brown_500)

DIMVAL_DEFINE_MEASURE(PropagationDelay,
                      ::dimval::Second,
                      "propagation_delay",
                      "Propagation Delay",
                      "mdi:timer-outline",
                      ::dimval::palette::blue_400)
