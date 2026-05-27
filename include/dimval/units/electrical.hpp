#pragma once

/// @file
/// @brief Electronics-specific compound and alternate units.
///
/// Includes field strength (V/m, A/m), apparent / reactive power (VA, var),
/// charge / energy alternates (Wh, Ah, V·s), material properties (Ω·m, S/m,
/// F/m, H/m), and equivalent forms of base SI quantities (J/C, C/V, ...).

#include <dimval/define.hpp>

DIMVAL_DEFINE_UNIT(VoltPerMeter,
                   "V/m",
                   "V/m",
                   "V/m",
                   "volt per meter",
                   "electric_field_strength",
                   1.0,
                   ::comms::Icons::mdi::arrow_expand_horizontal,
                   ::comms::Colors::mui::amber[400])

DIMVAL_DEFINE_UNIT(AmperePerMeter,
                   "A/m",
                   "A/m",
                   "A/m",
                   "ampere per meter",
                   "magnetic_field_strength",
                   1.0,
                   ::comms::Icon::from("ph:magnet"),
                   ::comms::Colors::mui::indigo[300])

DIMVAL_DEFINE_UNIT(CoulombPerKilogram,
                   "C/kg",
                   "C/kg",
                   "C/kg",
                   "coulomb per kilogram",
                   "ionizing_radiation_exposure",
                   1.0,
                   ::comms::Icons::mdi::radioactive_circle_outline,
                   ::comms::Colors::mui::pink[700])

DIMVAL_DEFINE_UNIT(VoltAmpere,
                   "VA",
                   "VA",
                   "VA",
                   "volt-ampere",
                   "apparent_power",
                   1.0,
                   ::comms::Icons::mdi::sine_wave,
                   ::comms::Colors::mui::deep_orange[300])

DIMVAL_DEFINE_UNIT(Var,
                   "var",
                   "var",
                   "var",
                   "volt-ampere reactive",
                   "reactive_power",
                   1.0,
                   ::comms::Icons::mdi::sine_wave,
                   ::comms::Colors::mui::deep_orange[200])

DIMVAL_DEFINE_UNIT(WattHour,
                   "Wh",
                   "Wh",
                   "Wh",
                   "watt-hour",
                   "energy",
                   3600.0,
                   ::comms::Icons::mdi::battery_high,
                   ::comms::Colors::mui::deep_orange[600])

DIMVAL_DEFINE_UNIT(AmpereHour,
                   "Ah",
                   "Ah",
                   "Ah",
                   "ampere-hour",
                   "charge",
                   3600.0,
                   ::comms::Icons::mdi::battery,
                   ::comms::Colors::mui::amber[800])

DIMVAL_DEFINE_UNIT(VoltSecond,
                   "V_s",
                   "V·s",
                   "V·s",
                   "volt-second",
                   "magnetic_flux",
                   1.0,
                   ::comms::Icons::mdi::chart_timeline_variant,
                   ::comms::Colors::mui::amber[300])

DIMVAL_DEFINE_UNIT(OhmMeter,
                   "ohm_m",
                   "Ω·m",
                   "Ω·m",
                   "ohm-meter",
                   "resistivity",
                   1.0,
                   ::comms::Icons::mdi::resistor,
                   ::comms::Colors::mui::brown[500])

DIMVAL_DEFINE_UNIT(SiemensPerMeter,
                   "S/m",
                   "S/m",
                   "S/m",
                   "siemens per meter",
                   "conductivity",
                   1.0,
                   ::comms::Icons::mdi::resistor_nodes,
                   ::comms::Colors::mui::brown[600])

DIMVAL_DEFINE_UNIT(FaradPerMeter,
                   "F/m",
                   "F/m",
                   "F/m",
                   "farad per meter",
                   "permittivity",
                   1.0,
                   ::comms::Icon::from("mdi:capacitor"),
                   ::comms::Colors::mui::brown[200])

DIMVAL_DEFINE_UNIT(HenryPerMeter,
                   "H/m",
                   "H/m",
                   "H/m",
                   "henry per meter",
                   "permeability",
                   1.0,
                   ::comms::Icon::from("mdi:coil"),
                   ::comms::Colors::mui::brown[700])

DIMVAL_DEFINE_UNIT(JoulePerCoulomb,
                   "J/C",
                   "J/C",
                   "J/C",
                   "joule per coulomb",
                   "voltage",
                   1.0,
                   ::comms::Icon::from("material-symbols:electric-bolt-rounded"),
                   ::comms::Colors::mui::amber[400])

DIMVAL_DEFINE_UNIT(CoulombPerVolt,
                   "C/V",
                   "C/V",
                   "C/V",
                   "coulomb per volt",
                   "capacitance",
                   1.0,
                   ::comms::Icon::from("mdi:capacitor"),
                   ::comms::Colors::mui::brown[300])

DIMVAL_DEFINE_UNIT(VoltPerAmpere,
                   "V/A",
                   "V/A",
                   "V/A",
                   "volt per ampere",
                   "resistance",
                   1.0,
                   ::comms::Icons::mdi::resistor,
                   ::comms::Colors::mui::brown[400])

DIMVAL_DEFINE_UNIT(AmperePerVolt,
                   "A/V",
                   "A/V",
                   "A/V",
                   "ampere per volt",
                   "conductance",
                   1.0,
                   ::comms::Icons::mdi::resistor_nodes,
                   ::comms::Colors::mui::brown[500])

DIMVAL_DEFINE_UNIT(WeberPerAmpere,
                   "Wb/A",
                   "Wb/A",
                   "Wb/A",
                   "weber per ampere",
                   "inductance",
                   1.0,
                   ::comms::Icon::from("mdi:coil"),
                   ::comms::Colors::mui::brown[600])

DIMVAL_DEFINE_UNIT(CoulombPerSecond,
                   "C/s",
                   "C/s",
                   "C/s",
                   "coulomb per second",
                   "current",
                   1.0,
                   ::comms::Icon::from("material-symbols:electric-bolt-rounded"),
                   ::comms::Colors::mui::amber[600])
