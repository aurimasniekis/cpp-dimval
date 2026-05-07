#pragma once

/// @file
/// @brief Core electrical measures: voltage, current, resistance, power, ...
///        Plus field/material properties (E-field, H-field, flux, resistivity).

#include <dimval/define.hpp>
#include <dimval/units/electrical.hpp>
#include <dimval/units/si.hpp>

// -----------------------------------------------------------------------------
// Core electrical
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_MEASURE(Voltage,
                      ::dimval::Volt,
                      "voltage",
                      "Voltage",
                      "material-symbols:electric-bolt-rounded",
                      ::dimval::palette::amber_500)

DIMVAL_DEFINE_MEASURE(Current,
                      ::dimval::Ampere,
                      "current",
                      "Electric Current",
                      "material-symbols:electric-bolt-rounded",
                      ::dimval::palette::amber_600)

DIMVAL_DEFINE_MEASURE(Resistance,
                      ::dimval::Ohm,
                      "resistance",
                      "Electrical Resistance",
                      "mdi:resistor",
                      ::dimval::palette::brown_400)

DIMVAL_DEFINE_MEASURE(Conductance,
                      ::dimval::Siemens,
                      "conductance",
                      "Electrical Conductance",
                      "mdi:resistor-nodes",
                      ::dimval::palette::brown_500)

DIMVAL_DEFINE_MEASURE(Capacitance,
                      ::dimval::Farad,
                      "capacitance",
                      "Capacitance",
                      "mdi:capacitor",
                      ::dimval::palette::brown_300)

DIMVAL_DEFINE_MEASURE(Inductance,
                      ::dimval::Henry,
                      "inductance",
                      "Inductance",
                      "mdi:coil",
                      ::dimval::palette::brown_600)

DIMVAL_DEFINE_MEASURE(Power,
                      ::dimval::Watt,
                      "power",
                      "Power",
                      "mdi:lightning-bolt",
                      ::dimval::palette::deep_orange_400)

DIMVAL_DEFINE_MEASURE(
    Energy, ::dimval::Joule, "energy", "Energy", "mdi:flash", ::dimval::palette::deep_orange_500)

DIMVAL_DEFINE_MEASURE(Charge,
                      ::dimval::Coulomb,
                      "charge",
                      "Electric Charge",
                      "mdi:transmission-tower",
                      ::dimval::palette::amber_700)

// -----------------------------------------------------------------------------
// Field / material properties
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_MEASURE(ElectricFieldStrength,
                      ::dimval::VoltPerMeter,
                      "electric_field_strength",
                      "Electric Field Strength",
                      "mdi:arrow-expand-horizontal",
                      ::dimval::palette::amber_400)

DIMVAL_DEFINE_MEASURE(MagneticFieldStrength,
                      ::dimval::AmperePerMeter,
                      "magnetic_field_strength",
                      "Magnetic Field Strength",
                      "ph:magnet",
                      ::dimval::palette::indigo_300)

DIMVAL_DEFINE_MEASURE(MagneticFlux,
                      ::dimval::Weber,
                      "magnetic_flux",
                      "Magnetic Flux",
                      "ph:magnet",
                      ::dimval::palette::indigo_400)

DIMVAL_DEFINE_MEASURE(MagneticFluxDensity,
                      ::dimval::Tesla,
                      "magnetic_flux_density",
                      "Magnetic Flux Density",
                      "ph:magnet",
                      ::dimval::palette::indigo_500)

DIMVAL_DEFINE_MEASURE(Resistivity,
                      ::dimval::OhmMeter,
                      "resistivity",
                      "Electrical Resistivity",
                      "mdi:resistor",
                      ::dimval::palette::brown_500)

DIMVAL_DEFINE_MEASURE(Conductivity,
                      ::dimval::SiemensPerMeter,
                      "conductivity",
                      "Electrical Conductivity",
                      "mdi:resistor-nodes",
                      ::dimval::palette::brown_600)

DIMVAL_DEFINE_MEASURE(Permittivity,
                      ::dimval::FaradPerMeter,
                      "permittivity",
                      "Permittivity",
                      "mdi:capacitor",
                      ::dimval::palette::brown_200)

DIMVAL_DEFINE_MEASURE(Permeability,
                      ::dimval::HenryPerMeter,
                      "permeability",
                      "Permeability",
                      "mdi:coil",
                      ::dimval::palette::brown_700)
