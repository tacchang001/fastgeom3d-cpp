#ifndef FASTGEOM3D_CIRCLE2D_H
#define FASTGEOM3D_CIRCLE2D_H

#include "fastgeom3d/AABB.h"
#include "fastgeom3d/Vec2.h"

namespace fastgeom3d {

/**
 * @brief 2D円を表すクラス。
 *
 * 2D空間における円を表現します。
 */
class Circle2D final {
public:
    /**
     * @brief Circle2Dのコンストラクタ。
     *
     * @param center_ 円の中心座標。
     * @param radius_ 円の半径。正の値でなければなりません。
     * @throw std::invalid_argument radiusが正でない場合。
     */
    Circle2D(const Vec2& center_, double radius_);

    /**
     * @brief 円の中心座標を取得します。
     *
     * @return 中心座標のVec2。
     */
    const Vec2& getCenter() const;

    /**
     * @brief 円の半径を取得します。
     *
     * @return 半径の値。
     */
    double getRadius() const;

    /**
     * @brief 円のAABBを取得します。
     *
     * @return 円を囲む軸平行境界ボックス。
     */
    AABB getAABB() const;

private:
    /** @brief 円の中心座標。 */
    Vec2 center;
    /** @brief 円の半径。 */
    double radius;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_CIRCLE2D_H
