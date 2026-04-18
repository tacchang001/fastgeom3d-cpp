#include <gtest/gtest.h>
#include "fastgeom3d/geodesy.h"

using namespace fastgeom3d;

// UTM座標の各フィールドがコンストラクタ引数通りに保持されることを確認する。
TEST(UTMCoordinateTests, Construction) {
    UTMCoordinate utm(33, true, 500000.0, 4000000.0, 100.0);
    EXPECT_EQ(utm.zoneNumber, 33);
    EXPECT_TRUE(utm.northernHemisphere);
    EXPECT_DOUBLE_EQ(utm.easting, 500000.0);
    EXPECT_DOUBLE_EQ(utm.northing, 4000000.0);
    EXPECT_DOUBLE_EQ(utm.elevation, 100.0);
}

// 範囲外のゾーン番号を与えると例外が送出されることを確認する。
TEST(UTMCoordinateTests, ConstructionInvalidZone) {
    EXPECT_THROW(UTMCoordinate(0, true, 500000.0, 4000000.0, 100.0), std::invalid_argument);
    EXPECT_THROW(UTMCoordinate(61, true, 500000.0, 4000000.0, 100.0), std::invalid_argument);
}

// 緯度経度からUTM座標を生成した際に代表的な属性が妥当範囲に入ることを確認する。
TEST(UTMCoordinateTests, FromLatLon) {
    UTMCoordinate utm = UTMCoordinate::fromLatLon(35.0, 139.0, 100.0);
    EXPECT_GE(utm.zoneNumber, 1);
    EXPECT_LE(utm.zoneNumber, 60);
    EXPECT_DOUBLE_EQ(utm.elevation, 100.0);
}

// UTM座標をVec3へ変換すると座標成分が引き継がれることを確認する。
TEST(UTMCoordinateTests, ToVec3) {
    UTMCoordinate utm(33, true, 500000.0, 4000000.0, 100.0);
    Vec3 point = utm.toVec3();
    EXPECT_DOUBLE_EQ(point.z, 100.0);
    EXPECT_GT(point.x, 0.0);
    EXPECT_GT(point.y, 0.0);
}