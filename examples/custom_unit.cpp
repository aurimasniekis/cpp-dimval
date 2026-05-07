#include <dimval/dimval.hpp>

#include <iostream>

namespace dv = dimval;

// Frame: a count event with no SI parent. 16 subframes per frame.
DIMVAL_DEFINE_UNIT(Frame,
                   "frame",
                   "frm",
                   "frm",
                   "frame",
                   "frame_count",
                   1.0,
                   "mdi:movie-roll",
                   dv::palette::blue_400)

DIMVAL_DEFINE_UNIT(SubFrame,
                   "subframe",
                   "subfrm",
                   "subfrm",
                   "subframe",
                   "frame_count",
                   1.0 / 16.0,
                   "mdi:movie-roll-outline",
                   dv::palette::blue_300)

int main() {
    const dv::FrameValue frames = 2.0;
    const auto sub = dv::convert<dv::SubFrame>(frames);
    std::cout << "frames    = " << frames << "\n";
    std::cout << "subframes = " << sub << "\n";

    // Runtime registration of yet another unit (no compile-time tag needed).
    auto& reg = dv::UnitRegistry::global();
    reg.register_unit({
        .id = "knot",
        .symbol = "kn",
        .short_name = "kn",
        .long_name = "knot",
        .kind = "speed",
        .factor = 0.514444,
    });
    if (const auto* d = reg.find("kn")) {
        std::cout << "registered runtime unit: " << *d << "\n";
    }
    return 0;
}
