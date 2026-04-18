#ifndef FASTGEOM3D_QUADRILATERALPRISM_H
#define FASTGEOM3D_QUADRILATERALPRISM_H

#include "fastgeom3d/PolygonalPrism.h"

namespace fastgeom3d {

class QuadrilateralPrism;

/**
 * @brief 4頂点の底面からQuadrilateralPrismを生成します。
 *
 * @param vertices 底面の四角形の頂点座標リスト。ちょうど4つの頂点が必要。
 * @param height プリズムの高さ。
 * @return QuadrilateralPrismオブジェクト。
 */
QuadrilateralPrism makeQuadrilateralPrism(const std::vector<Vec2>& vertices, double height);

/**
 * @brief 四角形プリズムを表すクラス。
 *
 * 底面が四角形である3D形状を表現します。
 * 内部表現としてPolygonalPrismを保持しますが、公開API上は独立した具体型です。
 */
class QuadrilateralPrism final {
public:
    /**
     * @brief QuadrilateralPrismのコンストラクタ。
     *
     * @param vertices 底面の四角形の頂点座標リスト。ちょうど4つの頂点が必要。
     * @param height プリズムの高さ。
     * @throws std::invalid_argument 頂点数が4でない場合。
     */
    QuadrilateralPrism(const std::vector<Vec2>& vertices, double height);

    /** @brief プリズムの高さを取得します。 */
    double getHeight() const;

    /** @brief 底面のz座標を取得します。 */
    double getBottomZ() const;

    /** @brief 上面のz座標を取得します。 */
    double getTopZ() const;

    /** @brief 底面のPolygon2D表現を取得します。 */
    const Polygon2D& getBase() const;

    /** @brief プリズム全体のAABBを取得します。 */
    AABB getAABB() const;

    /**
     * @brief 内部のPolygonalPrism表現を取得します。
     *
     * 汎用角柱処理に橋渡しするためのアクセサです。
     * @return 内部保持しているPolygonalPrism。
     */
    const PolygonalPrism& asPolygonalPrism() const;

private:
    /** @brief 内部表現として保持するPolygonalPrism。 */
    const PolygonalPrism prism;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_QUADRILATERALPRISM_H
