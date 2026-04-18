#include "fastgeom3d/Cylinder.h"
#include "fastgeom3d/Circle2D.h"
#include "PrismSupport.h"

namespace fastgeom3d {

/**
 * @brief 円形底面と高さから円柱を初期化する。
 */
Cylinder::Cylinder(const Vec2& center, double radius, double height) :
    center(center), radius(radius), height(height), aabb(detail::makePrismAABB(Circle2D(center, radius).getAABB(), height)) {}

/**
 * @brief 円形底面の中心座標を返す。
 */
const Vec2& Cylinder::getCenter() const {
    return center;
}

/**
 * @brief 円柱の半径を返す。
 */
double Cylinder::getRadius() const {
    return radius;
}

/**
 * @brief 円柱の高さを返す。
 */
double Cylinder::getHeight() const {
    return height;
}

/**
 * @brief 底面のZ座標を返す。
 */
double Cylinder::getBottomZ() const {
    return aabb.minZ;
}

/**
 * @brief 上面のZ座標を返す。
 */
double Cylinder::getTopZ() const {
    return aabb.maxZ;
}

/**
 * @brief 円柱を包含する軸平行境界ボックスを返す。
 */
AABB Cylinder::getAABB() const {
    return aabb;
}

} // namespace fastgeom3d