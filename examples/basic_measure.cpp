#include <dimval/dimval.hpp>

#include <iostream>
#include <memory>
#include <vector>

namespace dv = dimval;

int main() {
    const dv::DistanceValue distance = 1500.0;
    const dv::DurationValue duration = 60.0;

    std::cout << "distance = " << distance << "\n";
    std::cout << "duration = " << duration << "\n";

    // Drop the measure tag and use the underlying unit value.
    const auto u = distance.as_unit_value();
    std::cout << "raw distance unit value = " << u << "\n";

    // Frequency is built on Hertz.
    const dv::CenterFrequencyValue carrier = 2.45e9;
    std::cout << "carrier = " << carrier << "\n";

    // IMeasureValue lets us mix-and-match unrelated measures in one container.
    dv::IMeasureUniqueValues readings;
    readings.push_back(dv::DistanceValue::unique(42.0));
    readings.push_back(dv::FrequencyValue::unique(1000.0));
    readings.push_back(dv::SnrValue::unique(15.5));
    for (const auto& r : readings) {
        std::cout << "  " << r->descriptor().name << ": " << r->to_string() << "\n";
    }

    return 0;
}
