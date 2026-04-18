#ifndef FASTGEOM3D_ELLIPSE2D_H
#define FASTGEOM3D_ELLIPSE2D_H

#include "fastgeom3d/Shape2D.h"
#include "fastgeom3d/Vec2.h"

namespace fastgeom3d {

/**
 * @brief 2D楕円を表すクラス。
 *
 * Shape2Dを継承し、中心座標とx/y方向の半径を持つ楕円を表現します。
 */
class Ellipse2D final : public Shape2D {
public:
    /**
     * @brief Ellipse2Dのコンストラクタ。
     *
     * @param center_ 楕円の中心座標。
     * @param radiusX_ x方向の半径。正の値でなければならない。
     * @param radiusY_ y方向の半径。正の値でなければならない。
     * @throws std::invalid_argument radiusXまたはradiusYが正でない場合。
     */
    Ellipse2D(const Vec2& center_, double radiusX_, double radiusY_);

    /**
     * @brief 楕円の中心座標を取得します。
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

    /**
     * @brief 楕円の軸平行境界ボックス (AABB) を取得します。
     *
     * @return AABBオブジェクト。
     */
    AABB getAABB() const override;

private:
    /** @brief 楕円の中心座標。 */
    const Vec2 center;
    /** @brief x方向の半径。 */
    const double radiusX;
    /** @brief y方向の半径。 */
    const double radiusY;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_ELLIPSE2D_H
