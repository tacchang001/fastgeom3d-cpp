#include "fastgeom3d/PolygonalPrism.h"

namespace fastgeom3d {

PolygonalPrism::PolygonalPrism(const std::vector<Vec2>& vertices, double height) :
    Prism(Polygon2D(vertices), height), base(vertices) {}

const Polygon2D& PolygonalPrism::getBase() const {
    return base;
}

} // namespace fastgeom3d