#include "fastgeom3d/PolygonalPrism.h"
#include "PrismSupport.h"

namespace fastgeom3d {

/**
 * @brief 多角形底面を押し出して角柱を初期化する。
 */
PolygonalPrism::PolygonalPrism(const std::vector<Vec2>& vertices, double height) :
    base(vertices), height(height), aabb(detail::makePrismAABB(base.getAABB(), height)) {}

/**
 * @brief 押し出し高さを返す。
 */
double PolygonalPrism::getHeight() const {
    return height;
}

/**
 * @brief 底面のZ座標を返す。
 */
double PolygonalPrism::getBottomZ() const {
    return aabb.minZ;
}

/**
 * @brief 上面のZ座標を返す。
 */
double PolygonalPrism::getTopZ() const {
    return aabb.maxZ;
}

/**
 * @brief 底面となる多角形を返す。
 */
const Polygon2D& PolygonalPrism::getBase() const {
    return base;
}

/**
 * @brief 角柱を包含する軸平行境界ボックスを返す。
 */
AABB PolygonalPrism::getAABB() const {
    return aabb;
}

} // namespace fastgeom3d