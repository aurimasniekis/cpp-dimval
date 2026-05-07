#include <dimval/dimval.hpp>

#include <iostream>

namespace dv = dimval;

// A semantic specialization of Byte storage.
DIMVAL_DEFINE_MEASURE(StorageCapacity,
                      ::dimval::Byte,
                      "storage_capacity",
                      "Storage capacity",
                      "mdi:harddisk",
                      dv::palette::cyan_500)

int main() {
    dv::StorageCapacityValue disk = 512.0;
    std::cout << "disk = " << disk << "\n";
    std::cout << "disk (full) = " << std::format("{:full}", disk) << "\n";
    std::cout << "disk (json) = " << std::format("{:json}", disk) << "\n";
    return 0;
}
