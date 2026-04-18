#include "fastgeom3d/AABB.h"
#include <algorithm>
#include <limits>

namespace fastgeom3d {

AABB AABB::fromCenterHalfExtents(const Vec3& center, const Vec3& halfExtents) {
    return AABB(
        center.x - halfExtents.x,
        center.y - halfExtents.y,
        center.z - halfExtents.z,
        center.x + halfExtents.x,
        center.y + halfExtents.y,
        center.z + halfExtents.z
    );
}

AABB AABB::fromPoints(const std::vector<Vec3>& points) {
    if (points.empty()) {
        throw std::invalid_argument("points must not be empty");
    }

    double minX = std::numeric_limits<double>::infinity();
    double minY = std::numeric_limits<double>::infinity();
    double minZ = std::numeric_limits<double>::infinity();
    double maxX = -std::numeric_limits<double>::infinity();
    double maxY = -std::numeric_limits<double>::infinity();
    double maxZ = -std::numeric_limits<double>::infinity();

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
    if (points.empty()) {
        throw std::invalid_argument("points must not be empty");
    }

    double minX = std::numeric_limits<double>::infinity();
    double minY = std::numeric_limits<double>::infinity();
    double maxX = -std::numeric_limits<double>::infinity();
    double maxY = -std::numeric_limits<double>::infinity();

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
