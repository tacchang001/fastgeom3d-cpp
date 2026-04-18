#include "fastgeom3d/Intersections.h"
#include "fastgeom3d/AABB.h"
#include "fastgeom3d/Circle2D.h"
#include "fastgeom3d/Ellipse2D.h"
#include "fastgeom3d/Polygon2D.h"
#include "fastgeom3d/Polyline.h"
#include "fastgeom3d/Polyline2D.h"
#include "fastgeom3d/Sphere.h"
#include "fastgeom3d/Vec2.h"
#include <array>
#include <algorithm>
#include <cmath>
#include <numbers>

namespace fastgeom3d {

namespace {

constexpr std::size_t kCircleEllipseSampleCount = 32;

/**
 * @brief 値を指定区間へ切り詰める。
 */
double clampValue(double value, double min, double max) {
    return value < min ? min : (value > max ? max : value);
}

/**
 * @brief 2つの閉区間が交差または接触しているかを判定する。
 */
bool intervalIntersects(double minA, double maxA, double minB, double maxB) {
    return minA <= maxB && maxA >= minB;
}

/**
 * @brief 2つの区間が内部で重なっているかを判定する。
 */
bool intervalOverlaps(double minA, double maxA, double minB, double maxB) {
    return minA < maxB && maxA > minB;
}

/**
 * @brief 2点間の2次元距離の二乗を返す。
 */
double squaredDistance(const Vec2& a, const Vec2& b) {
    const double dx = a.x - b.x;
    const double dy = a.y - b.y;
    return dx * dx + dy * dy;
}

/**
 * @brief 3点の向きから反時計回り、時計回り、一直線上を判定する。
 */
int ccw(const Vec2& a, const Vec2& b, const Vec2& c) {
    const double value = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return value > 0 ? 1 : (value < 0 ? -1 : 0);
}

/**
 * @brief 点が線分上にあるかを判定する。
 */
bool pointOnSegment(const Vec2& point, const Vec2& a, const Vec2& b) {
    const double cross = (point.y - a.y) * (b.x - a.x) - (point.x - a.x) * (b.y - a.y);
    if (std::abs(cross) > 1e-9) {
        return false;
    }
    const double dot = (point.x - a.x) * (b.x - a.x) + (point.y - a.y) * (b.y - a.y);
    if (dot < 0.0) {
        return false;
    }
    const double squaredLength = (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
    return dot <= squaredLength;
}

/**
 * @brief 2本の線分が交差または接触しているかを判定する。
 */
bool segmentsIntersect(const Vec2& a1, const Vec2& a2, const Vec2& b1, const Vec2& b2) {
    // 端点が相手線分上にある接触ケースを先に拾う。
    if (pointOnSegment(a1, b1, b2) || pointOnSegment(a2, b1, b2) ||
        pointOnSegment(b1, a1, a2) || pointOnSegment(b2, a1, a2)) {
        return true;
    }

    // その後で向き判定により真の交差を判定する。
    return ccw(a1, a2, b1) != ccw(a1, a2, b2) && ccw(b1, b2, a1) != ccw(b1, b2, a2);
}

/**
 * @brief 点が多角形の内部または境界上にあるかを判定する。
 */
bool pointInPolygon(const Vec2& point, const Polygon2D& polygon) {
    const auto& vertices = polygon.getVertices();
    bool inside = false;

    // レイキャスティング法で交差回数の偶奇を数える。
    for (std::size_t i = 0, j = vertices.size() - 1; i < vertices.size(); j = i++) {
        const Vec2& pi = vertices[i];
        const Vec2& pj = vertices[j];
        if (pointOnSegment(point, pj, pi)) {
            return true;
        }
        const bool intersects = (pi.y > point.y) != (pj.y > point.y)
            && point.x < (pj.x - pi.x) * (point.y - pi.y) / (pj.y - pi.y) + pi.x;
        if (intersects) {
            inside = !inside;
        }
    }
    return inside;
}

/**
 * @brief 点が楕円の内部または境界上にあるかを判定する。
 */
bool pointInEllipse(const Vec2& point, const Ellipse2D& ellipse) {
    const double dx = (point.x - ellipse.getCenter().x) / ellipse.getRadiusX();
    const double dy = (point.y - ellipse.getCenter().y) / ellipse.getRadiusY();
    return dx * dx + dy * dy <= 1.0;
}

/**
 * @brief 円周サンプル点の単位ベクトル表を返す。
 */
const std::array<std::array<double, 2>, kCircleEllipseSampleCount>& unitCircleSamples() {
    static const auto samples = [] {
        std::array<std::array<double, 2>, kCircleEllipseSampleCount> table{};
        for (std::size_t index = 0; index < kCircleEllipseSampleCount; ++index) {
            const double angle = 2.0 * std::numbers::pi_v<double> * static_cast<double>(index)
                / static_cast<double>(kCircleEllipseSampleCount);
            table[index] = {std::cos(angle), std::sin(angle)};
        }
        return table;
    }();
    return samples;
}

/**
 * @brief 円周サンプルを用いて円と楕円の交差を近似判定する。
 */
bool circleSamplesIntersectEllipse(const Circle2D& circle, const Ellipse2D& ellipse) {
    const double centerX = circle.getCenter().x;
    const double centerY = circle.getCenter().y;
    const double radius = circle.getRadius();
    const double ellipseCenterX = ellipse.getCenter().x;
    const double ellipseCenterY = ellipse.getCenter().y;
    const double inverseRadiusX = 1.0 / ellipse.getRadiusX();
    const double inverseRadiusY = 1.0 / ellipse.getRadiusY();

    // 単位円サンプルを使うことで、将来はこのループをSIMDへ置き換えやすくする。
    for (const auto& sample : unitCircleSamples()) {
        const double sampleX = centerX + radius * sample[0];
        const double sampleY = centerY + radius * sample[1];
        const double dx = (sampleX - ellipseCenterX) * inverseRadiusX;
        const double dy = (sampleY - ellipseCenterY) * inverseRadiusY;
        if (dx * dx + dy * dy <= 1.0) {
            return true;
        }
    }
    return false;
}

/**
 * @brief 線分と円が交差または接触しているかを判定する。
 */
bool segmentIntersectsCircle(const Vec2& a, const Vec2& b, const Vec2& center, double radius) {
    const double dx = b.x - a.x;
    const double dy = b.y - a.y;
    const double fx = a.x - center.x;
    const double fy = a.y - center.y;
    const double r2 = radius * radius;

    const double aCoef = dx * dx + dy * dy;
    if (aCoef == 0.0) {
        return squaredDistance(a, center) <= r2;
    }

    // 射影係数を線分範囲にクランプして最近接点を求める。
    double t = -(fx * dx + fy * dy) / aCoef;
    t = std::max(0.0, std::min(1.0, t));
    const Vec2 closest(a.x + t * dx, a.y + t * dy);
    return squaredDistance(closest, center) <= r2;
}

/**
 * @brief 線分と楕円が交差または接触しているかを判定する。
 */
bool segmentIntersectsEllipse(const Vec2& a, const Vec2& b, const Ellipse2D& ellipse) {
    if (pointInEllipse(a, ellipse) || pointInEllipse(b, ellipse)) {
        return true;
    }
    const double dx = b.x - a.x;
    const double dy = b.y - a.y;
    const double cx = a.x - ellipse.getCenter().x;
    const double cy = a.y - ellipse.getCenter().y;
    const double rx = ellipse.getRadiusX();
    const double ry = ellipse.getRadiusY();
    const double rx2 = rx * rx;
    const double ry2 = ry * ry;
    const double A = dx * dx / rx2 + dy * dy / ry2;
    const double B = 2.0 * (cx * dx / rx2 + cy * dy / ry2);
    const double C = cx * cx / rx2 + cy * cy / ry2 - 1.0;
    if (A == 0.0) {
        return pointInEllipse(a, ellipse);
    }

    // 線分の媒介変数について二次方程式を解き、区間 [0, 1] に解があれば交差する。
    const double discriminant = B * B - 4.0 * A * C;
    if (discriminant < 0.0) {
        return false;
    }
    const double sqrtD = std::sqrt(discriminant);
    const double t1 = (-B - sqrtD) / (2.0 * A);
    const double t2 = (-B + sqrtD) / (2.0 * A);
    return (t1 >= 0.0 && t1 <= 1.0) || (t2 >= 0.0 && t2 <= 1.0);
}

} // namespace

/**
 * @brief 2つのAABBが交差または接触しているかを判定する。
 */
bool Intersections::intersect(const AABB& a, const AABB& b) {
    return intersectionType(a, b) != IntersectionType::NONE;
}

/**
 * @brief 2つの球が交差または接触しているかを判定する。
 */
bool Intersections::intersect(const Sphere& a, const Sphere& b) {
    return intersectionType(a, b) != IntersectionType::NONE;
}

/**
 * @brief AABBと球が交差または接触しているかを判定する。
 */
bool Intersections::intersect(const AABB& box, const Sphere& s) {
    return intersectionType(box, s) != IntersectionType::NONE;
}

/**
 * @brief 2本の2次元ポリラインが交差または接触しているかを判定する。
 */
bool Intersections::intersect(const Polyline2D& line, const Polyline2D& other) {
    const auto& points1 = line.getPoints();
    const auto& points2 = other.getPoints();

    // 各折れ線を線分列として総当たりし、最初の交差点で打ち切る。
    for (std::size_t i = 1; i < points1.size(); ++i) {
        const Vec2& a1 = points1[i - 1];
        const Vec2& a2 = points1[i];
        for (std::size_t j = 1; j < points2.size(); ++j) {
            const Vec2& b1 = points2[j - 1];
            const Vec2& b2 = points2[j];
            if (segmentsIntersect(a1, a2, b1, b2)) {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief 2次元ポリラインと円が交差または接触しているかを判定する。
 */
bool Intersections::intersect(const Polyline2D& line, const Circle2D& circle) {
    const auto& center = circle.getCenter();
    const double radius = circle.getRadius();
    const auto& points = line.getPoints();

    // 各線分について最近接点を使う線分対円判定を適用する。
    for (std::size_t i = 1; i < points.size(); ++i) {
        if (segmentIntersectsCircle(points[i - 1], points[i], center, radius)) {
            return true;
        }
    }
    return false;
}

/**
 * @brief 頂点列で表現された多角形と2次元ポリラインの交差を判定する。
 */
bool Intersections::intersectPolylineWithPolygonVertices(const Polyline2D& line, const std::vector<Vec2>& vertices) {
    const auto& points = line.getPoints();

    // 線分同士の交差判定で境界との接触を調べる。
    for (std::size_t i = 1; i < points.size(); ++i) {
        const Vec2& a = points[i - 1];
        const Vec2& b = points[i];
        for (std::size_t j = 1; j < vertices.size(); ++j) {
            if (segmentsIntersect(a, b, vertices[j - 1], vertices[j])) {
                return true;
            }
        }
        if (segmentsIntersect(a, b, vertices[vertices.size() - 1], vertices[0])) {
            return true;
        }
    }

    // 境界交差がなくても、折れ線の点が内部にあれば交差とみなす。
    for (const auto& point : points) {
        if (pointInPolygon(point, Polygon2D(vertices))) {
            return true;
        }
    }
    return false;
}

/**
 * @brief 2次元ポリラインと多角形が交差または接触しているかを判定する。
 */
bool Intersections::intersect(const Polyline2D& line, const Polygon2D& polygon) {
    return intersectPolylineWithPolygonVertices(line, polygon.getVertices());
}

/**
 * @brief 2つの円が交差または接触しているかを判定する。
 */
bool Intersections::intersect(const Circle2D& a, const Circle2D& b) {
    const double radiusSum = a.getRadius() + b.getRadius();
    return squaredDistance(a.getCenter(), b.getCenter()) <= radiusSum * radiusSum;
}

/**
 * @brief 頂点列で表現された多角形と円の交差を判定する。
 */
bool Intersections::intersectPolygonWithCircleVertices(const std::vector<Vec2>& vertices, const Circle2D& circle) {
    // 円の中心が多角形内部にある場合は境界交差がなくても交差とみなす。
    if (pointInPolygon(circle.getCenter(), Polygon2D(vertices))) {
        return true;
    }

    // その後で各辺と円の最近接判定を行う。
    for (std::size_t i = 1; i < vertices.size(); ++i) {
        if (segmentIntersectsCircle(vertices[i - 1], vertices[i], circle.getCenter(), circle.getRadius())) {
            return true;
        }
    }
    return segmentIntersectsCircle(vertices[vertices.size() - 1], vertices[0], circle.getCenter(), circle.getRadius());
}

/**
 * @brief 多角形と円が交差または接触しているかを判定する。
 */
bool Intersections::intersect(const Polygon2D& polygon, const Circle2D& circle) {
    return intersectPolygonWithCircleVertices(polygon.getVertices(), circle);
}

/**
 * @brief 2つの頂点列多角形が交差または包含関係にあるかを判定する。
 */
bool Intersections::intersectPolygonVertices(const std::vector<Vec2>& verticesA, const std::vector<Vec2>& verticesB) {
    for (std::size_t i = 1; i < verticesA.size(); ++i) {
        const Vec2& a1 = verticesA[i - 1];
        const Vec2& a2 = verticesA[i];
        for (std::size_t j = 1; j < verticesB.size(); ++j) {
            if (segmentsIntersect(a1, a2, verticesB[j - 1], verticesB[j])) {
                return true;
            }
        }
        if (segmentsIntersect(a1, a2, verticesB[verticesB.size() - 1], verticesB[0])) {
            return true;
        }
    }

    // 辺同士が交差しない場合は、どちらか一方が他方を包含しているかを確認する。
    if (pointInPolygon(verticesA[0], Polygon2D(verticesB))) {
        return true;
    }
    return pointInPolygon(verticesB[0], Polygon2D(verticesA));
}

/**
 * @brief 2つの多角形が交差または接触しているかを判定する。
 */
bool Intersections::intersect(const Polygon2D& a, const Polygon2D& b) {
    return intersectPolygonVertices(a.getVertices(), b.getVertices());
}

/**
 * @brief 2次元ポリラインと楕円が交差または接触しているかを判定する。
 */
bool Intersections::intersect(const Polyline2D& line, const Ellipse2D& ellipse) {
    const auto& points = line.getPoints();

    // 各線分を楕円方程式へ代入し、線分区間内に解があるかを調べる。
    for (std::size_t i = 1; i < points.size(); ++i) {
        if (segmentIntersectsEllipse(points[i - 1], points[i], ellipse)) {
            return true;
        }
    }

    // 線分交差がなくても端点が楕円内部にあれば交差とみなす。
    for (const auto& point : points) {
        if (pointInEllipse(point, ellipse)) {
            return true;
        }
    }
    return false;
}

/**
 * @brief 円と楕円が交差または接触しているかを判定する。
 */
bool Intersections::intersect(const Circle2D& circle, const Ellipse2D& ellipse) {
    if (pointInEllipse(circle.getCenter(), ellipse)) {
        return true;
    }

    // 円周上の固定サンプルを楕円へ代入して近似的に接触を検出する。
    return circleSamplesIntersectEllipse(circle, ellipse);
}

/**
 * @brief 頂点列で表現された多角形と楕円の交差を判定する。
 */
bool Intersections::intersectPolygonWithEllipseVertices(const std::vector<Vec2>& vertices, const Ellipse2D& ellipse) {
    for (std::size_t i = 1; i < vertices.size(); ++i) {
        if (segmentIntersectsEllipse(vertices[i - 1], vertices[i], ellipse)) {
            return true;
        }
    }
    if (segmentIntersectsEllipse(vertices[vertices.size() - 1], vertices[0], ellipse)) {
        return true;
    }
    return pointInEllipse(vertices[0], ellipse);
}

/**
 * @brief 多角形と楕円が交差または接触しているかを判定する。
 */
bool Intersections::intersect(const Polygon2D& polygon, const Ellipse2D& ellipse) {
    return intersectPolygonWithEllipseVertices(polygon.getVertices(), ellipse);
}

/**
 * @brief 2つのAABBの関係を NONE、TOUCH、OVERLAP に分類する。
 */
Intersections::IntersectionType Intersections::intersectionType(const AABB& a, const AABB& b) {
    const bool intersects = intervalIntersects(a.minX, a.maxX, b.minX, b.maxX) &&
                            intervalIntersects(a.minY, a.maxY, b.minY, b.maxY) &&
                            intervalIntersects(a.minZ, a.maxZ, b.minZ, b.maxZ);
    if (!intersects) {
        return IntersectionType::NONE;
    }

    // 全軸で開区間として重なれば OVERLAP、どこかの軸で境界一致のみなら TOUCH とする。
    const bool overlaps = intervalOverlaps(a.minX, a.maxX, b.minX, b.maxX) &&
                          intervalOverlaps(a.minY, a.maxY, b.minY, b.maxY) &&
                          intervalOverlaps(a.minZ, a.maxZ, b.minZ, b.maxZ);
    return overlaps ? IntersectionType::OVERLAP : IntersectionType::TOUCH;
}

/**
 * @brief 2つの球の関係を NONE、TOUCH、OVERLAP に分類する。
 */
Intersections::IntersectionType Intersections::intersectionType(const Sphere& a, const Sphere& b) {
    const double dx = a.center.x - b.center.x;
    const double dy = a.center.y - b.center.y;
    const double dz = a.center.z - b.center.z;
    const double r = a.radius + b.radius;
    const double distanceSquared = dx * dx + dy * dy + dz * dz;

    if (distanceSquared > r * r) {
        return IntersectionType::NONE;
    }
    return distanceSquared < r * r ? IntersectionType::OVERLAP : IntersectionType::TOUCH;
}

/**
 * @brief AABBと球の関係を NONE、TOUCH、OVERLAP に分類する。
 */
Intersections::IntersectionType Intersections::intersectionType(const AABB& box, const Sphere& s) {
    // 球中心をAABBへクランプした最近接点との距離で判定する。
    const double cx = clampValue(s.center.x, box.minX, box.maxX);
    const double cy = clampValue(s.center.y, box.minY, box.maxY);
    const double cz = clampValue(s.center.z, box.minZ, box.maxZ);

    const double dx = s.center.x - cx;
    const double dy = s.center.y - cy;
    const double dz = s.center.z - cz;
    const double distanceSquared = dx * dx + dy * dy + dz * dz;
    const double radiusSquared = s.radius * s.radius;

    if (distanceSquared > radiusSquared) {
        return IntersectionType::NONE;
    }
    return distanceSquared < radiusSquared ? IntersectionType::OVERLAP : IntersectionType::TOUCH;
}

} // namespace fastgeom3d
