#pragma once

/// @file
/// @brief Throughput units. BitPerSecond canonical; BytePerSecond as the
///        Byte-based alt. SI-prefix variants are formatter-only.

#include <dimval/define.hpp>

DIMVAL_DEFINE_UNIT(BitPerSecond,
                   "bit/s",
                   "bit/s",
                   "bit/s",
                   "bits per second",
                   "data_rate",
                   1.0,
                   ::comms::Icons::mdi::transfer,
                   ::comms::Colors::mui::cyan[400],
                   static constexpr ::std::string_view formatter = "bitrate";
                   static constexpr int default_precision = 2;)

DIMVAL_DEFINE_UNIT(BytePerSecond,
                   "B/s",
                   "B/s",
                   "B/s",
                   "bytes per second",
                   "data_rate",
                   8.0,
                   ::comms::Icons::mdi::transfer,
                   ::comms::Colors::mui::cyan[500],
                   static constexpr ::std::string_view formatter = "bitrate";
                   static constexpr int default_precision = 2;)
