#pragma once

/// @file
/// @brief Material UI color palette as `string_view` constants.
///
/// Mirrors the values exported from `@mui/material/colors` so C++ color
/// choices stay in lock-step with UI palettes that consume the same names.
/// Use these as the `Color` argument to DIMVAL_DEFINE_UNIT / DIMVAL_DEFINE_MEASURE.

#include <string_view>

namespace dimval::palette {

// red
inline constexpr std::string_view red_50 = "#ffebee";
inline constexpr std::string_view red_100 = "#ffcdd2";
inline constexpr std::string_view red_200 = "#ef9a9a";
inline constexpr std::string_view red_300 = "#e57373";
inline constexpr std::string_view red_400 = "#ef5350";
inline constexpr std::string_view red_500 = "#f44336";
inline constexpr std::string_view red_600 = "#e53935";
inline constexpr std::string_view red_700 = "#d32f2f";
inline constexpr std::string_view red_800 = "#c62828";
inline constexpr std::string_view red_900 = "#b71c1c";

// pink
inline constexpr std::string_view pink_50 = "#fce4ec";
inline constexpr std::string_view pink_100 = "#f8bbd0";
inline constexpr std::string_view pink_200 = "#f48fb1";
inline constexpr std::string_view pink_300 = "#f06292";
inline constexpr std::string_view pink_400 = "#ec407a";
inline constexpr std::string_view pink_500 = "#e91e63";
inline constexpr std::string_view pink_600 = "#d81b60";
inline constexpr std::string_view pink_700 = "#c2185b";
inline constexpr std::string_view pink_800 = "#ad1457";
inline constexpr std::string_view pink_900 = "#880e4f";

// purple
inline constexpr std::string_view purple_50 = "#f3e5f5";
inline constexpr std::string_view purple_100 = "#e1bee7";
inline constexpr std::string_view purple_200 = "#ce93d8";
inline constexpr std::string_view purple_300 = "#ba68c8";
inline constexpr std::string_view purple_400 = "#ab47bc";
inline constexpr std::string_view purple_500 = "#9c27b0";
inline constexpr std::string_view purple_600 = "#8e24aa";
inline constexpr std::string_view purple_700 = "#7b1fa2";
inline constexpr std::string_view purple_800 = "#6a1b9a";
inline constexpr std::string_view purple_900 = "#4a148c";

// deep_purple
inline constexpr std::string_view deep_purple_50 = "#ede7f6";
inline constexpr std::string_view deep_purple_100 = "#d1c4e9";
inline constexpr std::string_view deep_purple_200 = "#b39ddb";
inline constexpr std::string_view deep_purple_300 = "#9575cd";
inline constexpr std::string_view deep_purple_400 = "#7e57c2";
inline constexpr std::string_view deep_purple_500 = "#673ab7";
inline constexpr std::string_view deep_purple_600 = "#5e35b1";
inline constexpr std::string_view deep_purple_700 = "#512da8";
inline constexpr std::string_view deep_purple_800 = "#4527a0";
inline constexpr std::string_view deep_purple_900 = "#311b92";

// indigo
inline constexpr std::string_view indigo_50 = "#e8eaf6";
inline constexpr std::string_view indigo_100 = "#c5cae9";
inline constexpr std::string_view indigo_200 = "#9fa8da";
inline constexpr std::string_view indigo_300 = "#7986cb";
inline constexpr std::string_view indigo_400 = "#5c6bc0";
inline constexpr std::string_view indigo_500 = "#3f51b5";
inline constexpr std::string_view indigo_600 = "#3949ab";
inline constexpr std::string_view indigo_700 = "#303f9f";
inline constexpr std::string_view indigo_800 = "#283593";
inline constexpr std::string_view indigo_900 = "#1a237e";

// blue
inline constexpr std::string_view blue_50 = "#e3f2fd";
inline constexpr std::string_view blue_100 = "#bbdefb";
inline constexpr std::string_view blue_200 = "#90caf9";
inline constexpr std::string_view blue_300 = "#64b5f6";
inline constexpr std::string_view blue_400 = "#42a5f5";
inline constexpr std::string_view blue_500 = "#2196f3";
inline constexpr std::string_view blue_600 = "#1e88e5";
inline constexpr std::string_view blue_700 = "#1976d2";
inline constexpr std::string_view blue_800 = "#1565c0";
inline constexpr std::string_view blue_900 = "#0d47a1";

// light_blue
inline constexpr std::string_view light_blue_50 = "#e1f5fe";
inline constexpr std::string_view light_blue_100 = "#b3e5fc";
inline constexpr std::string_view light_blue_200 = "#81d4fa";
inline constexpr std::string_view light_blue_300 = "#4fc3f7";
inline constexpr std::string_view light_blue_400 = "#29b6f6";
inline constexpr std::string_view light_blue_500 = "#03a9f4";
inline constexpr std::string_view light_blue_600 = "#039be5";
inline constexpr std::string_view light_blue_700 = "#0288d1";
inline constexpr std::string_view light_blue_800 = "#0277bd";
inline constexpr std::string_view light_blue_900 = "#01579b";

// cyan
inline constexpr std::string_view cyan_50 = "#e0f7fa";
inline constexpr std::string_view cyan_100 = "#b2ebf2";
inline constexpr std::string_view cyan_200 = "#80deea";
inline constexpr std::string_view cyan_300 = "#4dd0e1";
inline constexpr std::string_view cyan_400 = "#26c6da";
inline constexpr std::string_view cyan_500 = "#00bcd4";
inline constexpr std::string_view cyan_600 = "#00acc1";
inline constexpr std::string_view cyan_700 = "#0097a7";
inline constexpr std::string_view cyan_800 = "#00838f";
inline constexpr std::string_view cyan_900 = "#006064";

// teal
inline constexpr std::string_view teal_50 = "#e0f2f1";
inline constexpr std::string_view teal_100 = "#b2dfdb";
inline constexpr std::string_view teal_200 = "#80cbc4";
inline constexpr std::string_view teal_300 = "#4db6ac";
inline constexpr std::string_view teal_400 = "#26a69a";
inline constexpr std::string_view teal_500 = "#009688";
inline constexpr std::string_view teal_600 = "#00897b";
inline constexpr std::string_view teal_700 = "#00796b";
inline constexpr std::string_view teal_800 = "#00695c";
inline constexpr std::string_view teal_900 = "#004d40";

// green
inline constexpr std::string_view green_50 = "#e8f5e9";
inline constexpr std::string_view green_100 = "#c8e6c9";
inline constexpr std::string_view green_200 = "#a5d6a7";
inline constexpr std::string_view green_300 = "#81c784";
inline constexpr std::string_view green_400 = "#66bb6a";
inline constexpr std::string_view green_500 = "#4caf50";
inline constexpr std::string_view green_600 = "#43a047";
inline constexpr std::string_view green_700 = "#388e3c";
inline constexpr std::string_view green_800 = "#2e7d32";
inline constexpr std::string_view green_900 = "#1b5e20";

// light_green
inline constexpr std::string_view light_green_50 = "#f1f8e9";
inline constexpr std::string_view light_green_100 = "#dcedc8";
inline constexpr std::string_view light_green_200 = "#c5e1a5";
inline constexpr std::string_view light_green_300 = "#aed581";
inline constexpr std::string_view light_green_400 = "#9ccc65";
inline constexpr std::string_view light_green_500 = "#8bc34a";
inline constexpr std::string_view light_green_600 = "#7cb342";
inline constexpr std::string_view light_green_700 = "#689f38";
inline constexpr std::string_view light_green_800 = "#558b2f";
inline constexpr std::string_view light_green_900 = "#33691e";

// lime
inline constexpr std::string_view lime_50 = "#f9fbe7";
inline constexpr std::string_view lime_100 = "#f0f4c3";
inline constexpr std::string_view lime_200 = "#e6ee9c";
inline constexpr std::string_view lime_300 = "#dce775";
inline constexpr std::string_view lime_400 = "#d4e157";
inline constexpr std::string_view lime_500 = "#cddc39";
inline constexpr std::string_view lime_600 = "#c0ca33";
inline constexpr std::string_view lime_700 = "#afb42b";
inline constexpr std::string_view lime_800 = "#9e9d24";
inline constexpr std::string_view lime_900 = "#827717";

// yellow
inline constexpr std::string_view yellow_50 = "#fffde7";
inline constexpr std::string_view yellow_100 = "#fff9c4";
inline constexpr std::string_view yellow_200 = "#fff59d";
inline constexpr std::string_view yellow_300 = "#fff176";
inline constexpr std::string_view yellow_400 = "#ffee58";
inline constexpr std::string_view yellow_500 = "#ffeb3b";
inline constexpr std::string_view yellow_600 = "#fdd835";
inline constexpr std::string_view yellow_700 = "#fbc02d";
inline constexpr std::string_view yellow_800 = "#f9a825";
inline constexpr std::string_view yellow_900 = "#f57f17";

// amber
inline constexpr std::string_view amber_50 = "#fff8e1";
inline constexpr std::string_view amber_100 = "#ffecb3";
inline constexpr std::string_view amber_200 = "#ffe082";
inline constexpr std::string_view amber_300 = "#ffd54f";
inline constexpr std::string_view amber_400 = "#ffca28";
inline constexpr std::string_view amber_500 = "#ffc107";
inline constexpr std::string_view amber_600 = "#ffb300";
inline constexpr std::string_view amber_700 = "#ffa000";
inline constexpr std::string_view amber_800 = "#ff8f00";
inline constexpr std::string_view amber_900 = "#ff6f00";

// orange
inline constexpr std::string_view orange_50 = "#fff3e0";
inline constexpr std::string_view orange_100 = "#ffe0b2";
inline constexpr std::string_view orange_200 = "#ffcc80";
inline constexpr std::string_view orange_300 = "#ffb74d";
inline constexpr std::string_view orange_400 = "#ffa726";
inline constexpr std::string_view orange_500 = "#ff9800";
inline constexpr std::string_view orange_600 = "#fb8c00";
inline constexpr std::string_view orange_700 = "#f57c00";
inline constexpr std::string_view orange_800 = "#ef6c00";
inline constexpr std::string_view orange_900 = "#e65100";

// deep_orange
inline constexpr std::string_view deep_orange_50 = "#fbe9e7";
inline constexpr std::string_view deep_orange_100 = "#ffccbc";
inline constexpr std::string_view deep_orange_200 = "#ffab91";
inline constexpr std::string_view deep_orange_300 = "#ff8a65";
inline constexpr std::string_view deep_orange_400 = "#ff7043";
inline constexpr std::string_view deep_orange_500 = "#ff5722";
inline constexpr std::string_view deep_orange_600 = "#f4511e";
inline constexpr std::string_view deep_orange_700 = "#e64a19";
inline constexpr std::string_view deep_orange_800 = "#d84315";
inline constexpr std::string_view deep_orange_900 = "#bf360c";

// brown
inline constexpr std::string_view brown_50 = "#efebe9";
inline constexpr std::string_view brown_100 = "#d7ccc8";
inline constexpr std::string_view brown_200 = "#bcaaa4";
inline constexpr std::string_view brown_300 = "#a1887f";
inline constexpr std::string_view brown_400 = "#8d6e63";
inline constexpr std::string_view brown_500 = "#795548";
inline constexpr std::string_view brown_600 = "#6d4c41";
inline constexpr std::string_view brown_700 = "#5d4037";
inline constexpr std::string_view brown_800 = "#4e342e";
inline constexpr std::string_view brown_900 = "#3e2723";

// grey
inline constexpr std::string_view grey_50 = "#fafafa";
inline constexpr std::string_view grey_100 = "#f5f5f5";
inline constexpr std::string_view grey_200 = "#eeeeee";
inline constexpr std::string_view grey_300 = "#e0e0e0";
inline constexpr std::string_view grey_400 = "#bdbdbd";
inline constexpr std::string_view grey_500 = "#9e9e9e";
inline constexpr std::string_view grey_600 = "#757575";
inline constexpr std::string_view grey_700 = "#616161";
inline constexpr std::string_view grey_800 = "#424242";
inline constexpr std::string_view grey_900 = "#212121";

// blue_grey
inline constexpr std::string_view blue_grey_50 = "#eceff1";
inline constexpr std::string_view blue_grey_100 = "#cfd8dc";
inline constexpr std::string_view blue_grey_200 = "#b0bec5";
inline constexpr std::string_view blue_grey_300 = "#90a4ae";
inline constexpr std::string_view blue_grey_400 = "#78909c";
inline constexpr std::string_view blue_grey_500 = "#607d8b";
inline constexpr std::string_view blue_grey_600 = "#546e7a";
inline constexpr std::string_view blue_grey_700 = "#455a64";
inline constexpr std::string_view blue_grey_800 = "#37474f";
inline constexpr std::string_view blue_grey_900 = "#263238";

}  // namespace dimval::palette
