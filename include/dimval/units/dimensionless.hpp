#pragma once

/// @file
/// @brief Dimensionless units. Percent / ppm / ppb are rendered by the
///        formatter; storage uses the canonical Ratio (1.0 = 100%).

#include <dimval/define.hpp>

// NOLINTNEXTLINE(readability-redundant-string-init)
DIMVAL_DEFINE_UNIT(Count,
                   "count",
                   "",
                   "",
                   "count",
                   "count",
                   1.0,
                   ::comms::Icons::mdi::counter,
                   ::comms::Colors::mui::grey[400],
                   static constexpr int default_precision = 0;
                   static constexpr bool no_space_before_symbol = true;)

// NOLINTNEXTLINE(readability-redundant-string-init)
DIMVAL_DEFINE_UNIT(Ratio,
                   "ratio",
                   "",
                   "",
                   "ratio",
                   "ratio",
                   1.0,
                   ::comms::Icons::mdi::percent_outline,
                   ::comms::Colors::mui::grey[400])

// NOLINTNEXTLINE(readability-redundant-string-init)
DIMVAL_DEFINE_UNIT(Dimensionless,
                   "dimensionless",
                   "",
                   "",
                   "dimensionless",
                   "dimensionless",
                   1.0,
                   ::comms::Icons::mdi::variable,
                   ::comms::Colors::mui::grey[400],
                   static constexpr bool no_space_before_symbol = true;)

DIMVAL_DEFINE_UNIT(Percent,
                   "percent",
                   "%",
                   "%",
                   "percent",
                   "ratio",
                   0.01,
                   ::comms::Icons::mdi::percent,
                   ::comms::Colors::mui::grey[400],
                   static constexpr ::std::string_view formatter = "percent";
                   static constexpr int default_precision = 2;
                   static constexpr bool no_space_before_symbol = true;)

DIMVAL_DEFINE_UNIT(PartsPerMillion,
                   "ppm",
                   "ppm",
                   "ppm",
                   "parts per million",
                   "ratio",
                   1e-6,
                   ::comms::Icons::mdi::tune_variant,
                   ::comms::Colors::mui::cyan[400],
                   static constexpr int default_precision = 2;)

DIMVAL_DEFINE_UNIT(PartsPerBillion,
                   "ppb",
                   "ppb",
                   "ppb",
                   "parts per billion",
                   "ratio",
                   1e-9,
                   ::comms::Icons::mdi::tune,
                   ::comms::Colors::mui::cyan[500],
                   static constexpr int default_precision = 2;)
