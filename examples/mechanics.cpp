#include <dimval/dimval.hpp>

#include <iostream>

namespace dv = dimval;

int main() {
    // Speed / acceleration / area / density measures.
    const dv::SpeedValue cruise = 27.78;            // m/s ≈ 100 km/h
    const dv::AccelerationValue gravity = 9.80665;  // m/s²
    const dv::AreaValue plot = 250.0;               // m²
    const dv::DensityValue water = 1000.0;          // kg/m³

    std::cout << "cruise   = " << cruise << "\n";
    std::cout << "gravity  = " << gravity << "\n";
    std::cout << "plot     = " << plot << "\n";
    std::cout << "water    = " << water << "\n";

    // Imperial ↔ metric crossing through unit_value's compatible-kind rule.
    const auto trip_mi = dv::unit_value<dv::Mile>(60.0);
    const auto trip_m = dv::convert<dv::Meter>(trip_mi);
    std::cout << trip_mi << " = " << trip_m << "\n";

    const auto height = dv::unit_value<dv::Foot>(6.0);
    std::cout << height << " = " << dv::convert<dv::Meter>(height) << "\n";

    // Pressure cross-conversion.
    const auto tyre_psi = dv::unit_value<dv::PoundsPerSquareInch>(32.0);
    const auto tyre_bar = dv::convert<dv::Bar>(tyre_psi);
    std::cout << tyre_psi << " = " << tyre_bar << "\n";

    // Knots → m/s for navigation.
    const auto wind = dv::unit_value<dv::Knot>(15.0);
    std::cout << wind << " = " << dv::convert<dv::MeterPerSecond>(wind) << "\n";

    return 0;
}
