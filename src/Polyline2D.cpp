#include "fastgeom3d/Polyline2D.h"
#include "fastgeom3d/AABB.h"
#include <stdexcept>

namespace fastgeom3d {

/**
 * @brief 2次元ポリラインを順序付き点列から初期化する。
 */
Polyline2D::Polyline2D(const std::vector<Vec2>& points_) : points(points_) {
    if (points.size() < 2) {
        throw std::invalid_argument("Polyline2D requires at least 2 points");
    }
}

/**
 * @brief 2次元ポリラインの制御点列を返す。
 */
const std::vector<Vec2>& Polyline2D::getPoints() const {
    return points;
}

/**
 * @brief 2次元ポリラインを包含する軸平行境界ボックスを返す。
 */
AABB Polyline2D::getAABB() const {
    return AABB::fromPoints2D(points);
}

} // namespace fastgeom3d