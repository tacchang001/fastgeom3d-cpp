#include "fastgeom3d/EllipticalCylinder.h"
#include "fastgeom3d/Ellipse2D.h"
#include "PrismSupport.h"

namespace fastgeom3d {

EllipticalCylinder::EllipticalCylinder(const Vec2& center, double radiusX, double radiusY, double height) :
    center(center), radiusX(radiusX), radiusY(radiusY), height(height),
    aabb(detail::makePrismAABB(Ellipse2D(center, radiusX, radiusY).getAABB(), height)) {}

const Vec2& EllipticalCylinder::getCenter() const {
    return center;
}

double EllipticalCylinder::getRadiusX() const {
    return radiusX;
}

double EllipticalCylinder::getRadiusY() const {
    return radiusY;
}

double EllipticalCylinder::getHeight() const {
    return height;
}

double EllipticalCylinder::getBottomZ() const {
    return aabb.minZ;
}

double EllipticalCylinder::getTopZ() const {
    return aabb.maxZ;
}

AABB EllipticalCylinder::getAABB() const {
    return aabb;
}

} // namespace fastgeom3d