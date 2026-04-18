#include "fastgeom3d/TriangularPrism.h"
#include <stdexcept>

namespace fastgeom3d {

/**
 * @brief 三角形底面と高さから三角柱を生成する。
 */
TriangularPrism makeTriangularPrism(const std::vector<Vec2>& vertices, double height) {
    if (vertices.size() != 3) {
        throw std::invalid_argument("Triangle2D requires exactly 3 vertices");
    }
    return TriangularPrism(vertices, height);
}

/**
 * @brief 三角形底面と高さから三角柱を初期化する。
 */
TriangularPrism::TriangularPrism(const std::vector<Vec2>& vertices, double height) : prism(vertices, height) {
    if (vertices.size() != 3) {
        throw std::invalid_argument("Triangle2D requires exactly 3 vertices");
    }
}

/**
 * @brief 柱の高さを返す。
 */
double TriangularPrism::getHeight() const {
    return prism.getHeight();
}

/**
 * @brief 底面のZ座標を返す。
 */
double TriangularPrism::getBottomZ() const {
    return prism.getBottomZ();
}

/**
 * @brief 上面のZ座標を返す。
 */
double TriangularPrism::getTopZ() const {
    return prism.getTopZ();
}

/**
 * @brief 三角形底面を多角形表現として返す。
 */
const Polygon2D& TriangularPrism::getBase() const {
    return prism.getBase();
}

/**
 * @brief 三角柱を包含する軸平行境界ボックスを返す。
 */
AABB TriangularPrism::getAABB() const {
    return prism.getAABB();
}

/**
 * @brief 内部の汎用多角柱表現を返す。
 */
const PolygonalPrism& TriangularPrism::asPolygonalPrism() const {
    return prism;
}

} // namespace fastgeom3d