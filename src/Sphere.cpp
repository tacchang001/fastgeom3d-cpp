#include "fastgeom3d/Sphere.h"
#include "fastgeom3d/AABB.h"

namespace fastgeom3d {

/**
 * @brief 球を中心座標と半径から初期化する。
 */
Sphere::Sphere(const Vec3& center_, double radius_) : center(center_), radius(radius_) {}

/**
 * @brief 球を包含する軸平行境界ボックスを返す。
 */
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