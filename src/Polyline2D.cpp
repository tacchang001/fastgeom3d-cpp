#include "fastgeom3d/Polyline2D.h"
#include "fastgeom3d/AABB.h"
#include <stdexcept>

namespace fastgeom3d {

Polyline2D::Polyline2D(const std::vector<Vec2>& points_) : points(points_) {
    if (points.size() < 2) {
        throw std::invalid_argument("Polyline2D requires at least 2 points");
    }
}

const std::vector<Vec2>& Polyline2D::getPoints() const {
    return points;
}

AABB Polyline2D::getAABB() const {
    return AABB::fromPoints2D(points);
}

} // namespace fastgeom3d