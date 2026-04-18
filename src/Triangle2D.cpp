#include "fastgeom3d/Triangle2D.h"
#include <stdexcept>

namespace fastgeom3d {

Triangle2D makeTriangle2D(const std::vector<Vec2>& vertices) {
    if (vertices.size() != 3) {
        throw std::invalid_argument("Triangle2D requires exactly 3 vertices");
    }
    return Triangle2D(vertices);
}

Triangle2D::Triangle2D(const std::vector<Vec2>& vertices) : Polygon2D(vertices) {
    if (vertices.size() != 3) {
        throw std::invalid_argument("Triangle2D requires exactly 3 vertices");
    }
}

} // namespace fastgeom3d