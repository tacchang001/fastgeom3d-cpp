#include <gtest/gtest.h>
#include "fastgeom3d/shapes3d.h"

using namespace fastgeom3d;

TEST(SphereTests, Construction) {
    Sphere sphere(Vec3(1.0, 2.0, 3.0), 4.0);
    EXPECT_DOUBLE_EQ(sphere.center.x, 1.0);
    EXPECT_DOUBLE_EQ(sphere.center.y, 2.0);
    EXPECT_DOUBLE_EQ(sphere.center.z, 3.0);
    EXPECT_DOUBLE_EQ(sphere.radius, 4.0);
}

TEST(SphereTests, GetAABB) {
    Sphere sphere(Vec3(0.0, 0.0, 0.0), 2.0);
    AABB box = sphere.getAABB();
    EXPECT_DOUBLE_EQ(box.minX, -2.0);
    EXPECT_DOUBLE_EQ(box.minY, -2.0);
    EXPECT_DOUBLE_EQ(box.minZ, -2.0);
    EXPECT_DOUBLE_EQ(box.maxX, 2.0);
    EXPECT_DOUBLE_EQ(box.maxY, 2.0);
    EXPECT_DOUBLE_EQ(box.maxZ, 2.0);
}