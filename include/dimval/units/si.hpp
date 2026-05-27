#pragma once

/// @file
/// @brief Canonical SI units (base + derived) and accepted/practical alts.

#include <dimval/define.hpp>

// -----------------------------------------------------------------------------
// SI base units
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_UNIT(Meter,
                   "m",
                   "m",
                   "m",
                   "meter",
                   "length",
                   1.0,
                   ::comms::Icon::from("tabler:ruler"),
                   ::comms::Colors::mui::teal[400])

DIMVAL_DEFINE_UNIT(Kilogram,
                   "kg",
                   "kg",
                   "kg",
                   "kilogram",
                   "mass",
                   1.0,
                   ::comms::Icons::mdi::weight,
                   ::comms::Colors::mui::blue_grey[400])

DIMVAL_DEFINE_UNIT(Second,
                   "s",
                   "s",
                   "s",
                   "second",
                   "time",
                   1.0,
                   ::comms::Icon::from("ph:clock"),
                   ::comms::Colors::mui::blue[400])

DIMVAL_DEFINE_UNIT(Ampere,
                   "A",
                   "A",
                   "A",
                   "ampere",
                   "current",
                   1.0,
                   ::comms::Icon::from("material-symbols:electric-bolt-rounded"),
                   ::comms::Colors::mui::amber[600])

DIMVAL_DEFINE_UNIT(Kelvin,
                   "K",
                   "K",
                   "K",
                   "kelvin",
                   "temperature",
                   1.0,
                   ::comms::Icon::from("ph:thermometer-light"),
                   ::comms::Colors::mui::orange[300])

DIMVAL_DEFINE_UNIT(Mole,
                   "mol",
                   "mol",
                   "mol",
                   "mole",
                   "amount_of_substance",
                   1.0,
                   ::comms::Icons::mdi::beaker_outline,
                   ::comms::Colors::mui::blue_grey[400])

DIMVAL_DEFINE_UNIT(Candela,
                   "cd",
                   "cd",
                   "cd",
                   "candela",
                   "luminous_intensity",
                   1.0,
                   ::comms::Icons::mdi::lightbulb_outline,
                   ::comms::Colors::mui::yellow[400])

// -----------------------------------------------------------------------------
// Time alternates (canonical = Second; linearly converting alt non-prefix units)
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_UNIT(Minute,
                   "min",
                   "min",
                   "min",
                   "minute",
                   "time",
                   60.0,
                   ::comms::Icons::mdi::timer,
                   ::comms::Colors::mui::blue[300])
DIMVAL_DEFINE_UNIT(Hour,
                   "h",
                   "h",
                   "h",
                   "hour",
                   "time",
                   3600.0,
                   ::comms::Icons::mdi::clock_time_three_outline,
                   ::comms::Colors::mui::blue[500])
DIMVAL_DEFINE_UNIT(Day,
                   "d",
                   "d",
                   "d",
                   "day",
                   "time",
                   86400.0,
                   ::comms::Icons::mdi::calendar,
                   ::comms::Colors::mui::blue[600])

// -----------------------------------------------------------------------------
// Temperature alternates (canonical = Kelvin)
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_UNIT(Celsius,
                   "degC",
                   "°C",
                   "°C",
                   "degree Celsius",
                   "temperature",
                   1.0,
                   ::comms::Icons::mdi::thermometer_lines,
                   ::comms::Colors::mui::orange[400],
                   static constexpr double offset = 273.15;
                   static constexpr int default_precision = 1;)
DIMVAL_DEFINE_UNIT(Fahrenheit,
                   "degF",
                   "°F",
                   "°F",
                   "degree Fahrenheit",
                   "temperature",
                   5.0 / 9.0,
                   ::comms::Icons::mdi::thermometer,
                   ::comms::Colors::mui::orange[500],
                   static constexpr double offset = 273.15 - 32.0 * 5.0 / 9.0;
                   static constexpr int default_precision = 1;)

// -----------------------------------------------------------------------------
// SI derived units
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_UNIT(Radian,
                   "rad",
                   "rad",
                   "rad",
                   "radian",
                   "angle",
                   1.0,
                   ::comms::Icons::mdi::angle_obtuse,
                   ::comms::Colors::mui::deep_purple[400])

DIMVAL_DEFINE_UNIT(Steradian,
                   "sr",
                   "sr",
                   "sr",
                   "steradian",
                   "solid_angle",
                   1.0,
                   ::comms::Icons::mdi::circle_outline,
                   ::comms::Colors::mui::deep_purple[300])

