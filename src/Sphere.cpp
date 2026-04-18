#include "fastgeom3d/Sphere.h"
#include "fastgeom3d/AABB.h"

namespace fastgeom3d {

Sphere::Sphere(const Vec3& center_, double radius_) : center(center_), radius(radius_) {}

AABB Sphere::getAABB() const {
    const double r = radius;
    return AABB(
        center.x - r,
        center.y - r,
        center.z - r,
        center.x + r,
        center.y + r,
        center.z + r
    );
}

} // namespace fastgeom3d