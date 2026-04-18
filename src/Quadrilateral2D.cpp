#include "fastgeom3d/Quadrilateral2D.h"
#include <stdexcept>

namespace fastgeom3d {

/**
 * @brief 4頂点から四角形を生成する。
 */
Quadrilateral2D makeQuadrilateral2D(const std::vector<Vec2>& vertices) {
    if (vertices.size() != 4) {
        throw std::invalid_argument("Quadrilateral2D requires exactly 4 vertices");
    }
    return Quadrilateral2D(vertices);
}

/**
 * @brief 4頂点から四角形を初期化する。
 */
Quadrilateral2D::Quadrilateral2D(const std::vector<Vec2>& vertices) : polygon(vertices) {
    if (vertices.size() != 4) {
        throw std::invalid_argument("Quadrilateral2D requires exactly 4 vertices");
    }
}

/**
 * @brief 四角形の頂点列を返す。
 */
const std::vector<Vec2>& Quadrilateral2D::getVertices() const {
    return polygon.getVertices();
}

/**
 * @brief 四角形を包含する軸平行境界ボックスを返す。
 */
AABB Quadrilateral2D::getAABB() const {
    return polygon.getAABB();
}

/**
 * @brief 四角形を多角形表現として返す。
 */
const Polygon2D& Quadrilateral2D::asPolygon() const {
    return polygon;
}

} // namespace fastgeom3d