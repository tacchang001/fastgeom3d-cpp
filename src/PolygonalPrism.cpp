#include "fastgeom3d/PolygonalPrism.h"
#include "PrismSupport.h"

namespace fastgeom3d {

PolygonalPrism::PolygonalPrism(const std::vector<Vec2>& vertices, double height) :
    base(vertices), height(height), aabb(detail::makePrismAABB(base.getAABB(), height)) {}

double PolygonalPrism::getHeight() const {
    return height;
}

double PolygonalPrism::getBottomZ() const {
    return aabb.minZ;
}

double PolygonalPrism::getTopZ() const {
    return aabb.maxZ;
}

const Polygon2D& PolygonalPrism::getBase() const {
    return base;
}

AABB PolygonalPrism::getAABB() const {
    return aabb;
}

} // namespace fastgeom3d