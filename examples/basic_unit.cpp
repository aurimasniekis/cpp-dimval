#include <dimval/dimval.hpp>

#include <iostream>

namespace dv = dimval;

int main() {
    // Stack: implicit-from-numeric, or brace-init.
    const dv::MeterValue height = 1.78;
    const dv::MeterValue height2 = 1.78;
    (void)height2;
    std::cout << "height = " << height << "\n";

    // Heap-owned: of() returns shared, unique() returns unique.
    const dv::MeterValueShared shr = dv::MeterValue::of(2.0);
    const dv::MeterValueUnique uniq = dv::MeterValue::unique(3.0);
    std::cout << "shared heap height = " << *shr << " (refs=" << shr.use_count() << ")\n";
    std::cout << "unique heap height = " << *uniq << "\n";

    const dv::HourValue lap = 1.5;
    const auto lap_seconds = dv::convert<dv::Second>(lap);
    std::cout << "lap = " << lap << " = " << lap_seconds << "\n";

    const dv::CelsiusValue room_temp = 21.5;
    std::cout << "room temperature = " << room_temp << " (" << dv::convert<dv::Kelvin>(room_temp)
              << ")\n";

    return 0;
}
