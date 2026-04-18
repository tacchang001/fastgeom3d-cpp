#include "fastgeom3d/EllipticalCylinder.h"
#include "fastgeom3d/Ellipse2D.h"
#include "PrismSupport.h"

namespace fastgeom3d {

/**
 * @brief 楕円底面の半径と高さから楕円柱を初期化する。
 */
EllipticalCylinder::EllipticalCylinder(const Vec2& center, double radiusX, double radiusY, double height) :
    center(center), radiusX(radiusX), radiusY(radiusY), height(height),
    aabb(detail::makePrismAABB(Ellipse2D(center, radiusX, radiusY).getAABB(), height)) {}

/**
 * @brief 楕円底面の中心座標を返す。
 */
const Vec2& EllipticalCylinder::getCenter() const {
    return center;
}

/**
 * @brief 底面のX軸方向半径を返す。
 */
double EllipticalCylinder::getRadiusX() const {
    return radiusX;
}

/**
 * @brief 底面のY軸方向半径を返す。
 */
double EllipticalCylinder::getRadiusY() const {
    return radiusY;
}

/**
 * @brief 押し出し高さを返す。
 */
double EllipticalCylinder::getHeight() const {
    return height;
}

/**
 * @brief 底面のZ座標を返す。
 */
double EllipticalCylinder::getBottomZ() const {
    return aabb.minZ;
}

/**
 * @brief 上面のZ座標を返す。
 */
double EllipticalCylinder::getTopZ() const {
    return aabb.maxZ;
}

/**
 * @brief 楕円柱を包含する軸平行境界ボックスを返す。
 */
AABB EllipticalCylinder::getAABB() const {
    return aabb;
}

} // namespace fastgeom3d