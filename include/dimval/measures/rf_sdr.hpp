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
                      "ph:wave-sine",
                      ::dimval::palette::light_blue_400)

DIMVAL_DEFINE_MEASURE(SampleRate,
                      ::dimval::Hertz,
                      "sample_rate",
                      "Sample Rate",
                      "mdi:chart-timeline-variant",
                      ::dimval::palette::light_blue_500)

DIMVAL_DEFINE_MEASURE(SymbolRate,
                      ::dimval::Hertz,
                      "symbol_rate",
                      "Symbol Rate",
                      "mdi:chart-bell-curve",
                      ::dimval::palette::light_blue_600)

DIMVAL_DEFINE_MEASURE(Bandwidth,
                      ::dimval::Hertz,
                      "bandwidth",
                      "Bandwidth",
                      "mdi:arrow-expand-horizontal",
                      ::dimval::palette::light_blue_300)

DIMVAL_DEFINE_MEASURE(IntermediateFrequency,
                      ::dimval::Hertz,
                      "intermediate_frequency",
                      "Intermediate Frequency",
                      "ph:wave-sine",
                      ::dimval::palette::light_blue_700)

// -----------------------------------------------------------------------------
// Power / signal level
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_MEASURE(RfPower,
                      ::dimval::Watt,
                      "rf_power",
                      "RF Power",
                      "mdi:signal",
                      ::dimval::palette::deep_orange_400)

DIMVAL_DEFINE_MEASURE(RfPowerDbm,
                      ::dimval::DecibelMilliwatt,
                      "rf_power_dbm",
                      "RF Power Level",
                      "mdi:signal",
                      ::dimval::palette::deep_orange_500)

DIMVAL_DEFINE_MEASURE(RfPowerDbw,
                      ::dimval::DecibelWatt,
                      "rf_power_dbw",
                      "RF Power Level",
                      "mdi:signal",
                      ::dimval::palette::deep_orange_600)

DIMVAL_DEFINE_MEASURE(SignalLevelDbuv,
                      ::dimval::DecibelMicrovolt,
                      "signal_level_dbuv",
                      "Signal Level",
                      "mdi:signal",
                      ::dimval::palette::deep_orange_300)

DIMVAL_DEFINE_MEASURE(SignalLevelDbmv,
                      ::dimval::DecibelMillivolt,
                      "signal_level_dbmv",
                      "Signal Level",
                      "mdi:signal",
                      ::dimval::palette::deep_orange_200)

// -----------------------------------------------------------------------------
// Gain / loss / quality
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_MEASURE(
    Gain, ::dimval::Decibel, "gain", "Gain", "mdi:chart-bell-curve", ::dimval::palette::green_400)

DIMVAL_DEFINE_MEASURE(
    Loss, ::dimval::Decibel, "loss", "Loss", "mdi:chart-bell-curve", ::dimval::palette::red_400)

DIMVAL_DEFINE_MEASURE(PathLoss,
                      ::dimval::Decibel,
                      "path_loss",
                      "Path Loss",
                      "mdi:chart-bell-curve",
                      ::dimval::palette::red_400)

DIMVAL_DEFINE_MEASURE(Snr,
                      ::dimval::Decibel,
                      "snr",
                      "Signal-to-Noise Ratio",
                      "mdi:chart-bell-curve",
                      ::dimval::palette::green_400)

DIMVAL_DEFINE_MEASURE(Cnr,
                      ::dimval::Decibel,
                      "cnr",
                      "Carrier-to-Noise Ratio",
                      "mdi:chart-bell-curve",
                      ::dimval::palette::green_400)

DIMVAL_DEFINE_MEASURE(EbNo,
                      ::dimval::Decibel,
                      "eb_no",
                      "Energy per Bit to Noise Density Ratio",
                      "mdi:chart-bell-curve",
                      ::dimval::palette::green_500)

DIMVAL_DEFINE_MEASURE(Mer,
                      ::dimval::Decibel,
                      "mer",
                      "Modulation Error Ratio",
                      "mdi:chart-bell-curve",
                      ::dimval::palette::green_400)

DIMVAL_DEFINE_MEASURE(EvmPercent,
                      ::dimval::Percent,
                      "evm_percent",
                      "Error Vector Magnitude",
                      "mdi:percent",
                      ::dimval::palette::red_400,
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(EvmDb,
                      ::dimval::Decibel,
                      "evm_db",
                      "Error Vector Magnitude",
                      "mdi:percent",
                      ::dimval::palette::red_400)

// -----------------------------------------------------------------------------
// Phase / IQ
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_MEASURE(Phase,
                      ::dimval::PhaseDegree,
                      "phase",
                      "Phase",
                      "mdi:angle-acute",
                      ::dimval::palette::deep_purple_400)

DIMVAL_DEFINE_MEASURE(PhaseRadians,
                      ::dimval::PhaseRadian,
                      "phase_radians",
                      "Phase",
                      "mdi:angle-acute",
                      ::dimval::palette::deep_purple_500)

DIMVAL_DEFINE_MEASURE(IqImbalanceGain,
                      ::dimval::Decibel,
                      "iq_imbalance_gain",
                      "IQ Gain Imbalance",
                      "mdi:sine-wave",
                      ::dimval::palette::green_600)

DIMVAL_DEFINE_MEASURE(IqImbalancePhase,
                      ::dimval::PhaseDegree,
                      "iq_imbalance_phase",
                      "IQ Phase Imbalance",
                      "mdi:sine-wave",
                      ::dimval::palette::deep_purple_600)

// -----------------------------------------------------------------------------
// Frequency error / stability / drift
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_MEASURE(FrequencyErrorHz,
                      ::dimval::Hertz,
                      "frequency_error_hz",
                      "Frequency Error",
                      "mdi:tune-variant",
                      ::dimval::palette::red_400)

DIMVAL_DEFINE_MEASURE(FrequencyErrorPpm,
                      ::dimval::PartsPerMillion,
                      "frequency_error_ppm",
                      "Frequency Error",
                      "mdi:tune-variant",
                      ::dimval::palette::red_400)

DIMVAL_DEFINE_MEASURE(FrequencyStabilityPpb,
                      ::dimval::PartsPerBillion,
                      "frequency_stability_ppb",
                      "Frequency Stability",
                      "mdi:tune",
                      ::dimval::palette::cyan_400)

DIMVAL_DEFINE_MEASURE(ClockDrift,
                      ::dimval::SecondsPerDay,
                      "clock_drift",
                      "Clock Drift",
                      "mdi:clock-alert-outline",
                      ::dimval::palette::blue_400)

// -----------------------------------------------------------------------------
// Spectral / noise density
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_MEASURE(NoiseDensityVoltage,
                      ::dimval::VoltPerRootHertz,
                      "noise_density_voltage",
                      "Voltage Noise Density",
                      "mdi:chart-line",
                      ::dimval::palette::cyan_400)

DIMVAL_DEFINE_MEASURE(NoiseDensityCurrent,
                      ::dimval::AmperePerRootHertz,
                      "noise_density_current",
                      "Current Noise Density",
                      "mdi:chart-line",
                      ::dimval::palette::cyan_500)

DIMVAL_DEFINE_MEASURE(PowerSpectralDensity,
                      ::dimval::WattPerHertz,
                      "power_spectral_density",
                      "Power Spectral Density",
                      "mdi:chart-line",
                      ::dimval::palette::cyan_600)

DIMVAL_DEFINE_MEASURE(NoiseDensityDb,
                      ::dimval::DecibelPerHertz,
                      "noise_density_db",
                      "Noise Density",
                      "mdi:chart-line",
                      ::dimval::palette::cyan_700)
