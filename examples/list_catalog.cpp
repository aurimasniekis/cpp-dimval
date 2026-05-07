#include <dimval/dimval.hpp>

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace dv = dimval;

int main() {
    const auto& units = dv::UnitRegistry::global();
    const auto& measures = dv::MeasureRegistry::global();

    // Group units by kind so the dump is legible at a glance.
    std::map<std::string, std::vector<dv::UnitDescriptor>> by_kind;
    for (const auto& u : units.list()) {
        by_kind[std::string{u.kind}].push_back(u);
    }

    std::cout << "Units (" << units.size() << " total across " << by_kind.size() << " kinds):\n";
    for (auto& [kind, group] : by_kind) {
        std::ranges::sort(group, [](const auto& a, const auto& b) { return a.id < b.id; });
        std::cout << "  [" << kind << "]";
        for (const auto& u : group) {
            std::cout << ' ' << u.id;
            if (!u.symbol.empty() && u.symbol != u.id) {
                std::cout << '(' << u.symbol << ')';
            }
        }
        std::cout << '\n';
    }

    auto m_list = measures.list();
    std::ranges::sort(m_list, [](const auto& a, const auto& b) { return a.id < b.id; });
    std::cout << "\nMeasures (" << measures.size() << " total):\n";
    for (const auto& m : m_list) {
        std::cout << "  " << m.id << " -> " << m.base_unit_id << "  (\"" << m.name << "\")\n";
    }
    return 0;
}
