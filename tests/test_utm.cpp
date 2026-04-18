#include <gtest/gtest.h>
#include "fastgeom3d/geodesy.h"

using namespace fastgeom3d;

TEST(UTMCoordinateTests, Construction) {
    UTMCoordinate utm(33, true, 500000.0, 4000000.0, 100.0);
    EXPECT_EQ(utm.zoneNumber, 33);
    EXPECT_TRUE(utm.northernHemisphere);
    EXPECT_DOUBLE_EQ(utm.easting, 500000.0);
    EXPECT_DOUBLE_EQ(utm.northing, 4000000.0);
    EXPECT_DOUBLE_EQ(utm.elevation, 100.0);
}

TEST(UTMCoordinateTests, ConstructionInvalidZone) {
    EXPECT_THROW(UTMCoordinate(0, true, 500000.0, 4000000.0, 100.0), std::invalid_argument);
    EXPECT_THROW(UTMCoordinate(61, true, 500000.0, 4000000.0, 100.0), std::invalid_argument);
}

TEST(UTMCoordinateTests, FromLatLon) {
    UTMCoordinate utm = UTMCoordinate::fromLatLon(35.0, 139.0, 100.0);
    EXPECT_GE(utm.zoneNumber, 1);
    EXPECT_LE(utm.zoneNumber, 60);
    EXPECT_DOUBLE_EQ(utm.elevation, 100.0);
}

TEST(UTMCoordinateTests, ToVec3) {
    UTMCoordinate utm(33, true, 500000.0, 4000000.0, 100.0);
    Vec3 point = utm.toVec3();
    EXPECT_DOUBLE_EQ(point.z, 100.0);
    EXPECT_GT(point.x, 0.0);
    EXPECT_GT(point.y, 0.0);
}