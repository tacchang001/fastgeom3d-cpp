#include "fastgeom3d/TriangularPrism.h"
#include <stdexcept>

namespace fastgeom3d {

TriangularPrism makeTriangularPrism(const std::vector<Vec2>& vertices, double height) {
    if (vertices.size() != 3) {
        throw std::invalid_argument("Triangle2D requires exactly 3 vertices");
    }
    return TriangularPrism(vertices, height);
}

TriangularPrism::TriangularPrism(const std::vector<Vec2>& vertices, double height) : prism(vertices, height) {
    if (vertices.size() != 3) {
        throw std::invalid_argument("Triangle2D requires exactly 3 vertices");
    }
}

double TriangularPrism::getHeight() const {
    return prism.getHeight();
}

double TriangularPrism::getBottomZ() const {
    return prism.getBottomZ();
}

double TriangularPrism::getTopZ() const {
    return prism.getTopZ();
}

const Polygon2D& TriangularPrism::getBase() const {
    return prism.getBase();
}

AABB TriangularPrism::getAABB() const {
    return prism.getAABB();
}

const PolygonalPrism& TriangularPrism::asPolygonalPrism() const {
    return prism;
}

} // namespace fastgeom3d