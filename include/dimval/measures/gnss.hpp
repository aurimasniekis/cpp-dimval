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
                      "mdi:latitude",
                      ::dimval::palette::teal_400,
                      static constexpr int default_precision = 6;)

DIMVAL_DEFINE_MEASURE(Longitude,
                      ::dimval::Degree,
                      "longitude",
                      "Longitude",
                      "mdi:longitude",
                      ::dimval::palette::teal_400,
                      static constexpr int default_precision = 6;)

DIMVAL_DEFINE_MEASURE(Altitude,
                      ::dimval::Meter,
                      "altitude",
                      "Altitude",
                      "mdi:image-filter-hdr",
                      ::dimval::palette::teal_400,
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(GeoidSeparation,
                      ::dimval::Meter,
                      "geoid_separation",
                      "Geoid Separation",
                      "mdi:image-filter-hdr",
                      ::dimval::palette::teal_400,
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(GroundSpeed,
                      ::dimval::MeterPerSecond,
                      "ground_speed",
                      "Ground Speed",
                      "mdi:speedometer",
                      ::dimval::palette::light_green_400)

DIMVAL_DEFINE_MEASURE(VerticalSpeed,
                      ::dimval::MeterPerSecond,
                      "vertical_speed",
                      "Vertical Speed",
                      "mdi:speedometer",
                      ::dimval::palette::light_green_500)

DIMVAL_DEFINE_MEASURE(CourseOverGround,
                      ::dimval::Degree,
                      "course_over_ground",
                      "Course Over Ground",
                      "mdi:compass",
                      ::dimval::palette::deep_purple_400)

DIMVAL_DEFINE_MEASURE(Heading,
                      ::dimval::Degree,
                      "heading",
                      "Heading",
                      "mdi:compass",
                      ::dimval::palette::deep_purple_400)

DIMVAL_DEFINE_MEASURE(PositionAccuracy,
                      ::dimval::Meter,
                      "position_accuracy",
                      "Position Accuracy",
                      "mdi:crosshairs-gps",
                      ::dimval::palette::teal_500,
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(HorizontalAccuracy,
                      ::dimval::Meter,
                      "horizontal_accuracy",
                      "Horizontal Accuracy",
                      "mdi:crosshairs-gps",
                      ::dimval::palette::teal_500,
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(VerticalAccuracy,
                      ::dimval::Meter,
                      "vertical_accuracy",
                      "Vertical Accuracy",
                      "mdi:crosshairs-gps",
                      ::dimval::palette::teal_500,
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(TimeAccuracy,
                      ::dimval::Second,
                      "time_accuracy",
                      "Time Accuracy",
                      "mdi:clock-check-outline",
                      ::dimval::palette::blue_400)

DIMVAL_DEFINE_MEASURE(DilutionOfPrecision,
                      ::dimval::Percent,
                      "dop",
                      "Dilution of Precision",
                      "mdi:crosshairs-question",
                      ::dimval::palette::red_400,
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(Hdop,
                      ::dimval::Percent,
                      "hdop",
                      "Horizontal Dilution of Precision",
                      "mdi:crosshairs-question",
                      ::dimval::palette::red_400,
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(Vdop,
                      ::dimval::Percent,
                      "vdop",
                      "Vertical Dilution of Precision",
                      "mdi:crosshairs-question",
                      ::dimval::palette::red_400,
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(Pdop,
                      ::dimval::Percent,
                      "pdop",
                      "Position Dilution of Precision",
                      "mdi:crosshairs-question",
                      ::dimval::palette::red_400,
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(Tdop,
                      ::dimval::Percent,
                      "tdop",
                      "Time Dilution of Precision",
                      "mdi:crosshairs-question",
                      ::dimval::palette::red_400,
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(CarrierToNoiseDensity,
                      ::dimval::Decibel,
                      "cn0",
                      "Carrier-to-Noise Density",
                      "mdi:satellite-variant",
                      ::dimval::palette::green_400)

DIMVAL_DEFINE_MEASURE(Pseudorange,
                      ::dimval::Meter,
                      "pseudorange",
                      "Pseudorange",
                      "mdi:satellite-variant",
                      ::dimval::palette::teal_500,
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(CarrierPhase,
                      ::dimval::PhaseRadian,
                      "carrier_phase",
                      "Carrier Phase",
                      "mdi:satellite-variant",
                      ::dimval::palette::deep_purple_500)
