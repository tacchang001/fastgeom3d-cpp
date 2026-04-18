#ifndef FASTGEOM3D_QUADRILATERAL2D_H
#define FASTGEOM3D_QUADRILATERAL2D_H

#include "fastgeom3d/Polygon2D.h"

namespace fastgeom3d {

class Quadrilateral2D;

/**
 * @brief 4頂点からQuadrilateral2Dを生成します。
 *
 * @param vertices 四角形の頂点座標リスト。ちょうど4つの頂点が必要。
 * @return Quadrilateral2Dオブジェクト。
 */
Quadrilateral2D makeQuadrilateral2D(const std::vector<Vec2>& vertices);

/**
 * @brief 2D四角形を表すクラス。
 *
 * 4つの頂点を持つ四角形を表現します。
 * 内部表現としてPolygon2Dを保持しますが、公開API上は独立した具体型です。
 */
class Quadrilateral2D final {
public:
    /**
     * @brief Quadrilateral2Dのコンストラクタ。
     *
     * @param vertices 四角形の頂点座標リスト。ちょうど4つの頂点が必要。
     * @throws std::invalid_argument 頂点数が4でない場合。
     */
    explicit Quadrilateral2D(const std::vector<Vec2>& vertices);

    /**
     * @brief 四角形の頂点座標を取得します。
     *
     * @return 頂点座標のリスト。
     */
    const std::vector<Vec2>& getVertices() const;

    /**
     * @brief 四角形のAABBを取得します。
     *
     * @return 四角形を囲む軸平行境界ボックス。
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

#endif // FASTGEOM3D_QUADRILATERAL2D_H
