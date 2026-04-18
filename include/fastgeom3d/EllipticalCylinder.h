#ifndef FASTGEOM3D_ELLIPTICALCYLINDER_H
#define FASTGEOM3D_ELLIPTICALCYLINDER_H

#include "fastgeom3d/AABB.h"
#include "fastgeom3d/Vec2.h"

namespace fastgeom3d {

/**
 * @brief 楕円柱を表すクラス。
 *
 * 底面が楕円である3D形状を表現します。
 */
class EllipticalCylinder final {
public:
    /**
     * @brief EllipticalCylinderのコンストラクタ。
     *
     * @param center 楕円柱の底面の中心座標。
     * @param radiusX x方向の半径。正の値でなければならない。
     * @param radiusY y方向の半径。正の値でなければならない。
     * @param height 楕円柱の高さ。
     * @throws std::invalid_argument radiusXまたはradiusYが正でない場合。
     */
    EllipticalCylinder(const Vec2& center, double radiusX, double radiusY, double height);

    /**
     * @brief 楕円柱の底面の中心座標を取得します。
     *
     * @return 中心座標。
     */
    const Vec2& getCenter() const;

    /**
     * @brief x方向の半径を取得します。
     *
     * @return x方向の半径。
     */
    double getRadiusX() const;

    /**
     * @brief y方向の半径を取得します。
     *
     * @return y方向の半径。
     */
    double getRadiusY() const;

    double getHeight() const;

    double getBottomZ() const;

    double getTopZ() const;

    AABB getAABB() const;

private:
    /** @brief 楕円柱の底面の中心座標。 */
    const Vec2 center;
    /** @brief x方向の半径。 */
    const double radiusX;
    /** @brief y方向の半径。 */
    const double radiusY;
    /** @brief 楕円柱の高さ。 */
    const double height;
    /** @brief 楕円柱のAABB。 */
    const AABB aabb;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_ELLIPTICALCYLINDER_H
