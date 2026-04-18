#include "fastgeom3d/Triangle2D.h"
#include <stdexcept>

namespace fastgeom3d {

Triangle2D makeTriangle2D(const std::vector<Vec2>& vertices) {
    if (vertices.size() != 3) {
        throw std::invalid_argument("Triangle2D requires exactly 3 vertices");
    }
    return Triangle2D(vertices);
}

Triangle2D::Triangle2D(const std::vector<Vec2>& vertices) : polygon(vertices) {
    if (vertices.size() != 3) {
        throw std::invalid_argument("Triangle2D requires exactly 3 vertices");
    }
}

const std::vector<Vec2>& Triangle2D::getVertices() const {
    return polygon.getVertices();
}

AABB Triangle2D::getAABB() const {
    return polygon.getAABB();
}

const Polygon2D& Triangle2D::asPolygon() const {
    return polygon;
}

} // namespace fastgeom3d