#include "fastgeom3d/Circle2D.h"
#include "fastgeom3d/AABB.h"
#include <stdexcept>

namespace fastgeom3d {

/**
 * @brief 円を中心座標と半径から初期化する。
 */
Circle2D::Circle2D(const Vec2& center_, double radius_) : center(center_), radius(radius_) {
    if (radius_ <= 0.0) {
        throw std::invalid_argument("radius must be positive");
    }
}

/**
 * @brief 円の中心座標を返す。
 */
const Vec2& Circle2D::getCenter() const {
    return center;
}

/**
 * @brief 円の半径を返す。
 */
double Circle2D::getRadius() const {
    return radius;
}

/**
 * @brief 円を包含する軸平行境界ボックスを返す。
 */
AABB Circle2D::getAABB() const {
    return AABB(
        center.x - radius,
        center.y - radius,
        0.0,
        center.x + radius,
        center.y + radius,
        0.0
    );
}

} // namespace fastgeom3d