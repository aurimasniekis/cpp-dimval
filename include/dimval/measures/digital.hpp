#pragma once

/// @file
/// @brief Digital / decoder / DSP measures.

#include <dimval/define.hpp>
#include <dimval/units/dimensionless.hpp>
#include <dimval/units/practical.hpp>
#include <dimval/units/rate.hpp>
#include <dimval/units/si.hpp>

DIMVAL_DEFINE_MEASURE(BitRate,
                      ::dimval::BitPerSecond,
                      "bit_rate",
                      "Bit Rate",
                      ::comms::Icons::mdi::transfer,
                      ::comms::Colors::mui::light_blue[400])

DIMVAL_DEFINE_MEASURE(ByteRate,
                      ::dimval::BytePerSecond,
                      "byte_rate",
                      "Byte Rate",
                      ::comms::Icons::mdi::transfer,
                      ::comms::Colors::mui::light_blue[400])

DIMVAL_DEFINE_MEASURE(Ber,
                      ::dimval::Percent,
                      "ber",
                      "Bit Error Rate",
                      ::comms::Icons::mdi::percent,
                      ::comms::Colors::mui::red[400],
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(Fer,
                      ::dimval::Percent,
                      "fer",
                      "Frame Error Rate",
                      ::comms::Icons::mdi::percent,
                      ::comms::Colors::mui::red[400],
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(PacketErrorRate,
                      ::dimval::Percent,
                      "packet_error_rate",
                      "Packet Error Rate",
                      ::comms::Icons::mdi::percent,
                      ::comms::Colors::mui::red[400],
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(Per,
                      ::dimval::Percent,
                      "per",
                      "Packet Error Rate",
                      ::comms::Icons::mdi::percent,
                      ::comms::Colors::mui::red[400],
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(FrameRate,
                      ::dimval::Hertz,
                      "frame_rate",
                      "Frame Rate",
                      ::comms::Icons::mdi::chart_timeline_variant,
                      ::comms::Colors::mui::light_blue[400])

DIMVAL_DEFINE_MEASURE(Latency,
                      ::dimval::Second,
                      "latency",
                      "Latency",
                      ::comms::Icons::mdi::timer_sand,
                      ::comms::Colors::mui::blue[400])

DIMVAL_DEFINE_MEASURE(Jitter,
                      ::dimval::Second,
                      "jitter",
                      "Jitter",
                      ::comms::Icons::mdi::chart_bell_curve,
                      ::comms::Colors::mui::blue[400])

DIMVAL_DEFINE_MEASURE(OffsetTime,
                      ::dimval::Second,
                      "offset_time",
                      "Time Offset",
                      ::comms::Icons::mdi::clock_outline,
                      ::comms::Colors::mui::cyan[400])

DIMVAL_DEFINE_MEASURE(RotationRate,
                      ::dimval::RotationPerMinute,
                      "rotation_rate",
                      "Rotation Rate",
                      ::comms::Icons::mdi::rotate_right,
                      ::comms::Colors::mui::light_green[400])
