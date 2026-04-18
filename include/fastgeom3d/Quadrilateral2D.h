#ifndef FASTGEOM3D_QUADRILATERAL2D_H
#define FASTGEOM3D_QUADRILATERAL2D_H

#include "fastgeom3d/Polygon2D.h"

namespace fastgeom3d {

class Quadrilateral2D;

Quadrilateral2D makeQuadrilateral2D(const std::vector<Vec2>& vertices);

/**
 * @brief 2D四角形を表すクラス。
 *
 * Polygon2Dを継承し、4つの頂点を持つ四角形を表現します。
 */
class Quadrilateral2D final : public Polygon2D {
public:
    /**
     * @brief Quadrilateral2Dのコンストラクタ。
     *
     * @param vertices 四角形の頂点座標リスト。ちょうど4つの頂点が必要。
     * @throws std::invalid_argument 頂点数が4でない場合。
     */
    explicit Quadrilateral2D(const std::vector<Vec2>& vertices);
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_QUADRILATERAL2D_H
