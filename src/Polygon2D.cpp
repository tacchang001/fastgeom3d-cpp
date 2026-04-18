#include "fastgeom3d/Polygon2D.h"
#include "fastgeom3d/AABB.h"
#include <stdexcept>

namespace fastgeom3d {

/**
 * @brief 多角形を順序付き頂点列から初期化する。
 */
Polygon2D::Polygon2D(const std::vector<Vec2>& vertices_) : vertices(vertices_) {
    if (vertices.size() < 3) {
        throw std::invalid_argument("Polygon2D requires at least 3 vertices");
    }
}

/**
 * @brief 多角形の頂点列を返す。
 */
const std::vector<Vec2>& Polygon2D::getVertices() const {
    return vertices;
}

/**
 * @brief 多角形を包含する軸平行境界ボックスを返す。
 */
AABB Polygon2D::getAABB() const {
    return AABB::fromPoints2D(vertices);
}

} // namespace fastgeom3d