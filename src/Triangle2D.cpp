#include "fastgeom3d/Triangle2D.h"
#include <stdexcept>

namespace fastgeom3d {

/**
 * @brief 3頂点から三角形を生成する。
 */
Triangle2D makeTriangle2D(const std::vector<Vec2>& vertices) {
    if (vertices.size() != 3) {
        throw std::invalid_argument("Triangle2D requires exactly 3 vertices");
    }
    return Triangle2D(vertices);
}

/**
 * @brief 3頂点から三角形を初期化する。
 */
Triangle2D::Triangle2D(const std::vector<Vec2>& vertices) : polygon(vertices) {
    if (vertices.size() != 3) {
        throw std::invalid_argument("Triangle2D requires exactly 3 vertices");
    }
}

/**
 * @brief 三角形の頂点列を返す。
 */
const std::vector<Vec2>& Triangle2D::getVertices() const {
    return polygon.getVertices();
}

/**
 * @brief 三角形を包含する軸平行境界ボックスを返す。
 */
AABB Triangle2D::getAABB() const {
    return polygon.getAABB();
}

/**
 * @brief 三角形を多角形表現として返す。
 */
const Polygon2D& Triangle2D::asPolygon() const {
    return polygon;
}

} // namespace fastgeom3d