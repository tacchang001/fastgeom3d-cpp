#include "fastgeom3d/AABB.h"
#include <algorithm>
#include <limits>

namespace fastgeom3d {

/**
 * @brief 軸平行境界ボックスを各軸の境界値から初期化する。
 */
AABB::AABB(double minX_, double minY_, double minZ_,
           double maxX_, double maxY_, double maxZ_) :
    minX(minX_), minY(minY_), minZ(minZ_),
    maxX(maxX_), maxY(maxY_), maxZ(maxZ_) {}

/**
 * @brief 中心座標と半サイズからAABBを生成する。
 */
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

/**
 * @brief 3次元点群を包含する最小のAABBを生成する。
 */
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

    // 全点を一度走査して各軸の最小値と最大値を更新する。
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

/**
 * @brief 2次元点群を包含する最小のAABBを生成する。
 */
AABB AABB::fromPoints2D(const std::vector<Vec2>& points) {
    if (points.empty()) {
        throw std::invalid_argument("points must not be empty");
    }

    double minX = std::numeric_limits<double>::infinity();
    double minY = std::numeric_limits<double>::infinity();
    double maxX = -std::numeric_limits<double>::infinity();
    double maxY = -std::numeric_limits<double>::infinity();

    // 2D形状は Z=0 平面に固定して境界を集約する。
    for (const auto& point : points) {
        minX = std::min(minX, point.x);
        minY = std::min(minY, point.y);
        maxX = std::max(maxX, point.x);
        maxY = std::max(maxY, point.y);
    }

    return AABB(minX, minY, 0.0, maxX, maxY, 0.0);
}

/**
 * @brief このボックス自身をAABBとして返す。
 */
AABB AABB::getAABB() const {
    return *this;
}

/**
 * @brief 全境界値が厳密一致するかを判定する。
 */
bool AABB::operator==(const AABB& other) const {
    return minX == other.minX && minY == other.minY && minZ == other.minZ &&
           maxX == other.maxX && maxY == other.maxY && maxZ == other.maxZ;
}

/**
 * @brief 全境界値の厳密一致に基づいて不一致を判定する。
 */
bool AABB::operator!=(const AABB& other) const {
    return !(*this == other);
}

} // namespace fastgeom3d
