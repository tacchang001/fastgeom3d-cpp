#ifndef FASTGEOM3D_TRIANGULARPRISM_H
#define FASTGEOM3D_TRIANGULARPRISM_H

#include "fastgeom3d/PolygonalPrism.h"

namespace fastgeom3d {

class TriangularPrism;

TriangularPrism makeTriangularPrism(const std::vector<Vec2>& vertices, double height);

/**
 * @brief 三角形プリズムを表すクラス。
 *
 * 底面が三角形である3D形状を表現します。
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

    double getHeight() const;

    double getBottomZ() const;

    double getTopZ() const;

    const Polygon2D& getBase() const;

    AABB getAABB() const;

    const PolygonalPrism& asPolygonalPrism() const;

private:
    const PolygonalPrism prism;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_TRIANGULARPRISM_H
