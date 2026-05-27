#pragma once

/// @file
/// @brief GNSS / GPS measures.

#include <dimval/define.hpp>
#include <dimval/units/dimensionless.hpp>
#include <dimval/units/practical.hpp>
#include <dimval/units/rf.hpp>
#include <dimval/units/si.hpp>

DIMVAL_DEFINE_MEASURE(Latitude,
                      ::dimval::Degree,
                      "latitude",
                      "Latitude",
                      ::comms::Icons::mdi::latitude,
                      ::comms::Colors::mui::teal[400],
                      static constexpr int default_precision = 6;)

DIMVAL_DEFINE_MEASURE(Longitude,
                      ::dimval::Degree,
                      "longitude",
                      "Longitude",
                      ::comms::Icons::mdi::longitude,
                      ::comms::Colors::mui::teal[400],
                      static constexpr int default_precision = 6;)

DIMVAL_DEFINE_MEASURE(Altitude,
                      ::dimval::Meter,
                      "altitude",
                      "Altitude",
                      ::comms::Icons::mdi::image_filter_hdr,
                      ::comms::Colors::mui::teal[400],
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(GeoidSeparation,
                      ::dimval::Meter,
                      "geoid_separation",
                      "Geoid Separation",
                      ::comms::Icons::mdi::image_filter_hdr,
                      ::comms::Colors::mui::teal[400],
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(GroundSpeed,
                      ::dimval::MeterPerSecond,
                      "ground_speed",
                      "Ground Speed",
                      ::comms::Icons::mdi::speedometer,
                      ::comms::Colors::mui::light_green[400])

DIMVAL_DEFINE_MEASURE(VerticalSpeed,
                      ::dimval::MeterPerSecond,
                      "vertical_speed",
                      "Vertical Speed",
                      ::comms::Icons::mdi::speedometer,
                      ::comms::Colors::mui::light_green[500])

DIMVAL_DEFINE_MEASURE(CourseOverGround,
                      ::dimval::Degree,
                      "course_over_ground",
                      "Course Over Ground",
                      ::comms::Icons::mdi::compass,
                      ::comms::Colors::mui::deep_purple[400])

DIMVAL_DEFINE_MEASURE(Heading,
                      ::dimval::Degree,
                      "heading",
                      "Heading",
                      ::comms::Icons::mdi::compass,
                      ::comms::Colors::mui::deep_purple[400])

DIMVAL_DEFINE_MEASURE(PositionAccuracy,
                      ::dimval::Meter,
                      "position_accuracy",
                      "Position Accuracy",
                      ::comms::Icons::mdi::crosshairs_gps,
                      ::comms::Colors::mui::teal[500],
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(HorizontalAccuracy,
                      ::dimval::Meter,
                      "horizontal_accuracy",
                      "Horizontal Accuracy",
                      ::comms::Icons::mdi::crosshairs_gps,
                      ::comms::Colors::mui::teal[500],
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(VerticalAccuracy,
                      ::dimval::Meter,
                      "vertical_accuracy",
                      "Vertical Accuracy",
                      ::comms::Icons::mdi::crosshairs_gps,
                      ::comms::Colors::mui::teal[500],
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(TimeAccuracy,
                      ::dimval::Second,
                      "time_accuracy",
                      "Time Accuracy",
                      ::comms::Icons::mdi::clock_check_outline,
                      ::comms::Colors::mui::blue[400])

DIMVAL_DEFINE_MEASURE(DilutionOfPrecision,
                      ::dimval::Percent,
                      "dop",
                      "Dilution of Precision",
                      ::comms::Icons::mdi::crosshairs_question,
                      ::comms::Colors::mui::red[400],
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(Hdop,
                      ::dimval::Percent,
                      "hdop",
                      "Horizontal Dilution of Precision",
                      ::comms::Icons::mdi::crosshairs_question,
                      ::comms::Colors::mui::red[400],
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(Vdop,
                      ::dimval::Percent,
                      "vdop",
                      "Vertical Dilution of Precision",
                      ::comms::Icons::mdi::crosshairs_question,
                      ::comms::Colors::mui::red[400],
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(Pdop,
                      ::dimval::Percent,
                      "pdop",
                      "Position Dilution of Precision",
                      ::comms::Icons::mdi::crosshairs_question,
                      ::comms::Colors::mui::red[400],
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(Tdop,
                      ::dimval::Percent,
                      "tdop",
                      "Time Dilution of Precision",
                      ::comms::Icons::mdi::crosshairs_question,
                      ::comms::Colors::mui::red[400],
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(CarrierToNoiseDensity,
                      ::dimval::Decibel,
                      "cn0",
                      "Carrier-to-Noise Density",
                      ::comms::Icons::mdi::satellite_variant,
                      ::comms::Colors::mui::green[400])

DIMVAL_DEFINE_MEASURE(Pseudorange,
                      ::dimval::Meter,
                      "pseudorange",
                      "Pseudorange",
                      ::comms::Icons::mdi::satellite_variant,
                      ::comms::Colors::mui::teal[500],
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(CarrierPhase,
                      ::dimval::PhaseRadian,
                      "carrier_phase",
                      "Carrier Phase",
                      ::comms::Icons::mdi::satellite_variant,
                      ::comms::Colors::mui::deep_purple[500])
