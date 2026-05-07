#pragma once

/// @file
/// @brief Thread-safe runtime registries of unit and measure descriptors.
///
/// Built-in units and measures auto-register at static-initialization time
/// through the DIMVAL_DEFINE_UNIT / DIMVAL_DEFINE_MEASURE macros. User code
/// can register additional descriptors at runtime; lifetime of the
/// std::string_view fields is the caller's responsibility.

#include <dimval/descriptor.hpp>
#include <dimval/traits.hpp>

#include <mutex>
#include <shared_mutex>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

namespace dimval {

/// Registry of unit descriptors. Lookups are guarded by a shared lock,
/// registrations by a unique lock. Use UnitRegistry::global() for the
/// process-wide instance; built-ins live there.
class UnitRegistry {
public:
    UnitRegistry() = default;
    UnitRegistry(const UnitRegistry&) = delete;
    UnitRegistry& operator=(const UnitRegistry&) = delete;
    UnitRegistry(UnitRegistry&&) = delete;
    UnitRegistry& operator=(UnitRegistry&&) = delete;
    ~UnitRegistry() = default;

    /// Process-wide singleton.
    static UnitRegistry& global() {
        static UnitRegistry instance;
        return instance;
    }

    /// Register a descriptor. Existing entries with the same id are replaced.
    void register_unit(const UnitDescriptor& d) {
        const std::unique_lock lock{mutex_};
        register_unit_locked(d);
    }

    /// Register a unit by tag — pulls the descriptor through Unit::descriptor().
    /// Returns false if the id was already present (no replacement); true if
    /// this call inserted a fresh entry.
    template <UnitLike Unit>
    bool register_unit() {
        const auto d = Unit::descriptor();
        const std::unique_lock lock{mutex_};
        if (id_index_.contains(d.id)) {
            return false;
        }
        register_unit_locked(d);
        return true;
    }

    /// Look up by id, then by symbol. Returns nullptr if not found.
    [[nodiscard]] const UnitDescriptor* find(const std::string_view id_or_symbol) const {
        const std::shared_lock lock{mutex_};
        if (const auto it = id_index_.find(id_or_symbol); it != id_index_.end()) {
            return &entries_[it->second];
        }
        if (const auto it = symbol_index_.find(id_or_symbol); it != symbol_index_.end()) {
            return &entries_[it->second];
        }
        return nullptr;
    }

    /// Snapshot all registered descriptors.
    [[nodiscard]] std::vector<UnitDescriptor> list() const {
        const std::shared_lock lock{mutex_};
        return entries_;
    }

    /// Snapshot all descriptors whose `kind` matches.
    [[nodiscard]] std::vector<UnitDescriptor> by_kind(const std::string_view kind) const {
        const std::shared_lock lock{mutex_};
        std::vector<UnitDescriptor> out;
        for (const auto& e : entries_) {
            if (e.kind == kind) {
                out.push_back(e);
            }
        }
        return out;
    }

    /// True iff both ids resolve and share the same kind.
    [[nodiscard]] bool compatible(const std::string_view a, const std::string_view b) const {
        const std::shared_lock lock{mutex_};
        const auto* da = find_locked(a);
        const auto* db = find_locked(b);
        return da != nullptr && db != nullptr && da->kind == db->kind;
    }

    /// Number of registered descriptors.
    [[nodiscard]] std::size_t size() const {
        const std::shared_lock lock{mutex_};
        return entries_.size();
    }

private:
    [[nodiscard]] const UnitDescriptor* find_locked(const std::string_view key) const {
        if (const auto it = id_index_.find(key); it != id_index_.end()) {
            return &entries_[it->second];
        }
        if (const auto it = symbol_index_.find(key); it != symbol_index_.end()) {
            return &entries_[it->second];
        }
        return nullptr;
    }

