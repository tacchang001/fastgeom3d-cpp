#ifndef FASTGEOM3D_AABB_H
#define FASTGEOM3D_AABB_H

#include "fastgeom3d/Vec3.h"
#include "fastgeom3d/Vec2.h"
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <vector>

namespace fastgeom3d {

/**
 * @brief 軸平行境界ボックス (Axis-Aligned Bounding Box) を表すクラス。
 *
 * 3D空間における軸平行な境界ボックスを表現します。
 */
class AABB final {
public:
    /** @brief 最小x座標。 */
    double minX;
    /** @brief 最小y座標。 */
    double minY;
    /** @brief 最小z座標。 */
    double minZ;
    /** @brief 最大x座標。 */
    double maxX;
    /** @brief 最大y座標。 */
    double maxY;
    /** @brief 最大z座標。 */
    double maxZ;

    /**
     * @brief AABBのコンストラクタ。
     *
     * @param minX_ 最小x座標。
     * @param minY_ 最小y座標。
     * @param minZ_ 最小z座標。
     * @param maxX_ 最大x座標。
     * @param maxY_ 最大y座標。
     * @param maxZ_ 最大z座標。
     */
    AABB(double minX_, double minY_, double minZ_,
         double maxX_, double maxY_, double maxZ_);

    /**
     * @brief 中心と半拡張からAABBを作成します。
     *
     * @param center 中心座標。
     * @param halfExtents 各軸方向の半拡張。
     * @return AABBオブジェクト。
     */
    static AABB fromCenterHalfExtents(const Vec3& center, const Vec3& halfExtents);

    /**
     * @brief 点のリストからAABBを作成します。
     *
     * @param points 点のリスト。
     * @return AABBオブジェクト。
     */
    static AABB fromPoints(const std::vector<Vec3>& points);

    /**
     * @brief 2D点のリストからAABBを作成します (zは0)。
     *
     * @param points 2D点のリスト。
     * @return AABBオブジェクト。
     */
    static AABB fromPoints2D(const std::vector<Vec2>& points);

    /**
     * @brief AABBのAABBを取得します (自身を返します)。
     *
     * @return このAABBオブジェクト。
     */
    AABB getAABB() const;

    /**
     * @brief 等価演算子。
     *
     * @param other 比較するAABB。
     * @return 等しい場合true。
     */
    bool operator==(const AABB& other) const;

    /**
     * @brief 非等価演算子。
     *
     * @param other 比較するAABB。
     * @return 等しくない場合true。
     */
    bool operator!=(const AABB& other) const;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_AABB_H
