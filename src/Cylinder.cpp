#include "fastgeom3d/Cylinder.h"
#include "fastgeom3d/Circle2D.h"
#include <stdexcept>

namespace fastgeom3d {

Cylinder::Cylinder(const Vec2& center, double radius, double height) :
    Prism(Circle2D(center, radius), height), center(center), radius(radius) {
    if (radius <= 0.0) {
        throw std::invalid_argument("radius must be positive");
    }
}

const Vec2& Cylinder::getCenter() const {
    return center;
}

double Cylinder::getRadius() const {
    return radius;
}

} // namespace fastgeom3d