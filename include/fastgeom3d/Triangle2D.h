#ifndef FASTGEOM3D_TRIANGLE2D_H
#define FASTGEOM3D_TRIANGLE2D_H

#include "fastgeom3d/Polygon2D.h"

namespace fastgeom3d {

class Triangle2D;

Triangle2D makeTriangle2D(const std::vector<Vec2>& vertices);

/**
 * @brief 2D三角形を表すクラス。
 *
 * 3つの頂点を持つ三角形を表現します。
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

    const std::vector<Vec2>& getVertices() const;

    AABB getAABB() const;

    const Polygon2D& asPolygon() const;

private:
    const Polygon2D polygon;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_TRIANGLE2D_H
