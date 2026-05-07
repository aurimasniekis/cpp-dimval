#pragma once

/// @file
/// @brief Umbrella header. Including this pulls in the entire public dimval API

#include <dimval/core.hpp>
#include <dimval/define.hpp>
#include <dimval/descriptor.hpp>
#include <dimval/format.hpp>
#include <dimval/hash.hpp>
#include <dimval/interface.hpp>
#include <dimval/json_nlohmann.hpp>
#include <dimval/measure.hpp>
#include <dimval/ostream.hpp>
#include <dimval/parcel.hpp>
#include <dimval/parse.hpp>
#include <dimval/range.hpp>
#include <dimval/registry.hpp>
#include <dimval/traits.hpp>
#include <dimval/unit.hpp>

// Built-in catalog.
#include <dimval/measures/antenna.hpp>
#include <dimval/measures/common.hpp>
#include <dimval/measures/digital.hpp>
#include <dimval/measures/electrical.hpp>
#include <dimval/measures/gnss.hpp>
#include <dimval/measures/mechanics.hpp>
#include <dimval/measures/rf_sdr.hpp>
#include <dimval/units/data.hpp>
#include <dimval/units/dimensionless.hpp>
#include <dimval/units/electrical.hpp>
#include <dimval/units/imperial.hpp>
#include <dimval/units/mechanics.hpp>
#include <dimval/units/practical.hpp>
#include <dimval/units/rate.hpp>
#include <dimval/units/rf.hpp>
#include <dimval/units/si.hpp>

namespace dimval {

/** @brief Library version as a dotted `MAJOR.MINOR.PATCH` string. */
inline constexpr std::string_view version = "0.1.0";

/** @brief Major version component. */
inline constexpr int version_major = 0;
/** @brief Minor version component. */
inline constexpr int version_minor = 1;
/** @brief Patch version component. */
inline constexpr int version_patch = 0;

}  // namespace dimval