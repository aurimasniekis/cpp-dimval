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
                      "mdi:transfer",
                      ::dimval::palette::light_blue_400)

DIMVAL_DEFINE_MEASURE(ByteRate,
                      ::dimval::BytePerSecond,
                      "byte_rate",
                      "Byte Rate",
                      "mdi:transfer",
                      ::dimval::palette::light_blue_400)

DIMVAL_DEFINE_MEASURE(Ber,
                      ::dimval::Percent,
                      "ber",
                      "Bit Error Rate",
                      "mdi:percent",
                      ::dimval::palette::red_400,
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(Fer,
                      ::dimval::Percent,
                      "fer",
                      "Frame Error Rate",
                      "mdi:percent",
                      ::dimval::palette::red_400,
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(PacketErrorRate,
                      ::dimval::Percent,
                      "packet_error_rate",
                      "Packet Error Rate",
                      "mdi:percent",
                      ::dimval::palette::red_400,
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(Per,
                      ::dimval::Percent,
                      "per",
                      "Packet Error Rate",
                      "mdi:percent",
                      ::dimval::palette::red_400,
                      static constexpr int default_precision = 2;)

DIMVAL_DEFINE_MEASURE(FrameRate,
                      ::dimval::Hertz,
                      "frame_rate",
                      "Frame Rate",
                      "mdi:chart-timeline-variant",
                      ::dimval::palette::light_blue_400)

DIMVAL_DEFINE_MEASURE(
    Latency, ::dimval::Second, "latency", "Latency", "mdi:timer-sand", ::dimval::palette::blue_400)

DIMVAL_DEFINE_MEASURE(Jitter,
                      ::dimval::Second,
                      "jitter",
                      "Jitter",
                      "mdi:chart-bell-curve",
                      ::dimval::palette::blue_400)

DIMVAL_DEFINE_MEASURE(OffsetTime,
                      ::dimval::Second,
                      "offset_time",
                      "Time Offset",
                      "mdi:clock-outline",
                      ::dimval::palette::cyan_400)

DIMVAL_DEFINE_MEASURE(RotationRate,
                      ::dimval::RotationPerMinute,
                      "rotation_rate",
                      "Rotation Rate",
                      "mdi:rotate-right",
                      ::dimval::palette::light_green_400)
