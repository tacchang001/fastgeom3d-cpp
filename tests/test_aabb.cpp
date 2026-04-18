#include <gtest/gtest.h>
#include "fastgeom3d/core.h"

using namespace fastgeom3d;

// AABBの各境界値がコンストラクタ引数通りに格納されることを確認する。
TEST(AABBTests, Construction) {
    AABB box(0.0, 1.0, 2.0, 3.0, 4.0, 5.0);
    EXPECT_DOUBLE_EQ(box.minX, 0.0);
    EXPECT_DOUBLE_EQ(box.minY, 1.0);
    EXPECT_DOUBLE_EQ(box.minZ, 2.0);
    EXPECT_DOUBLE_EQ(box.maxX, 3.0);
    EXPECT_DOUBLE_EQ(box.maxY, 4.0);
    EXPECT_DOUBLE_EQ(box.maxZ, 5.0);
}

// 中心と半サイズからAABBを生成できることを確認する。
TEST(AABBTests, FromCenterHalfExtents) {
    Vec3 center(1.0, 2.0, 3.0);
    Vec3 halfExtents(0.5, 1.0, 1.5);
    AABB box = AABB::fromCenterHalfExtents(center, halfExtents);
    EXPECT_DOUBLE_EQ(box.minX, 0.5);
    EXPECT_DOUBLE_EQ(box.minY, 1.0);
    EXPECT_DOUBLE_EQ(box.minZ, 1.5);
    EXPECT_DOUBLE_EQ(box.maxX, 1.5);
    EXPECT_DOUBLE_EQ(box.maxY, 3.0);
    EXPECT_DOUBLE_EQ(box.maxZ, 4.5);
}

// 3D点群からAABBを生成すると最小・最大座標が反映されることを確認する。
TEST(AABBTests, FromPoints) {
    std::vector<Vec3> points = {Vec3(0.0, 5.0, 1.0), Vec3(-1.0, 2.0, 4.0), Vec3(3.0, 0.0, 2.0)};
    AABB box = AABB::fromPoints(points);
    EXPECT_DOUBLE_EQ(box.minX, -1.0);
    EXPECT_DOUBLE_EQ(box.maxY, 5.0);
    EXPECT_DOUBLE_EQ(box.minZ, 1.0);
}

// 2D点群から生成したAABBでZがゼロ固定になることを確認する。
TEST(AABBTests, FromPoints2D) {
    std::vector<Vec2> points = {Vec2(0.0, 5.0), Vec2(-1.0, 2.0), Vec2(3.0, 0.0)};
    AABB box = AABB::fromPoints2D(points);
    EXPECT_DOUBLE_EQ(box.minX, -1.0);
    EXPECT_DOUBLE_EQ(box.maxY, 5.0);
    EXPECT_DOUBLE_EQ(box.minZ, 0.0);
    EXPECT_DOUBLE_EQ(box.maxZ, 0.0);
}

// AABB自身のgetAABBが同じ値を返すことを確認する。
TEST(AABBTests, GetAABB) {
    AABB box(0.0, 1.0, 2.0, 3.0, 4.0, 5.0);
    AABB aabb = box.getAABB();
    EXPECT_EQ(aabb.minX, box.minX);
    EXPECT_EQ(aabb.maxZ, box.maxZ);
}

// AABBの等値比較演算子が同一ボックスを正しく判定することを確認する。
TEST(AABBTests, Equality) {
    AABB a(0.0, 1.0, 2.0, 3.0, 4.0, 5.0);
    AABB b(0.0, 1.0, 2.0, 3.0, 4.0, 5.0);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}