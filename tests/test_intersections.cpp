#include <gtest/gtest.h>
#include "fastgeom3d/algorithms.h"
#include <numbers>

using namespace fastgeom3d;

// 球どうしの交差種別が重なり・接触・非交差に分かれることを確認する。
TEST(IntersectionsTests, SphereIntersectionType) {
    Sphere a(Vec3(0.0, 0.0, 0.0), 1.0);
    Sphere b(Vec3(1.5, 0.0, 0.0), 1.0);
    EXPECT_EQ(Intersections::intersectionType(a, b), Intersections::IntersectionType::OVERLAP);
    Sphere c(Vec3(2.0, 0.0, 0.0), 1.0);
    EXPECT_EQ(Intersections::intersectionType(a, c), Intersections::IntersectionType::TOUCH);
    Sphere d(Vec3(3.0, 0.0, 0.0), 1.0);
    EXPECT_EQ(Intersections::intersectionType(a, d), Intersections::IntersectionType::NONE);
}

// AABBどうしの交差判定が重なりと非交差を正しく返すことを確認する。
TEST(IntersectionsTests, AABBIntersection) {
    AABB a(0.0, 0.0, 0.0, 2.0, 2.0, 2.0);
    AABB b(1.0, 1.0, 1.0, 3.0, 3.0, 3.0);
    EXPECT_TRUE(Intersections::intersect(a, b));
    AABB c(3.0, 3.0, 3.0, 4.0, 4.0, 4.0);
    EXPECT_FALSE(Intersections::intersect(a, c));
}

// 多角形と円の交差判定が内部交差と非交差を区別できることを確認する。
TEST(IntersectionsTests, PolygonCircleIntersection) {
    Polygon2D polygon({Vec2(0.0, 0.0), Vec2(4.0, 0.0), Vec2(4.0, 4.0), Vec2(0.0, 4.0)});
    Circle2D circle(Vec2(2.0, 2.0), 0.5);
    EXPECT_TRUE(Intersections::intersect(polygon, circle));
    Circle2D circle2(Vec2(10.0, 10.0), 1.0);
    EXPECT_FALSE(Intersections::intersect(polygon, circle2));
}

// 2Dポリラインと多角形の交差判定が貫通と非交差を判定できることを確認する。
TEST(IntersectionsTests, Polyline2DPolygonIntersection) {
    Polyline2D line({Vec2(-1.0, 2.0), Vec2(5.0, 2.0)});
    Polygon2D polygon({Vec2(0.0, 0.0), Vec2(4.0, 0.0), Vec2(4.0, 4.0), Vec2(0.0, 4.0)});
    EXPECT_TRUE(Intersections::intersect(line, polygon));
    Polyline2D line2({Vec2(10.0, 10.0), Vec2(11.0, 11.0)});
    EXPECT_FALSE(Intersections::intersect(line2, polygon));
}

// 円どうしの交差判定が交差と非交差を返すことを確認する。
TEST(IntersectionsTests, CircleIntersection) {
    Circle2D a(Vec2(0.0, 0.0), 1.0);
    Circle2D b(Vec2(1.5, 0.0), 1.0);
    EXPECT_TRUE(Intersections::intersect(a, b));
    Circle2D c(Vec2(3.0, 0.0), 1.0);
    EXPECT_FALSE(Intersections::intersect(a, c));
}

// 円の厳密判定とAABB判定で答えが異なる代表例を確認する。
TEST(IntersectionsTests, CircleIntersectionDiffersFromAABBIntersection) {
    Circle2D a(Vec2(0.0, 0.0), 1.0);
    Circle2D b(Vec2(1.5, 1.5), 1.0);

    EXPECT_FALSE(Intersections::intersect(a, b));
    EXPECT_TRUE(Intersections::intersect(a.getAABB(), b.getAABB()));
}

// 巨大座標ではdouble丸めによりlong double想定と交差結果が変わりうることを確認する。
TEST(IntersectionsTests, CircleIntersectionCanChangeWithFloatingPointPrecision) {
    constexpr long double baseX = 10000000000000000.0L;
    constexpr long double exactOffset = 2.25L;
    constexpr long double radius = 1.0L;
    constexpr long double tangentDistance = 2.0L * radius;

    const long double exactCenterBX = baseX + exactOffset;
    const long double exactSeparation = exactCenterBX - baseX;
    const bool exactLongDoubleIntersection = exactSeparation <= tangentDistance;

    Circle2D a(Vec2(static_cast<double>(baseX), 0.0), static_cast<double>(radius));
    Circle2D b(Vec2(static_cast<double>(exactCenterBX), 0.0), static_cast<double>(radius));
    const double roundedSeparation = b.getCenter().x - a.getCenter().x;

    EXPECT_GT(exactSeparation, tangentDistance);
    EXPECT_FALSE(exactLongDoubleIntersection);
    EXPECT_DOUBLE_EQ(roundedSeparation, 2.0);
    EXPECT_TRUE(Intersections::intersect(a, b));
    EXPECT_EQ(Intersections::intersectionType(a, b), Intersections::IntersectionType::TOUCH);
}

// 円対楕円のサンプル判定が楕円内に入るケースを検出できることを確認する。
TEST(IntersectionsTests, CircleEllipseIntersection) {
    Circle2D circle(Vec2(0.0, 0.0), 1.0);
    Ellipse2D ellipse(Vec2(1.6, 0.0), 1.0, 0.75);

    EXPECT_TRUE(Intersections::intersect(circle, ellipse));
}

// 円対楕円のサンプル判定が十分に離れたケースを非交差と判定することを確認する。
TEST(IntersectionsTests, CircleEllipseNoIntersection) {
    Circle2D circle(Vec2(0.0, 0.0), 1.0);
    Ellipse2D ellipse(Vec2(4.0, 0.0), 1.0, 0.75);

    EXPECT_FALSE(Intersections::intersect(circle, ellipse));
}

// 2つの四角形が一点で接する場合にTOUCHと判定されることを確認する。
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

// 扇形と矩形が東側で接する場合にTOUCHと判定されることを確認する。
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

// 矩形と扇形の引数順を入れ替えても同じ接触判定になることを確認する。
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