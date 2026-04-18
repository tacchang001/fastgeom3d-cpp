#ifndef FASTGEOM3D_QUADRILATERALPRISM_H
#define FASTGEOM3D_QUADRILATERALPRISM_H

#include "fastgeom3d/PolygonalPrism.h"

namespace fastgeom3d {

class QuadrilateralPrism;

QuadrilateralPrism makeQuadrilateralPrism(const std::vector<Vec2>& vertices, double height);

/**
 * @brief 四角形プリズムを表すクラス。
 *
 * PolygonalPrismを継承し、底面が四角形である3D形状を表現します。
 */
class QuadrilateralPrism final : public PolygonalPrism {
public:
    /**
     * @brief QuadrilateralPrismのコンストラクタ。
     *
     * @param vertices 底面の四角形の頂点座標リスト。ちょうど4つの頂点が必要。
     * @param height プリズムの高さ。
     * @throws std::invalid_argument 頂点数が4でない場合。
     */
    QuadrilateralPrism(const std::vector<Vec2>& vertices, double height);
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_QUADRILATERALPRISM_H
