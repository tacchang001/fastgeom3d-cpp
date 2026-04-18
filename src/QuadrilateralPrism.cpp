#include "fastgeom3d/QuadrilateralPrism.h"
#include <stdexcept>

namespace fastgeom3d {

QuadrilateralPrism makeQuadrilateralPrism(const std::vector<Vec2>& vertices, double height) {
    if (vertices.size() != 4) {
        throw std::invalid_argument("Quadrilateral2D requires exactly 4 vertices");
    }
    return QuadrilateralPrism(vertices, height);
}

QuadrilateralPrism::QuadrilateralPrism(const std::vector<Vec2>& vertices, double height) : PolygonalPrism(vertices, height) {
    if (vertices.size() != 4) {
        throw std::invalid_argument("Quadrilateral2D requires exactly 4 vertices");
    }
}

} // namespace fastgeom3d