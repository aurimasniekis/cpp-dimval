#pragma once

/// @file
/// @brief RF / SDR measures.

#include <dimval/define.hpp>
#include <dimval/units/dimensionless.hpp>
#include <dimval/units/practical.hpp>
#include <dimval/units/rf.hpp>
#include <dimval/units/si.hpp>

// -----------------------------------------------------------------------------
// Frequency-related
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_MEASURE(CenterFrequency,
                      ::dimval::Hertz,
                      "center_frequency",
                      "Center Frequency",
                      ::comms::Icon::from("ph:wave-sine"),
                      ::comms::Colors::mui::light_blue[400])

DIMVAL_DEFINE_MEASURE(SampleRate,
                      ::dimval::Hertz,
                      "sample_rate",
                      "Sample Rate",
                      ::comms::Icons::mdi::chart_timeline_variant,
                      ::comms::Colors::mui::light_blue[500])

DIMVAL_DEFINE_MEASURE(SymbolRate,
                      ::dimval::Hertz,
                      "symbol_rate",
                      "Symbol Rate",
                      ::comms::Icons::mdi::chart_bell_curve,
                      ::comms::Colors::mui::light_blue[600])

DIMVAL_DEFINE_MEASURE(Bandwidth,
                      ::dimval::Hertz,
                      "bandwidth",
                      "Bandwidth",
                      ::comms::Icons::mdi::arrow_expand_horizontal,
                      ::comms::Colors::mui::light_blue[300])

DIMVAL_DEFINE_MEASURE(IntermediateFrequency,
                      ::dimval::Hertz,
                      "intermediate_frequency",
                      "Intermediate Frequency",
                      ::comms::Icon::from("ph:wave-sine"),
                      ::comms::Colors::mui::light_blue[700])

// -----------------------------------------------------------------------------
// Power / signal level
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_MEASURE(RfPower,
                      ::dimval::Watt,
                      "rf_power",
                      "RF Power",
                      ::comms::Icons::mdi::signal,
                      ::comms::Colors::mui::deep_orange[400])

DIMVAL_DEFINE_MEASURE(RfPowerDbm,
                      ::dimval::DecibelMilliwatt,
                      "rf_power_dbm",
                      "RF Power Level",
                      ::comms::Icons::mdi::signal,
                      ::comms::Colors::mui::deep_orange[500])

DIMVAL_DEFINE_MEASURE(RfPowerDbw,
                      ::dimval::DecibelWatt,
                      "rf_power_dbw",
                      "RF Power Level",
                      ::comms::Icons::mdi::signal,
                      ::comms::Colors::mui::deep_orange[600])

DIMVAL_DEFINE_MEASURE(SignalLevelDbuv,
                      ::dimval::DecibelMicrovolt,
                      "signal_level_dbuv",
                      "Signal Level",
                      ::comms::Icons::mdi::signal,
                      ::comms::Colors::mui::deep_orange[300])

DIMVAL_DEFINE_MEASURE(SignalLevelDbmv,
                      ::dimval::DecibelMillivolt,
                      "signal_level_dbmv",
                      "Signal Level",
                      ::comms::Icons::mdi::signal,
                      ::comms::Colors::mui::deep_orange[200])

// -----------------------------------------------------------------------------
// Gain / loss / quality
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_MEASURE(Gain,
                      ::dimval::Decibel,
                      "gain",
                      "Gain",
                      ::comms::Icons::mdi::chart_bell_curve,
                      ::comms::Colors::mui::green[400])

DIMVAL_DEFINE_MEASURE(Loss,
                      ::dimval::Decibel,
                      "loss",
                      "Loss",
                      ::comms::Icons::mdi::chart_bell_curve,
                      ::comms::Colors::mui::red[400])

DIMVAL_DEFINE_MEASURE(PathLoss,
                      ::dimval::Decibel,
                      "path_loss",
                      "Path Loss",
                      ::comms::Icons::mdi::chart_bell_curve,
                      ::comms::Colors::mui::red[400])

DIMVAL_DEFINE_MEASURE(Snr,
                      ::dimval::Decibel,
                      "snr",
                      "Signal-to-Noise Ratio",
                      ::comms::Icons::mdi::chart_bell_curve,
                      ::comms::Colors::mui::green[400])

DIMVAL_DEFINE_MEASURE(Cnr,
                      ::dimval::Decibel,
                      "cnr",
                      "Carrier-to-Noise Ratio",
                      ::comms::Icons::mdi::chart_bell_curve,
                      ::comms::Colors::mui::green[400])

