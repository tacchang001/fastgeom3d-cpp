#include "fastgeom3d/Circle2D.h"
#include "fastgeom3d/AABB.h"
#include <stdexcept>

namespace fastgeom3d {

Circle2D::Circle2D(const Vec2& center_, double radius_) : center(center_), radius(radius_) {
    if (radius_ <= 0.0) {
        throw std::invalid_argument("radius must be positive");
    }
}

const Vec2& Circle2D::getCenter() const {
    return center;
}

double Circle2D::getRadius() const {
    return radius;
}

AABB Circle2D::getAABB() const {
    return AABB(
        center.x - radius,  // minX: center.x minus radius
        center.y - radius,  // minY: center.y minus radius
        0.0,                // minZ: always 0 for 2D
        center.x + radius,  // maxX: center.x plus radius
        center.y + radius,  // maxY: center.y plus radius
        0.0                 // maxZ: always 0 for 2D
    );
}

} // namespace fastgeom3d