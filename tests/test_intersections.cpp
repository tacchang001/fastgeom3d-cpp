#include <gtest/gtest.h>
#include "fastgeom3d/algorithms.h"
#include <numbers>

using namespace fastgeom3d;

TEST(IntersectionsTests, SphereIntersectionType) {
    Sphere a(Vec3(0.0, 0.0, 0.0), 1.0);
    Sphere b(Vec3(1.5, 0.0, 0.0), 1.0);
    EXPECT_EQ(Intersections::intersectionType(a, b), Intersections::IntersectionType::OVERLAP);
    Sphere c(Vec3(2.0, 0.0, 0.0), 1.0);
    EXPECT_EQ(Intersections::intersectionType(a, c), Intersections::IntersectionType::TOUCH);
    Sphere d(Vec3(3.0, 0.0, 0.0), 1.0);
    EXPECT_EQ(Intersections::intersectionType(a, d), Intersections::IntersectionType::NONE);
}

TEST(IntersectionsTests, AABBIntersection) {
    AABB a(0.0, 0.0, 0.0, 2.0, 2.0, 2.0);
    AABB b(1.0, 1.0, 1.0, 3.0, 3.0, 3.0);
    EXPECT_TRUE(Intersections::intersect(a, b));
    AABB c(3.0, 3.0, 3.0, 4.0, 4.0, 4.0);
    EXPECT_FALSE(Intersections::intersect(a, c));
}

TEST(IntersectionsTests, PolygonCircleIntersection) {
    Polygon2D polygon({Vec2(0.0, 0.0), Vec2(4.0, 0.0), Vec2(4.0, 4.0), Vec2(0.0, 4.0)});
    Circle2D circle(Vec2(2.0, 2.0), 0.5);
    EXPECT_TRUE(Intersections::intersect(polygon, circle));
    Circle2D circle2(Vec2(10.0, 10.0), 1.0);
    EXPECT_FALSE(Intersections::intersect(polygon, circle2));
}

TEST(IntersectionsTests, Polyline2DPolygonIntersection) {
    Polyline2D line({Vec2(-1.0, 2.0), Vec2(5.0, 2.0)});
    Polygon2D polygon({Vec2(0.0, 0.0), Vec2(4.0, 0.0), Vec2(4.0, 4.0), Vec2(0.0, 4.0)});
    EXPECT_TRUE(Intersections::intersect(line, polygon));
    Polyline2D line2({Vec2(10.0, 10.0), Vec2(11.0, 11.0)});
    EXPECT_FALSE(Intersections::intersect(line2, polygon));
}

TEST(IntersectionsTests, CircleIntersection) {
    Circle2D a(Vec2(0.0, 0.0), 1.0);
    Circle2D b(Vec2(1.5, 0.0), 1.0);
    EXPECT_TRUE(Intersections::intersect(a, b));
    Circle2D c(Vec2(3.0, 0.0), 1.0);
    EXPECT_FALSE(Intersections::intersect(a, c));
}

TEST(IntersectionsTests, QuadrilateralCornerTouchIntersection) {
    Quadrilateral2D a({
        Vec2(0.0, 0.0),
        Vec2(1.0, 0.0),
        Vec2(1.0, 1.0),
        Vec2(0.0, 1.0)
    });
    Quadrilateral2D b({
        Vec2(1.0, 1.0),
        Vec2(2.0, 1.0),
        Vec2(2.0, 2.0),
        Vec2(1.0, 2.0)
    });

    EXPECT_TRUE(Intersections::intersect(a, b));
    EXPECT_EQ(Intersections::intersectionType(a, b), Intersections::IntersectionType::TOUCH);
}

TEST(IntersectionsTests, AnnularSectorQuadrilateralTouchIntersection) {
    AnnularSector2D sector(
        Vec2(1.0, 1.0),
        1.0,
        0.0,
        0.0,
        std::numbers::pi
    );
    Quadrilateral2D rectangle({
        Vec2(2.0, 0.0),
        Vec2(3.0, 0.0),
        Vec2(3.0, 2.0),
        Vec2(2.0, 2.0)
    });

    EXPECT_TRUE(Intersections::intersect(sector, rectangle));
    EXPECT_EQ(Intersections::intersectionType(sector, rectangle), Intersections::IntersectionType::TOUCH);
}

TEST(IntersectionsTests, QuadrilateralAnnularSectorTouchIntersection) {
    Quadrilateral2D rectangle({
        Vec2(0.0, 0.0),
        Vec2(1.0, 0.0),
        Vec2(1.0, 2.0),
        Vec2(0.0, 2.0)
    });
    AnnularSector2D sector(
        Vec2(1.0, 1.0),
        1.0,
        0.0,
        0.0,
        std::numbers::pi
    );

    EXPECT_TRUE(Intersections::intersect(rectangle, sector));
    EXPECT_EQ(Intersections::intersectionType(rectangle, sector), Intersections::IntersectionType::TOUCH);
}