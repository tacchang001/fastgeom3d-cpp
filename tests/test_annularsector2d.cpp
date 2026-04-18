#include <gtest/gtest.h>
#include "fastgeom3d/shapes2d.h"
#include <numbers>

using namespace fastgeom3d;

TEST(AnnularSector2DTests, Construction) {
    AnnularSector2D sector(Vec2(0.0, 0.0), 5.0, 2.0, 0.0, std::numbers::pi / 2.0);
    EXPECT_DOUBLE_EQ(sector.getCenter().x, 0.0);
    EXPECT_DOUBLE_EQ(sector.getCenter().y, 0.0);
    EXPECT_DOUBLE_EQ(sector.getOuterRadius(), 5.0);
    EXPECT_DOUBLE_EQ(sector.getInnerRadius(), 2.0);
    EXPECT_DOUBLE_EQ(sector.getStartAngle(), 0.0);
    EXPECT_DOUBLE_EQ(sector.getEndAngle(), std::numbers::pi / 2.0);
}

TEST(AnnularSector2DTests, ConstructionInvalid) {
    EXPECT_THROW(AnnularSector2D(Vec2(0.0, 0.0), 0.0, 2.0, 0.0, std::numbers::pi), std::invalid_argument);
    EXPECT_THROW(AnnularSector2D(Vec2(0.0, 0.0), 5.0, -1.0, 0.0, std::numbers::pi), std::invalid_argument);
    EXPECT_THROW(AnnularSector2D(Vec2(0.0, 0.0), 2.0, 3.0, 0.0, std::numbers::pi), std::invalid_argument);
    EXPECT_THROW(AnnularSector2D(Vec2(0.0, 0.0), 5.0, 2.0, std::numbers::pi, 0.0), std::invalid_argument);
}

TEST(AnnularSector2DTests, GetAABB) {
    AnnularSector2D sector(Vec2(0.0, 0.0), 5.0, 0.0, 0.0, std::numbers::pi / 2.0); // 北から東への扇形
    AABB box = sector.getAABB();
    EXPECT_DOUBLE_EQ(box.minX, 0.0);
    EXPECT_DOUBLE_EQ(box.minY, 0.0);
    EXPECT_DOUBLE_EQ(box.maxX, 5.0);
    EXPECT_DOUBLE_EQ(box.maxY, 5.0);
    EXPECT_DOUBLE_EQ(box.minZ, 0.0);
    EXPECT_DOUBLE_EQ(box.maxZ, 0.0);
}

TEST(AnnularSector2DTests, GetAABBAnnular) {
    AnnularSector2D sector(Vec2(0.0, 0.0), 5.0, 2.0, 0.0, std::numbers::pi / 2.0);
    AABB box = sector.getAABB();
    EXPECT_LE(box.minX, 0.0);
    EXPECT_LE(box.minY, 0.0);
    EXPECT_GE(box.maxX, 5.0);
    EXPECT_GE(box.maxY, 5.0);
}

TEST(AnnularSector2DTests, BearingConventionUsesNorthAsZeroAndClockwiseRotation) {
    AnnularSector2D sector(Vec2(10.0, 20.0), 5.0, 0.0, 0.0, std::numbers::pi);
    AABB box = sector.getAABB();

    EXPECT_DOUBLE_EQ(box.minX, 10.0);
    EXPECT_DOUBLE_EQ(box.maxX, 15.0);
    EXPECT_DOUBLE_EQ(box.minY, 15.0);
    EXPECT_DOUBLE_EQ(box.maxY, 25.0);
}

TEST(AnnularSector2DTests, BearingZeroPointsNorth) {
    AnnularSector2D sector(Vec2(10.0, 20.0), 5.0, 0.0, 0.0, 0.01);
    AABB box = sector.getAABB();

    EXPECT_DOUBLE_EQ(box.minX, 10.0);
    EXPECT_GT(box.maxX, 10.0);
    EXPECT_DOUBLE_EQ(box.minY, 20.0);
    EXPECT_DOUBLE_EQ(box.maxY, 25.0);
}

TEST(AnnularSector2DTests, BearingQuarterTurnPointsEast) {
    AnnularSector2D sector(Vec2(10.0, 20.0), 5.0, 0.0, std::numbers::pi / 2.0, std::numbers::pi / 2.0 + 0.01);
    AABB box = sector.getAABB();

    EXPECT_DOUBLE_EQ(box.minX, 10.0);
    EXPECT_DOUBLE_EQ(box.maxX, 15.0);
    EXPECT_LT(box.minY, 20.0);
    EXPECT_DOUBLE_EQ(box.maxY, 20.0);
}

TEST(AnnularSector2DTests, BearingHalfTurnPointsSouth) {
    AnnularSector2D sector(Vec2(10.0, 20.0), 5.0, 0.0, std::numbers::pi, std::numbers::pi + 0.01);
    AABB box = sector.getAABB();

    EXPECT_LT(box.minX, 10.0);
    EXPECT_DOUBLE_EQ(box.maxX, 10.0);
    EXPECT_DOUBLE_EQ(box.minY, 15.0);
    EXPECT_DOUBLE_EQ(box.maxY, 20.0);
}

TEST(AnnularSector2DTests, BearingThreeQuarterTurnPointsWest) {
    AnnularSector2D sector(Vec2(10.0, 20.0), 5.0, 0.0, 3.0 * std::numbers::pi / 2.0, 3.0 * std::numbers::pi / 2.0 + 0.01);
    AABB box = sector.getAABB();

    EXPECT_DOUBLE_EQ(box.minX, 5.0);
    EXPECT_DOUBLE_EQ(box.maxX, 10.0);
    EXPECT_DOUBLE_EQ(box.minY, 20.0);
    EXPECT_GT(box.maxY, 20.0);
}