DIMVAL_DEFINE_UNIT(Hertz,
                   "Hz",
                   "Hz",
                   "Hz",
                   "hertz",
                   "frequency",
                   1.0,
                   ::comms::Icon::from("ph:wave-sine"),
                   ::comms::Colors::mui::light_blue[400])

DIMVAL_DEFINE_UNIT(Newton,
                   "N",
                   "N",
                   "N",
                   "newton",
                   "force",
                   1.0,
                   ::comms::Icons::mdi::arrow_right_bold,
                   ::comms::Colors::mui::blue_grey[500])

DIMVAL_DEFINE_UNIT(Pascal,
                   "Pa",
                   "Pa",
                   "Pa",
                   "pascal",
                   "pressure",
                   1.0,
                   ::comms::Icon::from("ph:gauge"),
                   ::comms::Colors::mui::blue_grey[400])

DIMVAL_DEFINE_UNIT(Joule,
                   "J",
                   "J",
                   "J",
                   "joule",
                   "energy",
                   1.0,
                   ::comms::Icons::mdi::flash,
                   ::comms::Colors::mui::deep_orange[500])

DIMVAL_DEFINE_UNIT(Watt,
                   "W",
                   "W",
                   "W",
                   "watt",
                   "power",
                   1.0,
                   ::comms::Icons::mdi::lightning_bolt,
                   ::comms::Colors::mui::deep_orange[400])

DIMVAL_DEFINE_UNIT(Coulomb,
                   "C",
                   "C",
                   "C",
                   "coulomb",
                   "charge",
                   1.0,
                   ::comms::Icons::mdi::transmission_tower,
                   ::comms::Colors::mui::amber[700])

DIMVAL_DEFINE_UNIT(Volt,
                   "V",
                   "V",
                   "V",
                   "volt",
                   "voltage",
                   1.0,
                   ::comms::Icon::from("material-symbols:electric-bolt-rounded"),
                   ::comms::Colors::mui::amber[500])

DIMVAL_DEFINE_UNIT(Farad,
                   "F",
                   "F",
                   "F",
                   "farad",
                   "capacitance",
                   1.0,
                   ::comms::Icon::from("mdi:capacitor"),
                   ::comms::Colors::mui::brown[300])

DIMVAL_DEFINE_UNIT(Ohm,
                   "ohm",
                   "Ω",
                   "Ω",
                   "ohm",
                   "resistance",
                   1.0,
                   ::comms::Icons::mdi::resistor,
                   ::comms::Colors::mui::brown[400])

DIMVAL_DEFINE_UNIT(Siemens,
                   "siemens",
                   "S",
                   "S",
                   "siemens",
                   "conductance",
                   1.0,
                   ::comms::Icons::mdi::resistor_nodes,
                   ::comms::Colors::mui::brown[500])

DIMVAL_DEFINE_UNIT(Weber,
                   "Wb",
                   "Wb",
                   "Wb",
                   "weber",
                   "magnetic_flux",
                   1.0,
                   ::comms::Icon::from("ph:magnet"),
                   ::comms::Colors::mui::indigo[400])

DIMVAL_DEFINE_UNIT(Tesla,
                   "T",
                   "T",
                   "T",
                   "tesla",
                   "magnetic_flux_density",
                   1.0,
                   ::comms::Icon::from("ph:magnet"),
                   ::comms::Colors::mui::indigo[500])

DIMVAL_DEFINE_UNIT(Henry,
                   "H",
                   "H",
                   "H",
                   "henry",
                   "inductance",
                   1.0,
                   ::comms::Icon::from("mdi:coil"),
                   ::comms::Colors::mui::brown[600])

DIMVAL_DEFINE_UNIT(Lumen,
                   "lm",
                   "lm",
                   "lm",
                   "lumen",
                   "luminous_flux",
                   1.0,
                   ::comms::Icons::mdi::lightbulb_outline,
                   ::comms::Colors::mui::yellow[500])

DIMVAL_DEFINE_UNIT(Lux,
                   "lx",
                   "lx",
                   "lx",
                   "lux",
                   "illuminance",
                   1.0,
                   ::comms::Icons::mdi::brightness_6,
                   ::comms::Colors::mui::yellow[600])

DIMVAL_DEFINE_UNIT(Becquerel,
                   "Bq",
                   "Bq",
                   "Bq",
                   "becquerel",
                   "radioactivity",
                   1.0,
                   ::comms::Icons::mdi::radioactive_circle_outline,
                   ::comms::Colors::mui::pink[400])