DIMVAL_DEFINE_MEASURE(EbNo,
                      ::dimval::Decibel,
                      "eb_no",
                      "Energy per Bit to Noise Density Ratio",
                      ::comms::Icons::mdi::chart_bell_curve,
                      ::comms::Colors::mui::green[500])

DIMVAL_DEFINE_MEASURE(Mer,
                      ::dimval::Decibel,
                      "mer",
                      "Modulation Error Ratio",
                      ::comms::Icons::mdi::chart_bell_curve,
                      ::comms::Colors::mui::green[400])

DIMVAL_DEFINE_MEASURE(EvmPercent,
                      ::dimval::Percent,
                      "evm_percent",
                      "Error Vector Magnitude",
                      ::comms::Icons::mdi::percent,
                      ::comms::Colors::mui::red[400],
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(EvmDb,
                      ::dimval::Decibel,
                      "evm_db",
                      "Error Vector Magnitude",
                      ::comms::Icons::mdi::percent,
                      ::comms::Colors::mui::red[400])

// -----------------------------------------------------------------------------
// Phase / IQ
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_MEASURE(Phase,
                      ::dimval::PhaseDegree,
                      "phase",
                      "Phase",
                      ::comms::Icons::mdi::angle_acute,
                      ::comms::Colors::mui::deep_purple[400])

DIMVAL_DEFINE_MEASURE(PhaseRadians,
                      ::dimval::PhaseRadian,
                      "phase_radians",
                      "Phase",
                      ::comms::Icons::mdi::angle_acute,
                      ::comms::Colors::mui::deep_purple[500])

DIMVAL_DEFINE_MEASURE(IqImbalanceGain,
                      ::dimval::Decibel,
                      "iq_imbalance_gain",
                      "IQ Gain Imbalance",
                      ::comms::Icons::mdi::sine_wave,
                      ::comms::Colors::mui::green[600])

DIMVAL_DEFINE_MEASURE(IqImbalancePhase,
                      ::dimval::PhaseDegree,
                      "iq_imbalance_phase",
                      "IQ Phase Imbalance",
                      ::comms::Icons::mdi::sine_wave,
                      ::comms::Colors::mui::deep_purple[600])

// -----------------------------------------------------------------------------
// Frequency error / stability / drift
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_MEASURE(FrequencyErrorHz,
                      ::dimval::Hertz,
                      "frequency_error_hz",
                      "Frequency Error",
                      ::comms::Icons::mdi::tune_variant,
                      ::comms::Colors::mui::red[400])

DIMVAL_DEFINE_MEASURE(FrequencyErrorPpm,
                      ::dimval::PartsPerMillion,
                      "frequency_error_ppm",
                      "Frequency Error",
                      ::comms::Icons::mdi::tune_variant,
                      ::comms::Colors::mui::red[400])

DIMVAL_DEFINE_MEASURE(FrequencyStabilityPpb,
                      ::dimval::PartsPerBillion,
                      "frequency_stability_ppb",
                      "Frequency Stability",
                      ::comms::Icons::mdi::tune,
                      ::comms::Colors::mui::cyan[400])

DIMVAL_DEFINE_MEASURE(ClockDrift,
                      ::dimval::SecondsPerDay,
                      "clock_drift",
                      "Clock Drift",
                      ::comms::Icons::mdi::clock_alert_outline,
                      ::comms::Colors::mui::blue[400])

// -----------------------------------------------------------------------------
// Spectral / noise density
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_MEASURE(NoiseDensityVoltage,
                      ::dimval::VoltPerRootHertz,
                      "noise_density_voltage",
                      "Voltage Noise Density",
                      ::comms::Icons::mdi::chart_line,
                      ::comms::Colors::mui::cyan[400])

DIMVAL_DEFINE_MEASURE(NoiseDensityCurrent,
                      ::dimval::AmperePerRootHertz,
                      "noise_density_current",
                      "Current Noise Density",
                      ::comms::Icons::mdi::chart_line,
                      ::comms::Colors::mui::cyan[500])

DIMVAL_DEFINE_MEASURE(PowerSpectralDensity,
                      ::dimval::WattPerHertz,
                      "power_spectral_density",
                      "Power Spectral Density",
                      ::comms::Icons::mdi::chart_line,
                      ::comms::Colors::mui::cyan[600])

DIMVAL_DEFINE_MEASURE(NoiseDensityDb,
                      ::dimval::DecibelPerHertz,
                      "noise_density_db",
                      "Noise Density",
                      ::comms::Icons::mdi::chart_line,
                      ::comms::Colors::mui::cyan[700])
