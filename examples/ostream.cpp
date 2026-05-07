#include <dimval/dimval.hpp>

#include <iostream>

namespace dv = dimval;

int main() {
    std::cout << dv::MeterValue(1.5) << "\n";
    std::cout << dv::KilogramValue(80.0) << "\n";
    std::cout << dv::HertzValue(2.4e9) << "\n";

    const auto r = dv::MeterRangeValue::closed(0.0, 100.0);
    std::cout << r << "\n";

    std::cout << dv::Meter::descriptor() << "\n";
    return 0;
}
