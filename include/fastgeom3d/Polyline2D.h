#ifndef FASTGEOM3D_POLYLINE2D_H
#define FASTGEOM3D_POLYLINE2D_H

#include "fastgeom3d/Shape2D.h"
#include "fastgeom3d/Vec2.h"
#include <vector>

namespace fastgeom3d {

/**
 * @brief 2Dポリラインを表すクラス。
 *
 * Shape2Dを継承し、2D空間における連続した線分を表現します。
 */
class Polyline2D final : public Shape2D {
public:
    /**
     * @brief Polyline2Dのコンストラクタ。
     *
     * @param points_ ポリラインの頂点座標リスト。少なくとも2つの点が必要。
     * @throws std::invalid_argument 点数が2未満の場合。
     */
    explicit Polyline2D(const std::vector<Vec2>& points_);

    /**
     * @brief ポリラインの頂点座標を取得します。
     *
     * @return 頂点座標のリスト。
     */
    const std::vector<Vec2>& getPoints() const;

    /**
     * @brief ポリラインのAABBを取得します。
     *
     * @return ポリラインを囲む軸平行境界ボックス。
     */
    AABB getAABB() const override;

private:
    /** @brief ポリラインの頂点座標リスト。 */
    const std::vector<Vec2> points;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_POLYLINE2D_H
