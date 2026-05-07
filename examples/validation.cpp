#include <dimval/dimval.hpp>

#include <iostream>

namespace dv = dimval;

int main() {
    if (auto good = dv::MeterValue::parse("42.5 m")) {
        std::cout << "parsed: " << *good << "\n";
    }

    if (auto mismatch = dv::MeterValue::parse("3 km"); !mismatch) {
        std::cout << "unit mismatch (expected): " << mismatch.error().message << "\n";
    }

    if (auto invalid = dv::MeterValue::parse("not_a_number m"); !invalid) {
        std::cout << "invalid number (expected): " << invalid.error().message << "\n";
    }

    if (auto bad_range = dv::MeterRangeValue::make(10.0, 0.0); !bad_range) {
        std::cout << "inverted range rejected: " << bad_range.error().message << "\n";
    }

    if (auto dyn = dv::parse_dynamic_unit_value("125 dBm")) {
        std::cout << "dynamic parse: " << dyn->value << " " << dyn->desc->id
                  << " (kind=" << dyn->desc->kind << ")\n";
    }
    return 0;
}
