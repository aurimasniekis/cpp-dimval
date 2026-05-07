#include <dimval/dimval.hpp>

#include <iostream>

namespace dv = dimval;

int main() {
    const auto& unit_reg = dv::UnitRegistry::global();
    const auto& measure_reg = dv::MeasureRegistry::global();

    std::cout << "registered units: " << unit_reg.size() << "\n";
    std::cout << "registered measures: " << measure_reg.size() << "\n";

    std::cout << "all length units:\n";
    for (const auto& d : unit_reg.by_kind("length")) {
        std::cout << "  " << d << "\n";
    }

    if (const auto* d = unit_reg.find("Hz")) {
        std::cout << "found 'Hz': " << *d << "\n";
    }
    if (const auto* d = measure_reg.find("snr")) {
        std::cout << "found measure 'snr': " << *d << "\n";
    }
    std::cout << "m and km compatible? " << std::boolalpha << unit_reg.compatible("m", "km")
              << "\n";
    std::cout << "m and kg compatible? " << unit_reg.compatible("m", "kg") << "\n";
    return 0;
}
