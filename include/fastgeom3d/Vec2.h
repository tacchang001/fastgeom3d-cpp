#ifndef FASTGEOM3D_VEC2_H
#define FASTGEOM3D_VEC2_H

namespace fastgeom3d {

class Vec3;

/**
 * @brief 2Dベクトルを表すクラス。
 *
 * xとyの座標を持つ2次元ベクトルです。
 */
class Vec2 {
public:
    /** @brief x座標。 */
    double x;
    /** @brief y座標。 */
    double y;

    /**
     * @brief Vec2のコンストラクタ。
     *
     * @param x_ x座標。
     * @param y_ y座標。
     */
    Vec2(double x_, double y_);

    /**
     * @brief Vec3からVec2を作成します。
     *
     * @param vec3 3Dベクトル。
     * @return Vec2オブジェクト (x, y成分)。
     */
    static Vec2 fromVec3(const Vec3& vec3);
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_VEC2_H
