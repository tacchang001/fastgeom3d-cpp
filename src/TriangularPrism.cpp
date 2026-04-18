#include "fastgeom3d/TriangularPrism.h"
#include <stdexcept>

namespace fastgeom3d {

TriangularPrism makeTriangularPrism(const std::vector<Vec2>& vertices, double height) {
    if (vertices.size() != 3) {
        throw std::invalid_argument("Triangle2D requires exactly 3 vertices");
    }
    return TriangularPrism(vertices, height);
}

TriangularPrism::TriangularPrism(const std::vector<Vec2>& vertices, double height) : PolygonalPrism(vertices, height) {
    if (vertices.size() != 3) {
        throw std::invalid_argument("Triangle2D requires exactly 3 vertices");
    }
}

} // namespace fastgeom3d