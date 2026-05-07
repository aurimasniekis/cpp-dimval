#include <dimval/dimval.hpp>

#include <iostream>

#include <parcel/parcel.h>

namespace dv = dimval;
using json = ::parcel::json_t;

int main() {
    dv::UnitValueCell<dv::Meter> height = 1.78;
    const json j = height.to_json();
    std::cout << "unit cell: " << j.dump() << "\n";

    ::parcel::ParcelRegistry reg;
    auto decoded = dv::UnitValueCell<dv::Meter>::from_json(j, reg);
    std::cout << "round-trip: " << decoded->to_string() << "\n";

    auto r = dv::DistanceRangeValue::closed(0.0, 100.0);
    dv::MeasureRangeValueCell<dv::Distance> range_cell{r};
    const json jr = range_cell.to_json();
    std::cout << "range cell: " << jr.dump() << "\n";

    return 0;
}
