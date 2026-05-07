#pragma once

/// @file
/// @brief Abstract interfaces for runtime polymorphic handling of dimensional values.
///
/// `IUnitValue` and `IMeasureValue` are pure-virtual base classes implemented by
/// every `UnitValue<U,T>` / `MeasureValue<M,T>` template instantiation. They let
/// you store heterogeneous values in `std::vector<std::unique_ptr<IUnitValue>>`
/// or pass them across an ABI without seeing the concrete unit/measure tags.
///
/// The virtual surface is deliberately narrow: only the per-instance state
/// (numeric value, formatted rendering, deep copy) plus the descriptor accessor
/// needed to introspect metadata across the ABI boundary. Per-field metadata
/// (id, symbol, kind, ...) lives as `static constexpr` accessors on the concrete
/// `UnitValue<U,T>` / `MeasureValue<M,T>` templates and is reachable via
/// `descriptor()` from a polymorphic handle.

#include <dimval/descriptor.hpp>

#include <memory>
#include <string>
#include <vector>

namespace dimval {

/// Polymorphic interface implemented by every UnitValue<U,T>.
class IUnitValue {
public:
    IUnitValue() = default;
    IUnitValue(const IUnitValue&) = default;
    IUnitValue(IUnitValue&&) = default;
    IUnitValue& operator=(const IUnitValue&) = default;
    IUnitValue& operator=(IUnitValue&&) = default;
    virtual ~IUnitValue() = default;

    /// Full descriptor — read individual fields (`descriptor().id`, ...) from here.
    [[nodiscard]] virtual UnitDescriptor descriptor() const noexcept = 0;
    /// Numeric value as a double (lossy for >double types).
    [[nodiscard]] virtual double numeric_as_double() const noexcept = 0;

    /// Render `<value> <symbol>` (or whatever the descriptor's formatter dictates).
    [[nodiscard]] virtual std::string to_string() const = 0;
    /// Render with the descriptor's default precision applied.
    [[nodiscard]] virtual std::string to_formatted_string() const = 0;

    /// Deep copy as the interface type — the moral equivalent of a virtual copy ctor.
    [[nodiscard]] virtual std::unique_ptr<IUnitValue> clone() const = 0;
};

/// Owning handles to a polymorphic IUnitValue.
using IUnitValueUnique = std::unique_ptr<IUnitValue>;
using IUnitValueShared = std::shared_ptr<IUnitValue>;

/// Convenience aliases for collections of polymorphic values.
using IUnitValues = std::vector<IUnitValueShared>;
using IUnitUniqueValues = std::vector<IUnitValueUnique>;

/// Polymorphic interface implemented by every MeasureValue<M,T>.
class IMeasureValue {
public:
    IMeasureValue() = default;
    IMeasureValue(const IMeasureValue&) = default;
    IMeasureValue(IMeasureValue&&) = default;
    IMeasureValue& operator=(const IMeasureValue&) = default;
    IMeasureValue& operator=(IMeasureValue&&) = default;
    virtual ~IMeasureValue() = default;

    /// Measure descriptor — read fields like `descriptor().name` from here.
    [[nodiscard]] virtual MeasureDescriptor descriptor() const noexcept = 0;
    /// Underlying unit's descriptor — read `unit_descriptor().id`, `.symbol`, etc.
    [[nodiscard]] virtual UnitDescriptor unit_descriptor() const noexcept = 0;
    [[nodiscard]] virtual double numeric_as_double() const noexcept = 0;

    [[nodiscard]] virtual std::string to_string() const = 0;
    [[nodiscard]] virtual std::string to_formatted_string() const = 0;
    [[nodiscard]] virtual std::unique_ptr<IMeasureValue> clone() const = 0;
};

/// Owning handles to a polymorphic IMeasureValue.
using IMeasureValueUnique = std::unique_ptr<IMeasureValue>;
using IMeasureValueShared = std::shared_ptr<IMeasureValue>;

/// Convenience aliases for collections of polymorphic values.
using IMeasureValues = std::vector<IMeasureValueShared>;
using IMeasureUniqueValues = std::vector<IMeasureValueUnique>;

}  // namespace dimval
