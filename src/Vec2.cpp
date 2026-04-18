#include "fastgeom3d/Vec2.h"
#include "fastgeom3d/Vec3.h"

namespace fastgeom3d {

/**
 * @brief 2次元ベクトルを直交座標成分から初期化する。
 */
Vec2::Vec2(double x_, double y_) : x(x_), y(y_) {}

/**
 * @brief 3次元ベクトルからZ成分を除いて2次元ベクトルを生成する。
 */
Vec2 Vec2::fromVec3(const Vec3& vec3) {
    return Vec2(vec3.x, vec3.y);
}

} // namespace fastgeom3d