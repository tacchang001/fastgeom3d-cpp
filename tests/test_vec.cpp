#include <gtest/gtest.h>
#include "fastgeom3d/core.h"

using namespace fastgeom3d;

TEST(VecTests, Vec2Construction) {
    Vec2 v(1.0, 2.0);
    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 2.0);
}

TEST(VecTests, Vec2FromVec3) {
    Vec3 v3(1.0, 2.0, 3.0);
    Vec2 v2 = Vec2::fromVec3(v3);
    EXPECT_DOUBLE_EQ(v2.x, 1.0);
    EXPECT_DOUBLE_EQ(v2.y, 2.0);
}

TEST(VecTests, Vec3Construction) {
    Vec3 v(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 2.0);
    EXPECT_DOUBLE_EQ(v.z, 3.0);
}

TEST(VecTests, Vec3Add) {
    Vec3 a(1.0, 2.0, 3.0);
    Vec3 b(4.0, 5.0, 6.0);
    Vec3 sum = a.add(b);
    EXPECT_DOUBLE_EQ(sum.x, 5.0);
    EXPECT_DOUBLE_EQ(sum.y, 7.0);
    EXPECT_DOUBLE_EQ(sum.z, 9.0);
}

TEST(VecTests, Vec3Sub) {
    Vec3 a(5.0, 7.0, 9.0);
    Vec3 b(1.0, 2.0, 3.0);
    Vec3 diff = a.sub(b);
    EXPECT_DOUBLE_EQ(diff.x, 4.0);
    EXPECT_DOUBLE_EQ(diff.y, 5.0);
    EXPECT_DOUBLE_EQ(diff.z, 6.0);
}

TEST(VecTests, Vec3Dot) {
    Vec3 a(1.0, 2.0, 3.0);
    Vec3 b(4.0, 5.0, 6.0);
    double dot = a.dot(b);
    EXPECT_DOUBLE_EQ(dot, 32.0);
}

TEST(VecTests, Vec3LengthSquared) {
    Vec3 v(3.0, 4.0, 0.0);
    double lenSq = v.lengthSquared();
    EXPECT_DOUBLE_EQ(lenSq, 25.0);
}