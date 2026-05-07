#include <dimval/dimval.hpp>

#include <gtest/gtest.h>

#include <sstream>

namespace dv = dimval;

TEST(Ostream, UnitValue) {
    std::ostringstream os;
    os << dv::unit_value<dv::Meter>(1.5);
    EXPECT_EQ(os.str(), "1.5 m");
}

TEST(Ostream, MeasureValue) {
    std::ostringstream os;
    os << dv::measure_value<dv::Distance>(1.5);
    EXPECT_EQ(os.str(), "1.5 m");
}

TEST(Ostream, Range) {
    std::ostringstream os;
    const auto r = dv::UnitRangeValue<dv::Meter>::closed(dv::unit_value<dv::Meter>(1.0),
                                                         dv::unit_value<dv::Meter>(2.0));
    os << r;
    EXPECT_EQ(os.str(), "[1 m, 2 m]");
}

TEST(Ostream, UnitDescriptor) {
    std::ostringstream os;
    os << dv::Meter::descriptor();
    EXPECT_NE(os.str().find("id=m"), std::string::npos);
    EXPECT_NE(os.str().find("kind=length"), std::string::npos);
}
