#ifndef FASTGEOM3D_VEC2_H
#define FASTGEOM3D_VEC2_H

#include "fastgeom3d/Vec3.h"

namespace fastgeom3d {

struct Vec2 {
    const double x;
    const double y;

    Vec2(double x_, double y_) : x(x_), y(y_) {}

    static Vec2 fromVec3(const Vec3& vec3) {
        return Vec2(vec3.x, vec3.y);
    }
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_VEC2_H
