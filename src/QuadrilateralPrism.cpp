#include "fastgeom3d/QuadrilateralPrism.h"
#include <stdexcept>

namespace fastgeom3d {

/**
 * @brief 四角形底面と高さから四角柱を生成する。
 */
QuadrilateralPrism makeQuadrilateralPrism(const std::vector<Vec2>& vertices, double height) {
    if (vertices.size() != 4) {
        throw std::invalid_argument("Quadrilateral2D requires exactly 4 vertices");
    }
    return QuadrilateralPrism(vertices, height);
}

/**
 * @brief 四角形底面と高さから四角柱を初期化する。
 */
QuadrilateralPrism::QuadrilateralPrism(const std::vector<Vec2>& vertices, double height) : prism(vertices, height) {
    if (vertices.size() != 4) {
        throw std::invalid_argument("Quadrilateral2D requires exactly 4 vertices");
    }
}

/**
 * @brief 柱の高さを返す。
 */
double QuadrilateralPrism::getHeight() const {
    return prism.getHeight();
}

/**
 * @brief 底面のZ座標を返す。
 */
double QuadrilateralPrism::getBottomZ() const {
    return prism.getBottomZ();
}

/**
 * @brief 上面のZ座標を返す。
 */
double QuadrilateralPrism::getTopZ() const {
    return prism.getTopZ();
}

/**
 * @brief 四角形底面を多角形表現として返す。
 */
const Polygon2D& QuadrilateralPrism::getBase() const {
    return prism.getBase();
}

/**
 * @brief 四角柱を包含する軸平行境界ボックスを返す。
 */
AABB QuadrilateralPrism::getAABB() const {
    return prism.getAABB();
}

/**
 * @brief 内部の汎用多角柱表現を返す。
 */
const PolygonalPrism& QuadrilateralPrism::asPolygonalPrism() const {
    return prism;
}

} // namespace fastgeom3d