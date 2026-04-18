#include "fastgeom3d/AABB.h"
#include <algorithm>
#include <limits>

namespace fastgeom3d {

AABB::AABB(double minX_, double minY_, double minZ_,
           double maxX_, double maxY_, double maxZ_) :
    minX(minX_), minY(minY_), minZ(minZ_),
    maxX(maxX_), maxY(maxY_), maxZ(maxZ_) {}

AABB AABB::fromCenterHalfExtents(const Vec3& center, const Vec3& halfExtents) {
    // center: AABBの中心座標
    // halfExtents: 各軸方向の半拡張
    return AABB(
        center.x - halfExtents.x, // minX
        center.y - halfExtents.y, // minY
        center.z - halfExtents.z, // minZ
        center.x + halfExtents.x, // maxX
        center.y + halfExtents.y, // maxY
        center.z + halfExtents.z  // maxZ
    );
}

AABB AABB::fromPoints(const std::vector<Vec3>& points) {
    // points: AABBを計算する点のリスト
    if (points.empty()) {
        throw std::invalid_argument("points must not be empty");
    }

    double minX = std::numeric_limits<double>::infinity(); // 最小x座標の初期値
    double minY = std::numeric_limits<double>::infinity(); // 最小y座標の初期値
    double minZ = std::numeric_limits<double>::infinity(); // 最小z座標の初期値
    double maxX = -std::numeric_limits<double>::infinity(); // 最大x座標の初期値
    double maxY = -std::numeric_limits<double>::infinity(); // 最大y座標の初期値
    double maxZ = -std::numeric_limits<double>::infinity(); // 最大z座標の初期値

    for (const auto& point : points) {
        minX = std::min(minX, point.x);
        minY = std::min(minY, point.y);
        minZ = std::min(minZ, point.z);
        maxX = std::max(maxX, point.x);
        maxY = std::max(maxY, point.y);
        maxZ = std::max(maxZ, point.z);
    }

    return AABB(minX, minY, minZ, maxX, maxY, maxZ);
}

AABB AABB::fromPoints2D(const std::vector<Vec2>& points) {
    // points: 2D点のリスト
    if (points.empty()) {
        throw std::invalid_argument("points must not be empty");
    }

    double minX = std::numeric_limits<double>::infinity(); // 最小x座標
    double minY = std::numeric_limits<double>::infinity(); // 最小y座標
    double maxX = -std::numeric_limits<double>::infinity(); // 最大x座標
    double maxY = -std::numeric_limits<double>::infinity(); // 最大y座標

    for (const auto& point : points) {
        minX = std::min(minX, point.x);
        minY = std::min(minY, point.y);
        maxX = std::max(maxX, point.x);
        maxY = std::max(maxY, point.y);
    }

    return AABB(minX, minY, 0.0, maxX, maxY, 0.0);
}

AABB AABB::getAABB() const {
    return *this;
}

bool AABB::operator==(const AABB& other) const {
    return minX == other.minX && minY == other.minY && minZ == other.minZ &&
           maxX == other.maxX && maxY == other.maxY && maxZ == other.maxZ;
}

bool AABB::operator!=(const AABB& other) const {
    return !(*this == other);
}

} // namespace fastgeom3d
