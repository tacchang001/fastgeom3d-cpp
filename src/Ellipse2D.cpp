#include "fastgeom3d/Ellipse2D.h"
#include "fastgeom3d/AABB.h"
#include <stdexcept>

namespace fastgeom3d {

/**
 * @brief 楕円を中心座標と主軸半径から初期化する。
 */
Ellipse2D::Ellipse2D(const Vec2& center_, double radiusX_, double radiusY_) :
    center(center_), radiusX(radiusX_), radiusY(radiusY_) {
    if (radiusX_ <= 0.0 || radiusY_ <= 0.0) {
        throw std::invalid_argument("radiusX and radiusY must be positive");
    }
}

/**
 * @brief 楕円の中心座標を返す。
 */
const Vec2& Ellipse2D::getCenter() const {
    return center;
}

/**
 * @brief X軸方向の半径を返す。
 */
double Ellipse2D::getRadiusX() const {
    return radiusX;
}

/**
 * @brief Y軸方向の半径を返す。
 */
double Ellipse2D::getRadiusY() const {
    return radiusY;
}

/**
 * @brief 楕円を包含する軸平行境界ボックスを返す。
 */
AABB Ellipse2D::getAABB() const {
    return AABB(
        center.x - radiusX,
        center.y - radiusY,
        0.0,
        center.x + radiusX,
        center.y + radiusY,
        0.0
    );
}

} // namespace fastgeom3d