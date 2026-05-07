#pragma once

/// @file
/// @brief Concepts and helper accessors that drive the static side of dimval.
///
/// Every unit/measure is a struct that derives from UnitBase / MeasureBase
/// (see <dimval/base.hpp>) and publishes its metadata as `static constexpr`
/// members. The concepts below detect that derivation; the helpers forward to
/// each struct's own `descriptor()` for source compatibility.

#include <dimval/base.hpp>
#include <dimval/descriptor.hpp>

#include <type_traits>

namespace dimval {

/// Concept satisfied by any struct that inherits from UnitBase.
template <typename U>
concept UnitLike = std::is_base_of_v<UnitTag, U>;

/// Concept satisfied by any struct that inherits from MeasureBase.
template <typename M>
concept MeasureLike = std::is_base_of_v<MeasureTag, M>;

/// Convenience accessor: descriptor of a unit struct.
template <UnitLike U>
[[nodiscard]] constexpr UnitDescriptor unit_descriptor_of() noexcept {
    return U::descriptor();
}

/// Convenience accessor: descriptor of a measure struct.
template <MeasureLike M>
[[nodiscard]] constexpr MeasureDescriptor measure_descriptor_of() noexcept {
    return M::descriptor();
}

/// True iff two unit structs share the same kind (and therefore convert).
template <UnitLike A, UnitLike B>
[[nodiscard]] constexpr bool units_compatible() noexcept {
    return A::kind == B::kind;
}

/// True iff a measure's base unit is the given unit.
template <MeasureLike M, UnitLike U>
[[nodiscard]] constexpr bool measure_uses_unit() noexcept {
    return std::is_same_v<typename M::base_unit_t, U>;
}

}  // namespace dimval
