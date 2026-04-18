#ifndef FASTGEOM3D_SPHERE_H
#define FASTGEOM3D_SPHERE_H

#include "fastgeom3d/Shape3D.h"
#include "fastgeom3d/Vec3.h"

namespace fastgeom3d {

/**
 * @brief 3D球を表すクラス。
 *
 * Shape3Dを継承し、3D空間における球を表現します。
 */
class Sphere final : public Shape3D {
public:
    /** @brief 球の中心座標。 */
    const Vec3 center;
    /** @brief 球の半径。 */
    const double radius;

    /**
     * @brief Sphereのコンストラクタ。
     *
     * @param center_ 球の中心座標。
     * @param radius_ 球の半径。正の値でなければなりません。
     */
    Sphere(const Vec3& center_, double radius_);

    /**
     * @brief 球のAABBを取得します。
     *
     * @return 球を囲む軸平行境界ボックス。
     */
    AABB getAABB() const override;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_SPHERE_H
