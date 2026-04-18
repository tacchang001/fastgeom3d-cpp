#include <gtest/gtest.h>
#include "fastgeom3d/shapes2d.h"

using namespace fastgeom3d;

TEST(Circle2DTests, Construction) {
    Circle2D circle(Vec2(1.0, 2.0), 2.5);
    EXPECT_DOUBLE_EQ(circle.getCenter().x, 1.0);
    EXPECT_DOUBLE_EQ(circle.getCenter().y, 2.0);
    EXPECT_DOUBLE_EQ(circle.getRadius(), 2.5);
}

TEST(Circle2DTests, ConstructionInvalidRadius) {
    EXPECT_THROW(Circle2D(Vec2(0.0, 0.0), 0.0), std::invalid_argument);
    EXPECT_THROW(Circle2D(Vec2(0.0, 0.0), -1.0), std::invalid_argument);
}

TEST(Circle2DTests, GetAABB) {
    Circle2D circle(Vec2(1.0, 2.0), 2.5);
    AABB box = circle.getAABB();
    EXPECT_DOUBLE_EQ(box.minX, -1.5);
    EXPECT_DOUBLE_EQ(box.minY, -0.5);
    EXPECT_DOUBLE_EQ(box.maxX, 3.5);
    EXPECT_DOUBLE_EQ(box.maxY, 4.5);
    EXPECT_DOUBLE_EQ(box.minZ, 0.0);
    EXPECT_DOUBLE_EQ(box.maxZ, 0.0);
}