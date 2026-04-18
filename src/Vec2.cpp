#include "fastgeom3d/Vec2.h"
#include "fastgeom3d/Vec3.h"

namespace fastgeom3d {

Vec2::Vec2(double x_, double y_) : x(x_), y(y_) {}

Vec2 Vec2::fromVec3(const Vec3& vec3) {
    return Vec2(vec3.x, vec3.y);
}

} // namespace fastgeom3d