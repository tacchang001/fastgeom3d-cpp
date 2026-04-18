#ifndef FASTGEOM3D_SPHERE_H
#define FASTGEOM3D_SPHERE_H

#include "fastgeom3d/Shape3D.h"
#include "fastgeom3d/Vec3.h"
#include "fastgeom3d/AABB.h"

namespace fastgeom3d {

class Sphere final : public Shape3D {
public:
    const Vec3 center;
    const double radius;

    Sphere(const Vec3& center_, double radius_) : center(center_), radius(radius_) {}

    AABB getAABB() const override {
        const double r = radius;
        return AABB(
            center.x - r, center.y - r, center.z - r,
            center.x + r, center.y + r, center.z + r
        );
    }
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_SPHERE_H
