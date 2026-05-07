#include <dimval/dimval.hpp>

#include <iostream>

namespace dv = dimval;

int main() {
    const auto safe_range = dv::CelsiusRangeValue::closed(15.0, 25.0);

    const dv::CelsiusValue reading = 22.3;
    std::cout << "safe range = " << safe_range << "\n";
    std::cout << "reading    = " << reading << "\n";
    std::cout << "in range?  = " << std::boolalpha << safe_range.contains(reading) << "\n";

    const auto warning_range = dv::CelsiusRangeValue::left_open(25.0, 35.0);
    std::cout << "overlap?   = " << safe_range.overlaps(warning_range) << "\n";
    if (const auto inter = safe_range.intersect(warning_range)) {
        std::cout << "intersect  = " << *inter << "\n";
    } else {
        std::cout << "no intersection\n";
    }

    if (const auto bad = dv::MeterRangeValue::make(10.0, 0.0); !bad.has_value()) {
        std::cout << "rejected inverted range as expected\n";
    }
    return 0;
}
