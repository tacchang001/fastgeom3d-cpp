#include "fastgeom3d/QuadrilateralPrism.h"
#include <stdexcept>

namespace fastgeom3d {

QuadrilateralPrism makeQuadrilateralPrism(const std::vector<Vec2>& vertices, double height) {
    if (vertices.size() != 4) {
        throw std::invalid_argument("Quadrilateral2D requires exactly 4 vertices");
    }
    return QuadrilateralPrism(vertices, height);
}

QuadrilateralPrism::QuadrilateralPrism(const std::vector<Vec2>& vertices, double height) : prism(vertices, height) {
    if (vertices.size() != 4) {
        throw std::invalid_argument("Quadrilateral2D requires exactly 4 vertices");
    }
}

double QuadrilateralPrism::getHeight() const {
    return prism.getHeight();
}

double QuadrilateralPrism::getBottomZ() const {
    return prism.getBottomZ();
}

double QuadrilateralPrism::getTopZ() const {
    return prism.getTopZ();
}

const Polygon2D& QuadrilateralPrism::getBase() const {
    return prism.getBase();
}

AABB QuadrilateralPrism::getAABB() const {
    return prism.getAABB();
}

const PolygonalPrism& QuadrilateralPrism::asPolygonalPrism() const {
    return prism;
}

} // namespace fastgeom3d