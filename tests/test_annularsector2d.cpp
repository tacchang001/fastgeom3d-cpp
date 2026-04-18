#include <gtest/gtest.h>
#include "fastgeom3d/fastgeom3d.h"

using namespace fastgeom3d;

TEST(AnnularSector2DTests, Construction) {
    AnnularSector2D sector(Vec2(0.0, 0.0), 5.0, 2.0, 0.0, M_PI / 2);
    EXPECT_DOUBLE_EQ(sector.getCenter().x, 0.0);
    EXPECT_DOUBLE_EQ(sector.getCenter().y, 0.0);
    EXPECT_DOUBLE_EQ(sector.getOuterRadius(), 5.0);
    EXPECT_DOUBLE_EQ(sector.getInnerRadius(), 2.0);
    EXPECT_DOUBLE_EQ(sector.getStartAngle(), 0.0);
    EXPECT_DOUBLE_EQ(sector.getEndAngle(), M_PI / 2);
}

TEST(AnnularSector2DTests, ConstructionInvalid) {
    EXPECT_THROW(AnnularSector2D(Vec2(0.0, 0.0), 0.0, 2.0, 0.0, M_PI), std::invalid_argument);
    EXPECT_THROW(AnnularSector2D(Vec2(0.0, 0.0), 5.0, -1.0, 0.0, M_PI), std::invalid_argument);
    EXPECT_THROW(AnnularSector2D(Vec2(0.0, 0.0), 2.0, 3.0, 0.0, M_PI), std::invalid_argument);
    EXPECT_THROW(AnnularSector2D(Vec2(0.0, 0.0), 5.0, 2.0, M_PI, 0.0), std::invalid_argument);
}

TEST(AnnularSector2DTests, GetAABB) {
    AnnularSector2D sector(Vec2(0.0, 0.0), 5.0, 0.0, 0.0, M_PI / 2); // 扇形
    AABB box = sector.getAABB();
    EXPECT_DOUBLE_EQ(box.minX, 0.0);
    EXPECT_DOUBLE_EQ(box.minY, 0.0);
    EXPECT_DOUBLE_EQ(box.maxX, 5.0);
    EXPECT_DOUBLE_EQ(box.maxY, 5.0);
    EXPECT_DOUBLE_EQ(box.minZ, 0.0);
    EXPECT_DOUBLE_EQ(box.maxZ, 0.0);
}

TEST(AnnularSector2DTests, GetAABBAnnular) {
    AnnularSector2D sector(Vec2(0.0, 0.0), 5.0, 2.0, 0.0, M_PI / 2);
    AABB box = sector.getAABB();
    EXPECT_LE(box.minX, 0.0);
    EXPECT_LE(box.minY, 0.0);
    EXPECT_GE(box.maxX, 5.0);
    EXPECT_GE(box.maxY, 5.0);
}