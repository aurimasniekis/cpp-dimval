#pragma once

/// @file
/// @brief RF / SDR units — logarithmic ratios (dB family + Neper), phase
///        angle alternates, spectral density units, and sheet resistance.

#include <dimval/define.hpp>

// -----------------------------------------------------------------------------
// Logarithmic ratio units
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_UNIT(Decibel,
                   "dB",
                   "dB",
                   "dB",
                   "decibel",
                   "log_ratio",
                   1.0,
                   ::comms::Icons::mdi::chart_bell_curve,
                   ::comms::Colors::mui::green[400],
                   static constexpr ::std::string_view formatter = "decibel";
                   static constexpr int default_precision = 2;)

// 1 Np = 20/ln(10) dB ≈ 8.685889638 dB. Same kind as Decibel.
DIMVAL_DEFINE_UNIT(Neper,
                   "Np",
                   "Np",
                   "Np",
                   "neper",
                   "log_ratio",
                   8.685889638065035,
                   ::comms::Icons::mdi::chart_bell_curve,
                   ::comms::Colors::mui::green[500],
                   static constexpr int default_precision = 2;)

DIMVAL_DEFINE_UNIT(DecibelMilliwatt,
                   "dBm",
                   "dBm",
                   "dBm",
                   "decibel-milliwatt",
                   "log_power",
                   1.0,
                   ::comms::Icons::mdi::signal,
                   ::comms::Colors::mui::green[400],
                   static constexpr ::std::string_view formatter = "decibel";
                   static constexpr int default_precision = 2;)

DIMVAL_DEFINE_UNIT(DecibelWatt,
                   "dBW",
                   "dBW",
                   "dBW",
                   "decibel-watt",
                   "log_power",
                   1.0,
                   ::comms::Icons::mdi::signal,
                   ::comms::Colors::mui::green[400],
                   static constexpr double offset = 30.0;  // dBW + 30 = dBm.
                   static constexpr ::std::string_view formatter = "decibel";
                   static constexpr int default_precision = 2;)

DIMVAL_DEFINE_UNIT(DecibelMicrovolt,
                   "dBuV",
                   "dBµV",
                   "dBµV",
                   "decibel-microvolt",
                   "log_voltage",
                   1.0,
                   ::comms::Icons::mdi::signal,
                   ::comms::Colors::mui::green[400],
                   static constexpr ::std::string_view formatter = "decibel";
                   static constexpr int default_precision = 2;)

DIMVAL_DEFINE_UNIT(DecibelMillivolt,
                   "dBmV",
                   "dBmV",
                   "dBmV",
                   "decibel-millivolt",
                   "log_voltage",
                   1.0,
                   ::comms::Icons::mdi::signal,
                   ::comms::Colors::mui::green[400],
                   static constexpr double offset = -60.0;  // dBmV - 60 = dBµV.
                   static constexpr ::std::string_view formatter = "decibel";
                   static constexpr int default_precision = 2;)

// -----------------------------------------------------------------------------
// Phase angle alternates (canonical: PhaseRadian; same kind as Radian/Degree)
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_UNIT(PhaseDegree,
                   "phase_deg",
                   "°",
                   "°",
                   "phase degree",
                   "angle",
                   0.017453292519943295,
                   ::comms::Icons::mdi::angle_acute,
                   ::comms::Colors::mui::deep_purple[400],
                   static constexpr ::std::string_view formatter = "degree";
                   static constexpr int default_precision = 2;
                   static constexpr bool no_space_before_symbol = true;)

DIMVAL_DEFINE_UNIT(PhaseRadian,
                   "phase_rad",
                   "rad",
                   "rad",
                   "phase radian",
                   "angle",
                   1.0,
                   ::comms::Icons::mdi::angle_acute,
                   ::comms::Colors::mui::deep_purple[500],
                   static constexpr int default_precision = 4;)

// -----------------------------------------------------------------------------
// Sheet resistance
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_UNIT(OhmSquare,
                   "ohm_sq",
                   "Ω/□",
                   "Ω/□",
                   "ohms per square",
                   "sheet_resistance",
                   1.0,
                   ::comms::Icons::mdi::grid,
                   ::comms::Colors::mui::brown[500])

// -----------------------------------------------------------------------------
// Spectral density / noise units
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_UNIT(VoltPerRootHertz,
                   "v_per_sqrt_hz",
                   "V/√Hz",
                   "V/√Hz",
                   "volt per root hertz",
                   "voltage_noise_density",
                   1.0,
                   ::comms::Icons::mdi::chart_line,
                   ::comms::Colors::mui::cyan[400])

DIMVAL_DEFINE_UNIT(AmperePerRootHertz,
                   "a_per_sqrt_hz",
                   "A/√Hz",
                   "A/√Hz",
                   "ampere per root hertz",
                   "current_noise_density",
                   1.0,
                   ::comms::Icons::mdi::chart_line,
                   ::comms::Colors::mui::cyan[500])

DIMVAL_DEFINE_UNIT(WattPerHertz,
                   "w_per_hz",
                   "W/Hz",
                   "W/Hz",
                   "watt per hertz",
                   "power_spectral_density",
                   1.0,
                   ::comms::Icons::mdi::chart_line,
                   ::comms::Colors::mui::cyan[600])

DIMVAL_DEFINE_UNIT(DecibelPerHertz,
                   "db_per_hz",
                   "dB/Hz",
                   "dB/Hz",
                   "decibel per hertz",
                   "noise_density_db",
                   1.0,
                   ::comms::Icons::mdi::chart_line,
                   ::comms::Colors::mui::cyan[700],
                   static constexpr int default_precision = 2;)
