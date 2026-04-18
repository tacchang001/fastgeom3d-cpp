#include "fastgeom3d/EllipticalCylinder.h"
#include "fastgeom3d/Ellipse2D.h"
#include <stdexcept>

namespace fastgeom3d {

EllipticalCylinder::EllipticalCylinder(const Vec2& center, double radiusX, double radiusY, double height) :
    Prism(Ellipse2D(center, radiusX, radiusY), height),
    center(center), radiusX(radiusX), radiusY(radiusY) {
    if (radiusX <= 0.0 || radiusY <= 0.0) {
        throw std::invalid_argument("radiusX and radiusY must be positive");
    }
}

const Vec2& EllipticalCylinder::getCenter() const {
    return center;
}

double EllipticalCylinder::getRadiusX() const {
    return radiusX;
}

double EllipticalCylinder::getRadiusY() const {
    return radiusY;
}

} // namespace fastgeom3d