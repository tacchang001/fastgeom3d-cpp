#include "fastgeom3d/Polyline.h"
#include "fastgeom3d/AABB.h"
#include "fastgeom3d/UTMCoordinate.h"
#include <stdexcept>

namespace fastgeom3d {

Polyline::Polyline(const std::vector<Vec3>& points_) : points(points_) {
    if (points.size() < 2) {
        throw std::invalid_argument("Polyline requires at least 2 points");
    }
}

const std::vector<Vec3>& Polyline::getPoints() const {
    return points;
}

Polyline Polyline::fromUTM(const std::vector<UTMCoordinate>& utmPoints) {
    // utmPoints: UTM座標のリスト
    std::vector<Vec3> points; // 変換後のVec3点のリスト
    points.reserve(utmPoints.size()); // メモリ予約
    for (const auto& utm : utmPoints) {
        points.push_back(utm.toVec3()); // UTMをVec3に変換
    }
    return Polyline(points);
}

AABB Polyline::getAABB() const {
    return AABB::fromPoints(points);
}

} // namespace fastgeom3d
