#include <gtest/gtest.h>
#include "fastgeom3d/shapes2d.h"

using namespace fastgeom3d;

TEST(Polygon2DTests, Construction) {
    std::vector<Vec2> verts = {Vec2(0.0, 0.0), Vec2(4.0, 0.0), Vec2(4.0, 4.0), Vec2(0.0, 4.0)};
    Polygon2D poly(verts);
    EXPECT_EQ(poly.getVertices().size(), 4);
}

TEST(Polygon2DTests, ConstructionInvalid) {
    std::vector<Vec2> verts = {Vec2(0.0, 0.0), Vec2(1.0, 1.0)};
    EXPECT_THROW(Polygon2D(verts), std::invalid_argument);
}

TEST(Polygon2DTests, GetAABB) {
    std::vector<Vec2> verts = {Vec2(0.0, 0.0), Vec2(4.0, 0.0), Vec2(4.0, 4.0), Vec2(0.0, 4.0)};
    Polygon2D poly(verts);
    AABB box = poly.getAABB();
    EXPECT_DOUBLE_EQ(box.minX, 0.0);
    EXPECT_DOUBLE_EQ(box.minY, 0.0);
    EXPECT_DOUBLE_EQ(box.maxX, 4.0);
    EXPECT_DOUBLE_EQ(box.maxY, 4.0);
}

TEST(Polyline2DTests, Construction) {
    std::vector<Vec2> verts = {Vec2(0.0, 0.0), Vec2(1.0, 1.0), Vec2(2.0, 0.0)};
    Polyline2D line(verts);
    EXPECT_EQ(line.getVertices().size(), 3);
}

TEST(Polyline2DTests, GetAABB) {
    std::vector<Vec2> verts = {Vec2(0.0, 0.0), Vec2(1.0, 1.0), Vec2(2.0, 0.0)};
    Polyline2D line(verts);
    AABB box = line.getAABB();
    EXPECT_DOUBLE_EQ(box.minX, 0.0);
    EXPECT_DOUBLE_EQ(box.minY, 0.0);
    EXPECT_DOUBLE_EQ(box.maxX, 2.0);
    EXPECT_DOUBLE_EQ(box.maxY, 1.0);
}

TEST(Polygon2DTests, TriangleFactory) {
    Triangle2D triangle = makeTriangle2D({Vec2(0.0, 0.0), Vec2(1.0, 0.0), Vec2(0.0, 1.0)});
    EXPECT_EQ(triangle.getVertices().size(), 3);
}

TEST(Polygon2DTests, QuadrilateralFactory) {
    Quadrilateral2D quadrilateral = makeQuadrilateral2D({
        Vec2(0.0, 0.0), Vec2(1.0, 0.0), Vec2(1.0, 1.0), Vec2(0.0, 1.0)
    });
    EXPECT_EQ(quadrilateral.getVertices().size(), 4);
}