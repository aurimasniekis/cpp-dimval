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
                      ::comms::Icon::from("material-symbols:electric-bolt-rounded"),
                      ::comms::Colors::mui::amber[500])

DIMVAL_DEFINE_MEASURE(Current,
                      ::dimval::Ampere,
                      "current",
                      "Electric Current",
                      ::comms::Icon::from("material-symbols:electric-bolt-rounded"),
                      ::comms::Colors::mui::amber[600])

DIMVAL_DEFINE_MEASURE(Resistance,
                      ::dimval::Ohm,
                      "resistance",
                      "Electrical Resistance",
                      ::comms::Icons::mdi::resistor,
                      ::comms::Colors::mui::brown[400])

DIMVAL_DEFINE_MEASURE(Conductance,
                      ::dimval::Siemens,
                      "conductance",
                      "Electrical Conductance",
                      ::comms::Icons::mdi::resistor_nodes,
                      ::comms::Colors::mui::brown[500])

DIMVAL_DEFINE_MEASURE(Capacitance,
                      ::dimval::Farad,
                      "capacitance",
                      "Capacitance",
                      ::comms::Icon::from("mdi:capacitor"),
                      ::comms::Colors::mui::brown[300])

DIMVAL_DEFINE_MEASURE(Inductance,
                      ::dimval::Henry,
                      "inductance",
                      "Inductance",
                      ::comms::Icon::from("mdi:coil"),
                      ::comms::Colors::mui::brown[600])

DIMVAL_DEFINE_MEASURE(Power,
                      ::dimval::Watt,
                      "power",
                      "Power",
                      ::comms::Icons::mdi::lightning_bolt,
                      ::comms::Colors::mui::deep_orange[400])

DIMVAL_DEFINE_MEASURE(Energy,
                      ::dimval::Joule,
                      "energy",
                      "Energy",
                      ::comms::Icons::mdi::flash,
                      ::comms::Colors::mui::deep_orange[500])

DIMVAL_DEFINE_MEASURE(Charge,
                      ::dimval::Coulomb,
                      "charge",
                      "Electric Charge",
                      ::comms::Icons::mdi::transmission_tower,
                      ::comms::Colors::mui::amber[700])

// -----------------------------------------------------------------------------
// Field / material properties
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_MEASURE(ElectricFieldStrength,
                      ::dimval::VoltPerMeter,
                      "electric_field_strength",
                      "Electric Field Strength",
                      ::comms::Icons::mdi::arrow_expand_horizontal,
                      ::comms::Colors::mui::amber[400])

DIMVAL_DEFINE_MEASURE(MagneticFieldStrength,
                      ::dimval::AmperePerMeter,
                      "magnetic_field_strength",
                      "Magnetic Field Strength",
                      ::comms::Icon::from("ph:magnet"),
                      ::comms::Colors::mui::indigo[300])

DIMVAL_DEFINE_MEASURE(MagneticFlux,
                      ::dimval::Weber,
                      "magnetic_flux",
                      "Magnetic Flux",
                      ::comms::Icon::from("ph:magnet"),
                      ::comms::Colors::mui::indigo[400])

DIMVAL_DEFINE_MEASURE(MagneticFluxDensity,
                      ::dimval::Tesla,
                      "magnetic_flux_density",
                      "Magnetic Flux Density",
                      ::comms::Icon::from("ph:magnet"),
                      ::comms::Colors::mui::indigo[500])

DIMVAL_DEFINE_MEASURE(Resistivity,
                      ::dimval::OhmMeter,
                      "resistivity",
                      "Electrical Resistivity",
                      ::comms::Icons::mdi::resistor,
                      ::comms::Colors::mui::brown[500])

DIMVAL_DEFINE_MEASURE(Conductivity,
                      ::dimval::SiemensPerMeter,
                      "conductivity",
                      "Electrical Conductivity",
                      ::comms::Icons::mdi::resistor_nodes,
                      ::comms::Colors::mui::brown[600])

DIMVAL_DEFINE_MEASURE(Permittivity,
                      ::dimval::FaradPerMeter,
                      "permittivity",
                      "Permittivity",
                      ::comms::Icon::from("mdi:capacitor"),
                      ::comms::Colors::mui::brown[200])

DIMVAL_DEFINE_MEASURE(Permeability,
                      ::dimval::HenryPerMeter,
                      "permeability",
                      "Permeability",
                      ::comms::Icon::from("mdi:coil"),
                      ::comms::Colors::mui::brown[700])
