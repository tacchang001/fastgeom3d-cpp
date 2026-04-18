#ifndef FASTGEOM3D_PRISM_H
#define FASTGEOM3D_PRISM_H

#include "fastgeom3d/AABB.h"
#include "fastgeom3d/Shape3D.h"
#include <vector>

namespace fastgeom3d {

class Shape2D;
class Vec3;

/**
 * @brief プリズム（角柱）を表す基底クラス。
 *
 * Shape3Dを継承し、2D形状を底面とし、高さを持つ3D形状の基底クラスです。
 */
class Prism : public Shape3D {
public:
    /**
     * @brief プリズムの高さを取得します。
     *
     * @return 高さ。
     */
    double getHeight() const;

    /**
     * @brief プリズムの底面のz座標を取得します。
     *
     * @return 底面のz座標。
     */
    double getBottomZ() const;

    /**
     * @brief プリズムの上面のz座標を取得します。
     *
     * @return 上面のz座標。
     */
    double getTopZ() const;

    /**
     * @brief プリズムの軸平行境界ボックス (AABB) を取得します。
     *
     * @return AABBオブジェクト。
     */
    AABB getAABB() const override;

    /**
     * @brief 頂点が同じ水平面上にあるかを検証します。
     *
     * @param vertices 検証する頂点リスト。
     * @throws std::invalid_argument 頂点が空、または同じz座標でない場合。
     */
    static void validateHorizontalPlane(const std::vector<Vec3>& vertices);

protected:
    /**
     * @brief Prismのコンストラクタ。
     *
     * @param baseShape 底面の2D形状。
     * @param height_ 高さ。正の値でなければならない。
     * @throws std::invalid_argument heightが正でない場合。
     */
    Prism(const Shape2D& baseShape, double height_);

private:
    /**
     * @brief 底面形状と高さからAABBを作成します。
     *
     * @param baseShape 底面の2D形状。
     * @param height_ 高さ。
     * @return AABBオブジェクト。
     * @throws std::invalid_argument 底面がz軸で平坦でない場合。
     */
    static AABB createAABB(const Shape2D& baseShape, double height_);

    /** @brief プリズムの高さ。 */
    const double height;
    /** @brief プリズムのAABB。 */
    const AABB aabb;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_PRISM_H
