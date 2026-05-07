#pragma once

/// @file
/// @brief Canonical SI units (base + derived) and accepted/practical alts.

#include <dimval/define.hpp>

// -----------------------------------------------------------------------------
// SI base units
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_UNIT(
    Meter, "m", "m", "m", "meter", "length", 1.0, "tabler:ruler", ::dimval::palette::teal_400)

DIMVAL_DEFINE_UNIT(Kilogram,
                   "kg",
                   "kg",
                   "kg",
                   "kilogram",
                   "mass",
                   1.0,
                   "mdi:weight",
                   ::dimval::palette::blue_grey_400)

DIMVAL_DEFINE_UNIT(
    Second, "s", "s", "s", "second", "time", 1.0, "ph:clock", ::dimval::palette::blue_400)

DIMVAL_DEFINE_UNIT(Ampere,
                   "A",
                   "A",
                   "A",
                   "ampere",
                   "current",
                   1.0,
                   "material-symbols:electric-bolt-rounded",
                   ::dimval::palette::amber_600)

DIMVAL_DEFINE_UNIT(Kelvin,
                   "K",
                   "K",
                   "K",
                   "kelvin",
                   "temperature",
                   1.0,
                   "ph:thermometer-light",
                   ::dimval::palette::orange_300)

DIMVAL_DEFINE_UNIT(Mole,
                   "mol",
                   "mol",
                   "mol",
                   "mole",
                   "amount_of_substance",
                   1.0,
                   "mdi:beaker-outline",
                   ::dimval::palette::blue_grey_400)

DIMVAL_DEFINE_UNIT(Candela,
                   "cd",
                   "cd",
                   "cd",
                   "candela",
                   "luminous_intensity",
                   1.0,
                   "mdi:lightbulb-outline",
                   ::dimval::palette::yellow_400)

// -----------------------------------------------------------------------------
// Time alternates (canonical = Second; linearly converting alt non-prefix units)
// -----------------------------------------------------------------------------

DIMVAL_DEFINE_UNIT(
    Minute, "min", "min", "min", "minute", "time", 60.0, "mdi:timer", ::dimval::palette::blue_300)
DIMVAL_DEFINE_UNIT(Hour,
                   "h",
                   "h",
                   "h",
                   "hour",
                   "time",
                   3600.0,
                   "mdi:clock-time-three-outline",
                   ::dimval::palette::blue_500)
DIMVAL_DEFINE_UNIT(
    Day, "d", "d", "d", "day", "time", 86400.0, "mdi:calendar", ::dimval::palette::blue_600)

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
                   "mdi:thermometer-lines",
                   ::dimval::palette::orange_400,
                   static constexpr double offset = 273.15;
                   static constexpr int default_precision = 1;)
DIMVAL_DEFINE_UNIT(Fahrenheit,
                   "degF",
                   "°F",
                   "°F",
                   "degree Fahrenheit",
                   "temperature",
                   5.0 / 9.0,
                   "mdi:thermometer",
                   ::dimval::palette::orange_500,
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
                   "mdi:angle-obtuse",
                   ::dimval::palette::deep_purple_400)

DIMVAL_DEFINE_UNIT(Steradian,
                   "sr",
                   "sr",
                   "sr",
                   "steradian",
                   "solid_angle",
                   1.0,
                   "mdi:circle-outline",
                   ::dimval::palette::deep_purple_300)

DIMVAL_DEFINE_UNIT(Hertz,
                   "Hz",
                   "Hz",
                   "Hz",
                   "hertz",
                   "frequency",
                   1.0,
                   "ph:wave-sine",
                   ::dimval::palette::light_blue_400)

DIMVAL_DEFINE_UNIT(Newton,
                   "N",
                   "N",
                   "N",
                   "newton",
                   "force",
                   1.0,
                   "mdi:arrow-right-bold",
                   ::dimval::palette::blue_grey_500)

DIMVAL_DEFINE_UNIT(Pascal,
                   "Pa",
                   "Pa",
                   "Pa",
                   "pascal",
                   "pressure",
                   1.0,
                   "ph:gauge",
                   ::dimval::palette::blue_grey_400)

DIMVAL_DEFINE_UNIT(
    Joule, "J", "J", "J", "joule", "energy", 1.0, "mdi:flash", ::dimval::palette::deep_orange_500)

DIMVAL_DEFINE_UNIT(Watt,
                   "W",
                   "W",
                   "W",
                   "watt",
                   "power",
                   1.0,
                   "mdi:lightning-bolt",
                   ::dimval::palette::deep_orange_400)

DIMVAL_DEFINE_UNIT(Coulomb,
                   "C",
                   "C",
                   "C",
                   "coulomb",
                   "charge",
                   1.0,
                   "mdi:transmission-tower",
                   ::dimval::palette::amber_700)

