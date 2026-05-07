#include <dimval/dimval.hpp>

#include <iostream>

namespace dv = dimval;

int main() {
    // Parse: success and the six common failure shapes.
    if (auto v = dv::parse_unit_value<dv::Meter>("42.5 m")) {
        std::cout << "ok: " << *v << "\n";
    }

    if (auto v = dv::parse_unit_value<dv::Meter>("   "); !v) {
        std::cout << "empty input rejected: " << v.error().message << "\n";
    }

    if (auto v = dv::parse_unit_value<dv::Meter>("abc m"); !v) {
        std::cout << "invalid number rejected: " << v.error().message << "\n";
    }

    if (auto v = dv::parse_unit_value<dv::Meter>("42 kg"); !v) {
        std::cout << "unit mismatch rejected: " << v.error().message << "\n";
    }

    if (auto v = dv::parse_dynamic_unit_value("3.14 zorgs"); !v) {
        std::cout << "unknown unit rejected: " << v.error().message << "\n";
    }

    // Range: inverted bounds and empty open ranges are rejected.
    if (auto r = dv::MeterRangeValue::make(dv::unit_value<dv::Meter>(10.0),
                                           dv::unit_value<dv::Meter>(0.0));
        !r) {
        std::cout << "inverted range rejected: " << r.error().message << "\n";
    }

    if (auto r = dv::MeterRangeValue::make(dv::unit_value<dv::Meter>(5.0),
                                           dv::unit_value<dv::Meter>(5.0),
                                           dv::RangeInclusion::open());
        !r) {
        std::cout << "empty open range rejected: " << r.error().message << "\n";
    }

    return 0;
}
