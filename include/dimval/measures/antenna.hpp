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
                      ::comms::Icons::mdi::antenna,
                      ::comms::Colors::mui::green[400])

DIMVAL_DEFINE_MEASURE(Azimuth,
                      ::dimval::Degree,
                      "azimuth",
                      "Azimuth",
                      ::comms::Icons::mdi::compass,
                      ::comms::Colors::mui::deep_purple[400])

DIMVAL_DEFINE_MEASURE(Elevation,
                      ::dimval::Degree,
                      "elevation",
                      "Elevation",
                      ::comms::Icons::mdi::angle_acute,
                      ::comms::Colors::mui::deep_purple[400])

DIMVAL_DEFINE_MEASURE(PolarizationAngle,
                      ::dimval::Degree,
                      "polarization_angle",
                      "Polarization Angle",
                      ::comms::Icons::mdi::angle_acute,
                      ::comms::Colors::mui::deep_purple[500])

DIMVAL_DEFINE_MEASURE(WavelengthMeasure,
                      ::dimval::Wavelength,
                      "wavelength",
                      "Wavelength",
                      ::comms::Icon::from("ph:wave-sine"),
                      ::comms::Colors::mui::teal[500])

DIMVAL_DEFINE_MEASURE(Vswr,
                      ::dimval::Percent,
                      "vswr",
                      "Voltage Standing Wave Ratio",
                      ::comms::Icons::mdi::sine_wave,
                      ::comms::Colors::mui::red[400],
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(ReturnLoss,
                      ::dimval::Decibel,
                      "return_loss",
                      "Return Loss",
                      ::comms::Icons::mdi::chart_bell_curve,
                      ::comms::Colors::mui::red[400])

DIMVAL_DEFINE_MEASURE(SheetResistance,
                      ::dimval::OhmSquare,
                      "sheet_resistance",
                      "Sheet Resistance",
                      ::comms::Icons::mdi::grid,
                      ::comms::Colors::mui::brown[500])

DIMVAL_DEFINE_MEASURE(PropagationDelay,
                      ::dimval::Second,
                      "propagation_delay",
                      "Propagation Delay",
                      ::comms::Icons::mdi::timer_outline,
                      ::comms::Colors::mui::blue[400])
