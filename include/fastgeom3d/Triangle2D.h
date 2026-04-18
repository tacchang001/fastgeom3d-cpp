#ifndef FASTGEOM3D_TRIANGLE2D_H
#define FASTGEOM3D_TRIANGLE2D_H

#include "fastgeom3d/Polygon2D.h"

namespace fastgeom3d {

class Triangle2D;

/**
 * @brief 3頂点からTriangle2Dを生成します。
 *
 * @param vertices 三角形の頂点座標リスト。ちょうど3つの頂点が必要。
 * @return Triangle2Dオブジェクト。
 */
Triangle2D makeTriangle2D(const std::vector<Vec2>& vertices);

/**
 * @brief 2D三角形を表すクラス。
 *
 * 3つの頂点を持つ三角形を表現します。
 * 内部表現としてPolygon2Dを保持しますが、公開API上は独立した具体型です。
 */
class Triangle2D final {
public:
    /**
     * @brief Triangle2Dのコンストラクタ。
     *
     * @param vertices 三角形の頂点座標リスト。ちょうど3つの頂点が必要。
     * @throws std::invalid_argument 頂点数が3でない場合。
     */
    explicit Triangle2D(const std::vector<Vec2>& vertices);

     * @brief 三角形の頂点座標を取得します。
     *
     * @return 頂点座標のリスト。
     */
    const std::vector<Vec2>& getVertices() const;

    /**
     * @brief 三角形のAABBを取得します。
     *
     * @return 三角形を囲む軸平行境界ボックス。
     */
    AABB getAABB() const;

    /**
     * @brief 内部のPolygon2D表現を取得します。
     *
     * 交差判定や汎用多角形処理に橋渡しするためのアクセサです。
     * @return 内部保持しているPolygon2D。
     */
    const Polygon2D& asPolygon() const;

private:
    /** @brief 内部表現として保持するPolygon2D。 */
    const Polygon2D polygon;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_TRIANGLE2D_H
