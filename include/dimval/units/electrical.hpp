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
                   "mdi:arrow-expand-horizontal",
                   ::dimval::palette::amber_400)

DIMVAL_DEFINE_UNIT(AmperePerMeter,
                   "A/m",
                   "A/m",
                   "A/m",
                   "ampere per meter",
                   "magnetic_field_strength",
                   1.0,
                   "ph:magnet",
                   ::dimval::palette::indigo_300)

DIMVAL_DEFINE_UNIT(CoulombPerKilogram,
                   "C/kg",
                   "C/kg",
                   "C/kg",
                   "coulomb per kilogram",
                   "ionizing_radiation_exposure",
                   1.0,
                   "mdi:radioactive-circle-outline",
                   ::dimval::palette::pink_700)

DIMVAL_DEFINE_UNIT(VoltAmpere,
                   "VA",
                   "VA",
                   "VA",
                   "volt-ampere",
                   "apparent_power",
                   1.0,
                   "mdi:sine-wave",
                   ::dimval::palette::deep_orange_300)

DIMVAL_DEFINE_UNIT(Var,
                   "var",
                   "var",
                   "var",
                   "volt-ampere reactive",
                   "reactive_power",
                   1.0,
                   "mdi:sine-wave",
                   ::dimval::palette::deep_orange_200)

DIMVAL_DEFINE_UNIT(WattHour,
                   "Wh",
                   "Wh",
                   "Wh",
                   "watt-hour",
                   "energy",
                   3600.0,
                   "mdi:battery-high",
                   ::dimval::palette::deep_orange_600)

DIMVAL_DEFINE_UNIT(AmpereHour,
                   "Ah",
                   "Ah",
                   "Ah",
                   "ampere-hour",
                   "charge",
                   3600.0,
                   "mdi:battery",
                   ::dimval::palette::amber_800)

DIMVAL_DEFINE_UNIT(VoltSecond,
                   "V_s",
                   "V·s",
                   "V·s",
                   "volt-second",
                   "magnetic_flux",
                   1.0,
                   "mdi:chart-timeline-variant",
                   ::dimval::palette::amber_300)

DIMVAL_DEFINE_UNIT(OhmMeter,
                   "ohm_m",
                   "Ω·m",
                   "Ω·m",
                   "ohm-meter",
                   "resistivity",
                   1.0,
                   "mdi:resistor",
                   ::dimval::palette::brown_500)

DIMVAL_DEFINE_UNIT(SiemensPerMeter,
                   "S/m",
                   "S/m",
                   "S/m",
                   "siemens per meter",
                   "conductivity",
                   1.0,
                   "mdi:resistor-nodes",
                   ::dimval::palette::brown_600)

DIMVAL_DEFINE_UNIT(FaradPerMeter,
                   "F/m",
                   "F/m",
                   "F/m",
                   "farad per meter",
                   "permittivity",
                   1.0,
                   "mdi:capacitor",
                   ::dimval::palette::brown_200)

DIMVAL_DEFINE_UNIT(HenryPerMeter,
                   "H/m",
                   "H/m",
                   "H/m",
                   "henry per meter",
                   "permeability",
                   1.0,
                   "mdi:coil",
                   ::dimval::palette::brown_700)

DIMVAL_DEFINE_UNIT(JoulePerCoulomb,
                   "J/C",
                   "J/C",
                   "J/C",
                   "joule per coulomb",
                   "voltage",
                   1.0,
                   "material-symbols:electric-bolt-rounded",
                   ::dimval::palette::amber_400)

DIMVAL_DEFINE_UNIT(CoulombPerVolt,
                   "C/V",
                   "C/V",
                   "C/V",
                   "coulomb per volt",
                   "capacitance",
                   1.0,
                   "mdi:capacitor",
                   ::dimval::palette::brown_300)

DIMVAL_DEFINE_UNIT(VoltPerAmpere,
                   "V/A",
                   "V/A",
                   "V/A",
                   "volt per ampere",
                   "resistance",
                   1.0,
                   "mdi:resistor",
                   ::dimval::palette::brown_400)

DIMVAL_DEFINE_UNIT(AmperePerVolt,
                   "A/V",
                   "A/V",
                   "A/V",
                   "ampere per volt",
                   "conductance",
                   1.0,
                   "mdi:resistor-nodes",
                   ::dimval::palette::brown_500)

DIMVAL_DEFINE_UNIT(WeberPerAmpere,
                   "Wb/A",
                   "Wb/A",
                   "Wb/A",
                   "weber per ampere",
                   "inductance",
                   1.0,
                   "mdi:coil",
                   ::dimval::palette::brown_600)

DIMVAL_DEFINE_UNIT(CoulombPerSecond,
                   "C/s",
                   "C/s",
                   "C/s",
                   "coulomb per second",
                   "current",
                   1.0,
                   "material-symbols:electric-bolt-rounded",
                   ::dimval::palette::amber_600)
