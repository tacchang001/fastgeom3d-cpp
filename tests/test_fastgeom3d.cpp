#include <gtest/gtest.h>
#include "fastgeom3d/fastgeom3d.h"

using namespace fastgeom3d;

// 単位立方体の体積をテスト
TEST(FastGeom3DTests, VolumeOfUnitCube) {
    EXPECT_DOUBLE_EQ(volumeOfUnitCube(), 1.0); // 単位立方体の体積は1.0
}

// 3D距離計算をテスト
TEST(FastGeom3DTests, Distance3D) {
    EXPECT_DOUBLE_EQ(distance3D(0.0, 0.0, 0.0, 1.0, 2.0, 2.0), 3.0); // (0,0,0)から(1,2,2)までの距離
    EXPECT_DOUBLE_EQ(distance3D(1.0, 1.0, 1.0, 1.0, 1.0, 1.0), 0.0); // 同じ点間の距離
    EXPECT_DOUBLE_EQ(distance3D(0.0, 0.0, 0.0, 3.0, 4.0, 0.0), 5.0); // (0,0,0)から(3,4,0)までの距離
}
