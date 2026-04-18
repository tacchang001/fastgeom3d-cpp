#include "fastgeom3d/Intersections.h"
#include "fastgeom3d/AABB.h"
#include "fastgeom3d/Circle2D.h"
#include "fastgeom3d/Ellipse2D.h"
#include "fastgeom3d/Polygon2D.h"
#include "fastgeom3d/Polyline.h"
#include "fastgeom3d/Polyline2D.h"
#include "fastgeom3d/Sphere.h"
#include "fastgeom3d/Vec2.h"
#include <algorithm>
#include <cmath>

namespace fastgeom3d {

namespace {

double clampValue(double value, double min, double max) {
    return value < min ? min : (value > max ? max : value);
}

bool intervalIntersects(double minA, double maxA, double minB, double maxB) {
    return minA <= maxB && maxA >= minB;
}

bool intervalOverlaps(double minA, double maxA, double minB, double maxB) {
    return minA < maxB && maxA > minB;
}

double squaredDistance(const Vec2& a, const Vec2& b) {
    const double dx = a.x - b.x;
    const double dy = a.y - b.y;
    return dx * dx + dy * dy;
}

int ccw(const Vec2& a, const Vec2& b, const Vec2& c) {
    const double value = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return value > 0 ? 1 : (value < 0 ? -1 : 0);
}

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

bool segmentsIntersect(const Vec2& a1, const Vec2& a2, const Vec2& b1, const Vec2& b2) {
    if (pointOnSegment(a1, b1, b2) || pointOnSegment(a2, b1, b2) ||
        pointOnSegment(b1, a1, a2) || pointOnSegment(b2, a1, a2)) {
        return true;
    }
    return ccw(a1, a2, b1) != ccw(a1, a2, b2) && ccw(b1, b2, a1) != ccw(b1, b2, a2);
}

bool pointInPolygon(const Vec2& point, const Polygon2D& polygon) {
    const auto& vertices = polygon.getVertices();
    bool inside = false;
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

bool pointInEllipse(const Vec2& point, const Ellipse2D& ellipse) {
    const double dx = (point.x - ellipse.getCenter().x) / ellipse.getRadiusX();
    const double dy = (point.y - ellipse.getCenter().y) / ellipse.getRadiusY();
    return dx * dx + dy * dy <= 1.0;
}

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

    double t = -(fx * dx + fy * dy) / aCoef;
    t = std::max(0.0, std::min(1.0, t));
    const Vec2 closest(a.x + t * dx, a.y + t * dy);
    return squaredDistance(closest, center) <= r2;
}

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

bool Intersections::intersect(const AABB& a, const AABB& b) {
    return intersectionType(a, b) != IntersectionType::NONE;
}

bool Intersections::intersect(const Sphere& a, const Sphere& b) {
    return intersectionType(a, b) != IntersectionType::NONE;
}

bool Intersections::intersect(const AABB& box, const Sphere& s) {
    return intersectionType(box, s) != IntersectionType::NONE;
}

bool Intersections::intersect(const Polyline2D& line, const Polyline2D& other) {
    const auto& points1 = line.getPoints(); // lineの点リスト
    const auto& points2 = other.getPoints(); // otherの点リスト
    for (std::size_t i = 1; i < points1.size(); ++i) {
        const Vec2& a1 = points1[i - 1]; // セグメントの始点
        const Vec2& a2 = points1[i]; // セグメントの終点
        for (std::size_t j = 1; j < points2.size(); ++j) {
            const Vec2& b1 = points2[j - 1]; // 他のセグメントの始点
            const Vec2& b2 = points2[j]; // 他のセグメントの終点
            if (segmentsIntersect(a1, a2, b1, b2)) {
                return true;
            }
        }
    }
    return false;
}

bool Intersections::intersect(const Polyline2D& line, const Circle2D& circle) {
    const auto& center = circle.getCenter(); // 円の中心
    const double radius = circle.getRadius(); // 円の半径
    const auto& points = line.getPoints(); // ラインの点リスト
    for (std::size_t i = 1; i < points.size(); ++i) {
        if (segmentIntersectsCircle(points[i - 1], points[i], center, radius)) {
            return true;
        }
    }
    return false;
}

bool Intersections::intersectPolylineWithPolygonVertices(const Polyline2D& line, const std::vector<Vec2>& vertices) {
    const auto& points = line.getPoints(); // ラインの点リスト
    for (std::size_t i = 1; i < points.size(); ++i) {
        const Vec2& a = points[i - 1]; // セグメントの始点
        const Vec2& b = points[i]; // セグメントの終点
        for (std::size_t j = 1; j < vertices.size(); ++j) {
            if (segmentsIntersect(a, b, vertices[j - 1], vertices[j])) {
                return true;
            }
        }
        if (segmentsIntersect(a, b, vertices[vertices.size() - 1], vertices[0])) {
            return true;
        }
    }
    for (const auto& point : points) {
        if (pointInPolygon(point, Polygon2D(vertices))) {
            return true;
        }
    }
    return false;
}

bool Intersections::intersect(const Polyline2D& line, const Polygon2D& polygon) {
    return intersectPolylineWithPolygonVertices(line, polygon.getVertices());
}

bool Intersections::intersect(const Circle2D& a, const Circle2D& b) {
    const double radiusSum = a.getRadius() + b.getRadius(); // 半径の和
    return squaredDistance(a.getCenter(), b.getCenter()) <= radiusSum * radiusSum;
}

bool Intersections::intersectPolygonWithCircleVertices(const std::vector<Vec2>& vertices, const Circle2D& circle) {
    if (pointInPolygon(circle.getCenter(), Polygon2D(vertices))) {
        return true;
    }
    for (std::size_t i = 1; i < vertices.size(); ++i) {
        if (segmentIntersectsCircle(vertices[i - 1], vertices[i], circle.getCenter(), circle.getRadius())) {
            return true;
        }
    }
    return segmentIntersectsCircle(vertices[vertices.size() - 1], vertices[0], circle.getCenter(), circle.getRadius());
}

bool Intersections::intersect(const Polygon2D& polygon, const Circle2D& circle) {
    return intersectPolygonWithCircleVertices(polygon.getVertices(), circle);
}

bool Intersections::intersectPolygonVertices(const std::vector<Vec2>& verticesA, const std::vector<Vec2>& verticesB) {
    for (std::size_t i = 1; i < verticesA.size(); ++i) {
        const Vec2& a1 = verticesA[i - 1]; // Aのセグメント始点
        const Vec2& a2 = verticesA[i]; // Aのセグメント終点
        for (std::size_t j = 1; j < verticesB.size(); ++j) {
            if (segmentsIntersect(a1, a2, verticesB[j - 1], verticesB[j])) {
                return true;
            }
        }
        if (segmentsIntersect(a1, a2, verticesB[verticesB.size() - 1], verticesB[0])) {
            return true;
        }
    }
    if (pointInPolygon(verticesA[0], Polygon2D(verticesB))) {
        return true;
    }
    return pointInPolygon(verticesB[0], Polygon2D(verticesA));
}

bool Intersections::intersect(const Polygon2D& a, const Polygon2D& b) {
    return intersectPolygonVertices(a.getVertices(), b.getVertices());
}

bool Intersections::intersect(const Polyline2D& line, const Ellipse2D& ellipse) {
    const auto& points = line.getPoints(); // ラインの点リスト
    for (std::size_t i = 1; i < points.size(); ++i) {
        if (segmentIntersectsEllipse(points[i - 1], points[i], ellipse)) {
            return true;
        }
    }
    for (const auto& point : points) {
        if (pointInEllipse(point, ellipse)) {
            return true;
        }
    }
    return false;
}

bool Intersections::intersect(const Circle2D& circle, const Ellipse2D& ellipse) {
    if (pointInEllipse(circle.getCenter(), ellipse)) {
        return true;
    }
    const double radius = circle.getRadius(); // 円の半径
    const Vec2 center = circle.getCenter(); // 円の中心
    for (int i = 0; i < 32; ++i) {
        const double angle = 2.0 * M_PI * i / 32.0; // サンプル角度
        const Vec2 sample(center.x + radius * std::cos(angle), center.y + radius * std::sin(angle)); // 円周上のサンプル点
        if (pointInEllipse(sample, ellipse)) {
            return true;
        }
    }
    return false;
}

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

bool Intersections::intersect(const Polygon2D& polygon, const Ellipse2D& ellipse) {
    return intersectPolygonWithEllipseVertices(polygon.getVertices(), ellipse);
}

Intersections::IntersectionType Intersections::intersectionType(const AABB& a, const AABB& b) {
    const bool intersects = intervalIntersects(a.minX, a.maxX, b.minX, b.maxX) &&
                            intervalIntersects(a.minY, a.maxY, b.minY, b.maxY) &&
                            intervalIntersects(a.minZ, a.maxZ, b.minZ, b.maxZ); // 各軸で交差するか
    if (!intersects) {
        return IntersectionType::NONE;
    }

    const bool overlaps = intervalOverlaps(a.minX, a.maxX, b.minX, b.maxX) &&
                          intervalOverlaps(a.minY, a.maxY, b.minY, b.maxY) &&
                          intervalOverlaps(a.minZ, a.maxZ, b.minZ, b.maxZ); // 各軸で重なりがあるか
    return overlaps ? IntersectionType::OVERLAP : IntersectionType::TOUCH;
}

Intersections::IntersectionType Intersections::intersectionType(const Sphere& a, const Sphere& b) {
    const double dx = a.center.x - b.center.x; // x差
    const double dy = a.center.y - b.center.y; // y差
    const double dz = a.center.z - b.center.z; // z差
    const double r = a.radius + b.radius; // 半径の和
    const double distanceSquared = dx * dx + dy * dy + dz * dz; // 距離の二乗

    if (distanceSquared > r * r) {
        return IntersectionType::NONE;
    }
    return distanceSquared < r * r ? IntersectionType::OVERLAP : IntersectionType::TOUCH;
}

Intersections::IntersectionType Intersections::intersectionType(const AABB& box, const Sphere& s) {
    const double cx = clampValue(s.center.x, box.minX, box.maxX); // ボックス内にクランプされたx
    const double cy = clampValue(s.center.y, box.minY, box.maxY); // ボックス内にクランプされたy
    const double cz = clampValue(s.center.z, box.minZ, box.maxZ); // ボックス内にクランプされたz

    const double dx = s.center.x - cx; // 球中心からクランプ点へのx差
    const double dy = s.center.y - cy; // y差
    const double dz = s.center.z - cz; // z差
    const double distanceSquared = dx * dx + dy * dy + dz * dz; // 距離の二乗
    const double radiusSquared = s.radius * s.radius; // 半径の二乗

    if (distanceSquared > radiusSquared) {
        return IntersectionType::NONE;
    }
    return distanceSquared < radiusSquared ? IntersectionType::OVERLAP : IntersectionType::TOUCH;
}

} // namespace fastgeom3d
