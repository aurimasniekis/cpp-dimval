#include <dimval/dimval.hpp>

#include <nlohmann/json.hpp>

#include <iostream>

namespace dv = dimval;
using json = nlohmann::json;

int main() {
    dv::MeterValue height = 1.78;
    const json j = height;
    std::cout << "json: " << j.dump() << "\n";

    const auto roundtrip = j.get<dv::MeterValue>();
    std::cout << "round-trip value: " << roundtrip << "\n";

    dv::DistanceValue distance = 42.0;
    const json jm = distance;
    std::cout << "measure json: " << jm.dump() << "\n";

    auto r = dv::MeterRangeValue::closed(dv::MeterValue(0.0), dv::MeterValue(100.0));
    const json jr = r;
    std::cout << "range json: " << jr.dump() << "\n";

    return 0;
}
