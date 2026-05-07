#include <dimval/dimval.hpp>

#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

namespace dv = dimval;

int main() {
    std::vector<dv::MeterValue> v{
        3.0,
        1.0,
        2.0,
    };
    std::ranges::sort(v);
    for (const auto& x : v) {
        std::cout << x << "\n";
    }

    std::unordered_set<dv::MeterValue> set;
    set.insert(1.0);
    set.insert(1.0);
    set.insert(2.0);
    std::cout << "unique values: " << set.size() << "\n";
    return 0;
}
