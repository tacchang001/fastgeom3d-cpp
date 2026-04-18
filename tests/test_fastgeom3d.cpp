#include <gtest/gtest.h>
#include "fastgeom3d/fastgeom3d.h"

using namespace fastgeom3d;

TEST(FastGeom3DTests, VolumeOfUnitCube) {
    EXPECT_DOUBLE_EQ(volumeOfUnitCube(), 1.0);
}

TEST(FastGeom3DTests, Distance3D) {
    EXPECT_DOUBLE_EQ(distance3D(0.0, 0.0, 0.0, 1.0, 2.0, 2.0), 3.0);
}

TEST(FastGeom3DTests, Vec3Operations) {
    Vec3 a(1.0, 2.0, 3.0);
    Vec3 b(4.0, 1.0, -2.0);
    Vec3 sum = a.add(b);
    EXPECT_DOUBLE_EQ(sum.x, 5.0);
    EXPECT_DOUBLE_EQ(sum.y, 3.0);
    EXPECT_DOUBLE_EQ(sum.z, 1.0);
    EXPECT_DOUBLE_EQ(a.dot(b), 0.0);
    EXPECT_DOUBLE_EQ(a.lengthSquared(), 14.0);
}

TEST(FastGeom3DTests, AABBFromPoints) {
    std::vector<Vec3> points{Vec3(0.0, 5.0, 1.0), Vec3(-1.0, 2.0, 4.0), Vec3(3.0, 0.0, 2.0)};
    AABB box = AABB::fromPoints(points);
    EXPECT_DOUBLE_EQ(box.minX, -1.0);
    EXPECT_DOUBLE_EQ(box.maxY, 5.0);
    EXPECT_DOUBLE_EQ(box.minZ, 1.0);
}

TEST(FastGeom3DTests, Circle2DAABB) {
    Circle2D circle(Vec2(1.0, 2.0), 2.5);
    AABB box = circle.getAABB();
    EXPECT_DOUBLE_EQ(box.minX, -1.5);
    EXPECT_DOUBLE_EQ(box.maxY, 4.5);
}

TEST(FastGeom3DTests, SphereIntersectionType) {
    Sphere a(Vec3(0.0, 0.0, 0.0), 1.0);
    Sphere b(Vec3(1.5, 0.0, 0.0), 1.0);
    EXPECT_EQ(Intersections::intersectionType(a, b), Intersections::IntersectionType::OVERLAP);
    Sphere c(Vec3(2.0, 0.0, 0.0), 1.0);
    EXPECT_EQ(Intersections::intersectionType(a, c), Intersections::IntersectionType::TOUCH);
}

TEST(FastGeom3DTests, PolygonCircleIntersection) {
    Polygon2D polygon({Vec2(0.0, 0.0), Vec2(4.0, 0.0), Vec2(4.0, 4.0), Vec2(0.0, 4.0)});
    Circle2D circle(Vec2(2.0, 2.0), 0.5);
    EXPECT_TRUE(Intersections::intersect(polygon, circle));
}

TEST(FastGeom3DTests, Polyline2DPolygonIntersection) {
    Polyline2D line({Vec2(-1.0, 2.0), Vec2(5.0, 2.0)});
    Polygon2D polygon({Vec2(0.0, 0.0), Vec2(4.0, 0.0), Vec2(4.0, 4.0), Vec2(0.0, 4.0)});
    EXPECT_TRUE(Intersections::intersect(line, polygon));
}

TEST(FastGeom3DTests, UTMConversion) {
    UTMCoordinate utm = UTMCoordinate::fromLatLon(35.0, 139.0, 100.0);
    Vec3 point = utm.toVec3();
    EXPECT_DOUBLE_EQ(point.z, 100.0);
    EXPECT_GT(point.x, 0.0);
    EXPECT_GT(point.y, 0.0);
}
