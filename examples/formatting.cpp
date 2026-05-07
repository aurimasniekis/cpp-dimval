#include <dimval/dimval.hpp>

#include <format>
#include <iostream>

namespace dv = dimval;

int main() {
    dv::MeterValue d = 3.14159;

    std::cout << std::format("{}", d) << "\n";         // 3.14159 m
    std::cout << std::format("{:short}", d) << "\n";   // 3.14159m
    std::cout << std::format("{:full}", d) << "\n";    // 3.14159 meter
    std::cout << std::format("{:json}", d) << "\n";    // {"unit":"m","value":3.14159}
    std::cout << std::format("{:.2}", d) << "\n";      // 3.14 m
    std::cout << std::format("{:full.3}", d) << "\n";  // 3.142 meter

    // Ratio (canonical) carries a fraction; render-as-percent is the formatter's job.
    dv::RatioValue r = 0.75;
    std::cout << std::format("{}", r) << "\n";  // 0.75

    dv::DegreeValue a = 90.0;
    std::cout << std::format("{}", a) << "\n";  // 90.00°

    return 0;
}
