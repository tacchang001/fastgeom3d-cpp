#include "fastgeom3d/Ellipse2D.h"
#include "fastgeom3d/AABB.h"
#include <stdexcept>

namespace fastgeom3d {

Ellipse2D::Ellipse2D(const Vec2& center_, double radiusX_, double radiusY_) :
    center(center_), radiusX(radiusX_), radiusY(radiusY_) {
    if (radiusX_ <= 0.0 || radiusY_ <= 0.0) {
        throw std::invalid_argument("radiusX and radiusY must be positive");
    }
}

const Vec2& Ellipse2D::getCenter() const {
    return center;
}

double Ellipse2D::getRadiusX() const {
    return radiusX;
}

double Ellipse2D::getRadiusY() const {
    return radiusY;
}

AABB Ellipse2D::getAABB() const {
    return AABB(
        center.x - radiusX,
        center.y - radiusY,
        0.0,
        center.x + radiusX,
        center.y + radiusY,
        0.0
    );
}

} // namespace fastgeom3d