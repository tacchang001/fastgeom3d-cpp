#ifndef FASTGEOM3D_CYLINDER_H
#define FASTGEOM3D_CYLINDER_H

#include "fastgeom3d/Prism.h"
#include "fastgeom3d/Vec2.h"

namespace fastgeom3d {

/**
 * @brief 円柱を表すクラス。
 *
 * Prismを継承し、底面が円である3D形状を表現します。
 */
class Cylinder final : public Prism {
public:
    /**
     * @brief Cylinderのコンストラクタ。
     *
     * @param center 円柱の底面の中心座標。
     * @param radius 円柱の半径。正の値でなければならない。
     * @param height 円柱の高さ。
     * @throws std::invalid_argument radiusが正でない場合。
     */
    Cylinder(const Vec2& center, double radius, double height);

    /**
     * @brief 円柱の底面の中心座標を取得します。
     *
     * @return 中心座標。
     */
    const Vec2& getCenter() const;

    /**
     * @brief 円柱の半径を取得します。
     *
     * @return 半径。
     */
    double getRadius() const;

private:
    /** @brief 円柱の底面の中心座標。 */
    const Vec2 center;
    /** @brief 円柱の半径。 */
    const double radius;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_CYLINDER_H
