#include "fastgeom3d/Polygon2D.h"
#include "fastgeom3d/AABB.h"
#include <stdexcept>

namespace fastgeom3d {

Polygon2D::Polygon2D(const std::vector<Vec2>& vertices_) : vertices(vertices_) {
    if (vertices.size() < 3) {
        throw std::invalid_argument("Polygon2D requires at least 3 vertices");
    }
}

const std::vector<Vec2>& Polygon2D::getVertices() const {
    return vertices;
}

AABB Polygon2D::getAABB() const {
    return AABB::fromPoints2D(vertices);
}

} // namespace fastgeom3d