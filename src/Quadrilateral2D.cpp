#include "fastgeom3d/Quadrilateral2D.h"
#include <stdexcept>

namespace fastgeom3d {

Quadrilateral2D makeQuadrilateral2D(const std::vector<Vec2>& vertices) {
    if (vertices.size() != 4) {
        throw std::invalid_argument("Quadrilateral2D requires exactly 4 vertices");
    }
    return Quadrilateral2D(vertices);
}

Quadrilateral2D::Quadrilateral2D(const std::vector<Vec2>& vertices) : polygon(vertices) {
    if (vertices.size() != 4) {
        throw std::invalid_argument("Quadrilateral2D requires exactly 4 vertices");
    }
}

const std::vector<Vec2>& Quadrilateral2D::getVertices() const {
    return polygon.getVertices();
}

AABB Quadrilateral2D::getAABB() const {
    return polygon.getAABB();
}

const Polygon2D& Quadrilateral2D::asPolygon() const {
    return polygon;
}

} // namespace fastgeom3d