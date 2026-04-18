#ifndef FASTGEOM3D_TRIANGULARPRISM_H
#define FASTGEOM3D_TRIANGULARPRISM_H

#include "fastgeom3d/PolygonalPrism.h"

namespace fastgeom3d {

class TriangularPrism;

/**
 * @brief 3頂点の底面からTriangularPrismを生成します。
 *
 * @param vertices 底面の三角形の頂点座標リスト。ちょうど3つの頂点が必要。
 * @param height プリズムの高さ。
 * @return TriangularPrismオブジェクト。
 */
TriangularPrism makeTriangularPrism(const std::vector<Vec2>& vertices, double height);

/**
 * @brief 三角形プリズムを表すクラス。
 *
 * 底面が三角形である3D形状を表現します。
 * 内部表現としてPolygonalPrismを保持しますが、公開API上は独立した具体型です。
 */
class TriangularPrism final {
public:
    /**
     * @brief TriangularPrismのコンストラクタ。
     *
     * @param vertices 底面の三角形の頂点座標リスト。ちょうど3つの頂点が必要。
     * @param height プリズムの高さ。
     * @throws std::invalid_argument 頂点数が3でない場合。
     */
    TriangularPrism(const std::vector<Vec2>& vertices, double height);

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

#endif // FASTGEOM3D_TRIANGULARPRISM_H
