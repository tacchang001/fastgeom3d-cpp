#ifndef FASTGEOM3D_POLYGON2D_H
#define FASTGEOM3D_POLYGON2D_H

#include "fastgeom3d/Shape2D.h"
#include "fastgeom3d/Vec2.h"
#include <vector>

namespace fastgeom3d {

/**
 * @brief 2D多角形を表すクラス。
 *
 * Shape2Dを継承し、頂点のリストを持つ多角形を表現します。
 */
class Polygon2D : public Shape2D {
public:
    /**
     * @brief Polygon2Dのコンストラクタ。
     *
     * @param vertices_ 多角形の頂点座標のリスト。少なくとも3つの頂点が必要。
     * @throws std::invalid_argument 頂点数が3未満の場合。
     */
    explicit Polygon2D(const std::vector<Vec2>& vertices_);

    /**
     * @brief 多角形の頂点座標を取得します。
     *
     * @return 頂点座標のリスト。
     */
    const std::vector<Vec2>& getVertices() const;

    /**
     * @brief 多角形の軸平行境界ボックス (AABB) を取得します。
     *
     * @return AABBオブジェクト。
     */
    AABB getAABB() const override;

private:
    /** @brief 多角形の頂点座標リスト。 */
    const std::vector<Vec2> vertices;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_POLYGON2D_H
