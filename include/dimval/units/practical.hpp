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
                   ::comms::Icons::mdi::clock_alert_outline,
                   ::comms::Colors::mui::blue[300],
                   static constexpr int default_precision = 2;)

DIMVAL_DEFINE_UNIT(RotationPerMinute,
                   "rpm",
                   "rpm",
                   "rpm",
                   "rotation per minute",
                   "rotational_frequency",
                   1.0,
                   ::comms::Icons::mdi::rotate_right,
                   ::comms::Colors::mui::light_blue[500],
                   static constexpr int default_precision = 0;)

DIMVAL_DEFINE_UNIT(MeterPerSecond,
                   "m_per_s",
                   "m/s",
                   "m/s",
                   "meter per second",
                   "velocity",
                   1.0,
                   ::comms::Icons::mdi::speedometer,
                   ::comms::Colors::mui::light_green[400],
                   static constexpr int default_precision = 2;)

DIMVAL_DEFINE_UNIT(Wavelength,
                   "wavelength",
                   "λ",
                   "λ",
                   "wavelength",
                   "length",
                   1.0,
                   ::comms::Icon::from("ph:wave-sine"),
                   ::comms::Colors::mui::teal[500],
                   static constexpr int default_precision = 2;)

DIMVAL_DEFINE_UNIT(KilometerPerHour,
                   "km_per_h",
                   "km/h",
                   "km/h",
                   "kilometer per hour",
                   "velocity",
                   0.2777777777777778,
                   ::comms::Icons::mdi::speedometer,
                   ::comms::Colors::mui::light_green[500],
                   static constexpr int default_precision = 1;)

DIMVAL_DEFINE_UNIT(Knot,
                   "kn",
                   "kn",
                   "kn",
                   "knot",
                   "velocity",
                   0.5144444444444445,
                   ::comms::Icons::mdi::sail_boat,
                   ::comms::Colors::mui::light_green[600],
                   static constexpr int default_precision = 1;)
