#pragma once

/// @file
/// @brief Data size units. Byte and Bit are kept as distinct (Byte = 8 bits);
///        SI-prefix variants (kB, MB, kbit, ...) are formatter-only.

#include <dimval/define.hpp>

DIMVAL_DEFINE_UNIT(Bit,
                   "bit",
                   "bit",
                   "bit",
                   "bit",
                   "data_size",
                   1.0,
                   "mdi:numeric-1-box-outline",
                   ::dimval::palette::cyan_400)

DIMVAL_DEFINE_UNIT(
    Byte, "B", "B", "B", "byte", "data_size", 8.0, "mdi:memory", ::dimval::palette::cyan_500)