DIMVAL_DEFINE_UNIT(Volt,
                   "V",
                   "V",
                   "V",
                   "volt",
                   "voltage",
                   1.0,
                   "material-symbols:electric-bolt-rounded",
                   ::dimval::palette::amber_500)

DIMVAL_DEFINE_UNIT(Farad,
                   "F",
                   "F",
                   "F",
                   "farad",
                   "capacitance",
                   1.0,
                   "mdi:capacitor",
                   ::dimval::palette::brown_300)

DIMVAL_DEFINE_UNIT(
    Ohm, "ohm", "Ω", "Ω", "ohm", "resistance", 1.0, "mdi:resistor", ::dimval::palette::brown_400)

DIMVAL_DEFINE_UNIT(Siemens,
                   "siemens",
                   "S",
                   "S",
                   "siemens",
                   "conductance",
                   1.0,
                   "mdi:resistor-nodes",
                   ::dimval::palette::brown_500)

DIMVAL_DEFINE_UNIT(Weber,
                   "Wb",
                   "Wb",
                   "Wb",
                   "weber",
                   "magnetic_flux",
                   1.0,
                   "ph:magnet",
                   ::dimval::palette::indigo_400)

DIMVAL_DEFINE_UNIT(Tesla,
                   "T",
                   "T",
                   "T",
                   "tesla",
                   "magnetic_flux_density",
                   1.0,
                   "ph:magnet",
                   ::dimval::palette::indigo_500)

DIMVAL_DEFINE_UNIT(
    Henry, "H", "H", "H", "henry", "inductance", 1.0, "mdi:coil", ::dimval::palette::brown_600)

DIMVAL_DEFINE_UNIT(Lumen,
                   "lm",
                   "lm",
                   "lm",
                   "lumen",
                   "luminous_flux",
                   1.0,
                   "mdi:lightbulb-outline",
                   ::dimval::palette::yellow_500)

DIMVAL_DEFINE_UNIT(Lux,
                   "lx",
                   "lx",
                   "lx",
                   "lux",
                   "illuminance",
                   1.0,
                   "mdi:brightness-6",
                   ::dimval::palette::yellow_600)

DIMVAL_DEFINE_UNIT(Becquerel,
                   "Bq",
                   "Bq",
                   "Bq",
                   "becquerel",
                   "radioactivity",
                   1.0,
                   "mdi:radioactive-circle-outline",
                   ::dimval::palette::pink_400)

DIMVAL_DEFINE_UNIT(Gray,
                   "Gy",
                   "Gy",
                   "Gy",
                   "gray",
                   "absorbed_dose",
                   1.0,
                   "mdi:radioactive-circle-outline",
                   ::dimval::palette::pink_500)

DIMVAL_DEFINE_UNIT(Sievert,
                   "Sv",
                   "Sv",
                   "Sv",
                   "sievert",
                   "dose_equivalent",
                   1.0,
                   "mdi:radioactive-circle-outline",
                   ::dimval::palette::pink_600)

DIMVAL_DEFINE_UNIT(Katal,
                   "kat",
                   "kat",
                   "kat",
                   "katal",
                   "catalytic_activity",
                   1.0,
                   "mdi:beaker-outline",
                   ::dimval::palette::pink_300)

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
                   "mdi:water-outline",
                   ::dimval::palette::blue_grey_300)

DIMVAL_DEFINE_UNIT(CubicMeter,
                   "m3",
                   "m³",
                   "m³",
                   "cubic meter",
                   "volume",
                   1000.0,
                   "mdi:cube-outline",
                   ::dimval::palette::blue_grey_400)

DIMVAL_DEFINE_UNIT(
    Tonne, "t", "t", "t", "tonne", "mass", 1000.0, "mdi:weight", ::dimval::palette::blue_grey_500)

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
                   "ph:gauge",
                   ::dimval::palette::blue_grey_500,
                   static constexpr int default_precision = 2;)

DIMVAL_DEFINE_UNIT(Atmosphere,
                   "atm",
                   "atm",
                   "atm",
                   "standard atmosphere",
                   "pressure",
                   101325.0,
                   "ph:gauge",
                   ::dimval::palette::blue_grey_600,
                   static constexpr int default_precision = 3;)

DIMVAL_DEFINE_UNIT(KilowattHour,
                   "kWh",
                   "kWh",
                   "kWh",
                   "kilowatt-hour",
                   "energy",
                   3.6e6,
                   "mdi:battery-high",
                   ::dimval::palette::deep_orange_700,
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
                   "ph:magnet",
                   ::dimval::palette::indigo_400)

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
                   "mdi:angle-obtuse",
                   ::dimval::palette::deep_purple_400,
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
                   "mdi:angle-acute",
                   ::dimval::palette::deep_purple_300,
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
                   "mdi:angle-acute",
                   ::dimval::palette::deep_purple_200,
                   static constexpr int default_precision = 3;
                   static constexpr bool no_space_before_symbol = true;)