    void register_unit_locked(const UnitDescriptor& d) {
        if (const auto it = id_index_.find(d.id); it != id_index_.end()) {
            entries_[it->second] = d;
        } else {
            const auto idx = entries_.size();
            entries_.push_back(d);
            id_index_[d.id] = idx;
            if (!d.symbol.empty() && d.symbol != d.id) {
                symbol_index_[d.symbol] = idx;
            }
        }
    }

    mutable std::shared_mutex mutex_;
    std::vector<UnitDescriptor> entries_;
    std::unordered_map<std::string_view, std::size_t> id_index_;
    std::unordered_map<std::string_view, std::size_t> symbol_index_;
};

/// Registry of measure descriptors.
class MeasureRegistry {
public:
    MeasureRegistry() = default;
    MeasureRegistry(const MeasureRegistry&) = delete;
    MeasureRegistry& operator=(const MeasureRegistry&) = delete;
    MeasureRegistry(MeasureRegistry&&) = delete;
    MeasureRegistry& operator=(MeasureRegistry&&) = delete;
    ~MeasureRegistry() = default;

    /// Process-wide singleton.
    static MeasureRegistry& global() {
        static MeasureRegistry instance;
        return instance;
    }

    /// Register a descriptor. Existing entries with the same id are replaced.
    void register_measure(const MeasureDescriptor& d) {
        const std::unique_lock lock{mutex_};
        register_measure_locked(d);
    }

    /// Register a measure by tag — pulls the descriptor through
    /// Measure::descriptor(). Returns false if the id was already present.
    template <MeasureLike Measure>
    bool register_measure() {
        const auto d = Measure::descriptor();
        const std::unique_lock lock{mutex_};
        if (id_index_.contains(d.id)) {
            return false;
        }
        register_measure_locked(d);
        return true;
    }

    [[nodiscard]] const MeasureDescriptor* find(const std::string_view id) const {
        const std::shared_lock lock{mutex_};
        if (const auto it = id_index_.find(id); it != id_index_.end()) {
            return &entries_[it->second];
        }
        return nullptr;
    }

    [[nodiscard]] std::vector<MeasureDescriptor> list() const {
        const std::shared_lock lock{mutex_};
        return entries_;
    }

    /// True iff `measure_id` and `unit_id` both resolve and the measure's
    /// declared base unit equals `unit_id`.
    [[nodiscard]] bool compatible(const std::string_view measure_id,
                                  const std::string_view unit_id) const {
        const std::shared_lock lock{mutex_};
        if (const auto it = id_index_.find(measure_id); it != id_index_.end()) {
            return entries_[it->second].base_unit_id == unit_id;
        }
        return false;
    }

    [[nodiscard]] std::size_t size() const {
        const std::shared_lock lock{mutex_};
        return entries_.size();
    }

private:
    void register_measure_locked(const MeasureDescriptor& d) {
        if (const auto it = id_index_.find(d.id); it != id_index_.end()) {
            entries_[it->second] = d;
        } else {
            const auto idx = entries_.size();
            entries_.push_back(d);
            id_index_[d.id] = idx;
        }
    }

    mutable std::shared_mutex mutex_;
    std::vector<MeasureDescriptor> entries_;
    std::unordered_map<std::string_view, std::size_t> id_index_;
};

namespace detail {

/// Helper invoked by the DIMVAL_DEFINE_UNIT macro at static-init time. Calls
/// the tag-based register_unit<Unit>() so the registry mirrors the source-of-
/// truth descriptor pulled through Unit::descriptor().
template <UnitLike Unit>
[[maybe_unused]] inline int register_unit_tag() {
    UnitRegistry::global().register_unit<Unit>();
    return 0;
}

/// Helper invoked by the DIMVAL_DEFINE_MEASURE macro at static-init time.
template <MeasureLike Measure>
[[maybe_unused]] inline int register_measure_tag() {
    MeasureRegistry::global().register_measure<Measure>();
    return 0;
}

}  // namespace detail

}  // namespace dimval
