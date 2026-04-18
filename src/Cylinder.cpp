#include "fastgeom3d/Cylinder.h"
#include "fastgeom3d/Circle2D.h"
#include "PrismSupport.h"

namespace fastgeom3d {

Cylinder::Cylinder(const Vec2& center, double radius, double height) :
    center(center), radius(radius), height(height), aabb(detail::makePrismAABB(Circle2D(center, radius).getAABB(), height)) {}

const Vec2& Cylinder::getCenter() const {
    return center;
}

double Cylinder::getRadius() const {
    return radius;
}

double Cylinder::getHeight() const {
    return height;
}

double Cylinder::getBottomZ() const {
    return aabb.minZ;
}

double Cylinder::getTopZ() const {
    return aabb.maxZ;
}

AABB Cylinder::getAABB() const {
    return aabb;
}

} // namespace fastgeom3d