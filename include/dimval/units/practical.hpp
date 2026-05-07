#pragma once

/// @file
/// @brief Practical / accepted units that mostly carry their own kind:
///        clock drift, rotational frequency, velocity, wavelength.

#include <dimval/define.hpp>

DIMVAL_DEFINE_UNIT(SecondsPerDay,
                   "s_per_day",
                   "s/day",
                   "s/day",
                   "seconds per day",
                   "clock_drift",
                   1.0,
                   "mdi:clock-alert-outline",
                   ::dimval::palette::blue_300,
                   static constexpr int default_precision = 2;)

DIMVAL_DEFINE_UNIT(RotationPerMinute,
                   "rpm",
                   "rpm",
                   "rpm",
                   "rotation per minute",
                   "rotational_frequency",
                   1.0,
                   "mdi:rotate-right",
                   ::dimval::palette::light_blue_500,
                   static constexpr int default_precision = 0;)

DIMVAL_DEFINE_UNIT(MeterPerSecond,
                   "m_per_s",
                   "m/s",
                   "m/s",
                   "meter per second",
                   "velocity",
                   1.0,
                   "mdi:speedometer",
                   ::dimval::palette::light_green_400,
                   static constexpr int default_precision = 2;)

DIMVAL_DEFINE_UNIT(Wavelength,
                   "wavelength",
                   "λ",
                   "λ",
                   "wavelength",
                   "length",
                   1.0,
                   "ph:wave-sine",
                   ::dimval::palette::teal_500,
                   static constexpr int default_precision = 2;)

DIMVAL_DEFINE_UNIT(KilometerPerHour,
                   "km_per_h",
                   "km/h",
                   "km/h",
                   "kilometer per hour",
                   "velocity",
                   0.2777777777777778,
                   "mdi:speedometer",
                   ::dimval::palette::light_green_500,
                   static constexpr int default_precision = 1;)

DIMVAL_DEFINE_UNIT(Knot,
                   "kn",
                   "kn",
                   "kn",
                   "knot",
                   "velocity",
                   0.5144444444444445,
                   "mdi:sail-boat",
                   ::dimval::palette::light_green_600,
                   static constexpr int default_precision = 1;)
