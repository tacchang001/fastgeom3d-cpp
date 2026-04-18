#ifndef FASTGEOM3D_POLYLINE_H
#define FASTGEOM3D_POLYLINE_H

#include "fastgeom3d/AABB.h"
#include "fastgeom3d/Vec3.h"
#include <vector>

namespace fastgeom3d {

struct UTMCoordinate;

/**
 * @brief 3Dポリラインを表すクラス。
 *
 * 3D空間における連続した線分を表現します。
 */
class Polyline final {
public:
    /**
     * @brief Polylineのコンストラクタ。
     *
     * @param points_ ポリラインの頂点座標リスト。少なくとも2つの点が必要。
     * @throws std::invalid_argument 点数が2未満の場合。
     */
    explicit Polyline(const std::vector<Vec3>& points_);

    /**
     * @brief UTM座標のリストからPolylineを作成します。
     *
     * @param utmPoints UTM座標のリスト。
     * @return Polylineオブジェクト。
     */
    static Polyline fromUTM(const std::vector<UTMCoordinate>& utmPoints);

    /**
     * @brief ポリラインの頂点座標を取得します。
     *
     * @return 頂点座標のリスト。
     */
    const std::vector<Vec3>& getPoints() const;

    /**
     * @brief ポリラインのAABBを取得します。
     *
     * @return ポリラインを囲む軸平行境界ボックス。
     */
    AABB getAABB() const;

private:
    /** @brief ポリラインの頂点座標リスト。 */
    const std::vector<Vec3> points;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_POLYLINE_H