DIMVAL_DEFINE_UNIT(Gray,
                   "Gy",
                   "Gy",
                   "Gy",
                   "gray",
                   "absorbed_dose",
                   1.0,
                   ::comms::Icons::mdi::radioactive_circle_outline,
                   ::comms::Colors::mui::pink[500])

DIMVAL_DEFINE_UNIT(Sievert,
                   "Sv",
                   "Sv",
                   "Sv",
                   "sievert",
                   "dose_equivalent",
                   1.0,
                   ::comms::Icons::mdi::radioactive_circle_outline,
                   ::comms::Colors::mui::pink[600])

DIMVAL_DEFINE_UNIT(Katal,
                   "kat",
                   "kat",
                   "kat",
                   "katal",
                   "catalytic_activity",
                   1.0,
                   ::comms::Icons::mdi::beaker_outline,
                   ::comms::Colors::mui::pink[300])

// -----------------------------------------------------------------------------
// Volume / mass alternates
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_UNIT(Litre,
                   "L",
                   "L",
                   "L",
                   "litre",
                   "volume",
                   1.0,
                   ::comms::Icons::mdi::water_outline,
                   ::comms::Colors::mui::blue_grey[300])

DIMVAL_DEFINE_UNIT(CubicMeter,
                   "m3",
                   "m³",
                   "m³",
                   "cubic meter",
                   "volume",
                   1000.0,
                   ::comms::Icons::mdi::cube_outline,
                   ::comms::Colors::mui::blue_grey[400])

DIMVAL_DEFINE_UNIT(Tonne,
                   "t",
                   "t",
                   "t",
                   "tonne",
                   "mass",
                   1000.0,
                   ::comms::Icons::mdi::weight,
                   ::comms::Colors::mui::blue_grey[500])

// -----------------------------------------------------------------------------
// Pressure / energy alternates
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_UNIT(Bar,
                   "bar",
                   "bar",
                   "bar",
                   "bar",
                   "pressure",
                   1e5,
                   ::comms::Icon::from("ph:gauge"),
                   ::comms::Colors::mui::blue_grey[500],
                   static constexpr int default_precision = 2;)

DIMVAL_DEFINE_UNIT(Atmosphere,
                   "atm",
                   "atm",
                   "atm",
                   "standard atmosphere",
                   "pressure",
                   101325.0,
                   ::comms::Icon::from("ph:gauge"),
                   ::comms::Colors::mui::blue_grey[600],
                   static constexpr int default_precision = 3;)

DIMVAL_DEFINE_UNIT(KilowattHour,
                   "kWh",
                   "kWh",
                   "kWh",
                   "kilowatt-hour",
                   "energy",
                   3.6e6,
                   ::comms::Icons::mdi::battery_high,
                   ::comms::Colors::mui::deep_orange[700],
                   static constexpr int default_precision = 2;)

// -----------------------------------------------------------------------------
// Magnetic flux density alternate
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_UNIT(Gauss,
                   "G",
                   "G",
                   "G",
                   "gauss",
                   "magnetic_flux_density",
                   1e-4,
                   ::comms::Icon::from("ph:magnet"),
                   ::comms::Colors::mui::indigo[400])

// -----------------------------------------------------------------------------
// Angle (canonical Radian; Degree alt non-prefix unit)
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_UNIT(Degree,
                   "deg",
                   "°",
                   "°",
                   "degree",
                   "angle",
                   0.017453292519943295,
                   ::comms::Icons::mdi::angle_obtuse,
                   ::comms::Colors::mui::deep_purple[400],
                   static constexpr ::std::string_view formatter = "degree";
                   static constexpr int default_precision = 2;
                   static constexpr bool no_space_before_symbol = true;)

// 1 arcminute = π/10800 rad. Used in astronomy / GNSS heading reports.
DIMVAL_DEFINE_UNIT(Arcminute,
                   "arcmin",
                   "′",
                   "′",
                   "arcminute",
                   "angle",
                   2.908882086657216e-4,
                   ::comms::Icons::mdi::angle_acute,
                   ::comms::Colors::mui::deep_purple[300],
                   static constexpr int default_precision = 2;
                   static constexpr bool no_space_before_symbol = true;)

// 1 arcsecond = π/648000 rad.
DIMVAL_DEFINE_UNIT(Arcsecond,
                   "arcsec",
                   "″",
                   "″",
                   "arcsecond",
                   "angle",
                   4.84813681109536e-6,
                   ::comms::Icons::mdi::angle_acute,
                   ::comms::Colors::mui::deep_purple[200],
                   static constexpr int default_precision = 3;
                   static constexpr bool no_space_before_symbol = true;)
