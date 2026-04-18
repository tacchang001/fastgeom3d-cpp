#ifndef FASTGEOM3D_POLYGONALPRISM_H
#define FASTGEOM3D_POLYGONALPRISM_H

#include "fastgeom3d/Prism.h"
#include "fastgeom3d/Polygon2D.h"

namespace fastgeom3d {

/**
 * @brief 多角形プリズムを表すクラス。
 *
 * Prismを継承し、底面が多角形である3D形状を表現します。
 */
class PolygonalPrism : public Prism {
public:
    /**
     * @brief PolygonalPrismのコンストラクタ。
     *
     * @param vertices 底面の多角形の頂点座標リスト。
     * @param height プリズムの高さ。
     */
    PolygonalPrism(const std::vector<Vec2>& vertices, double height);

    /**
     * @brief プリズムの底面を取得します。
     *
     * @return 底面のPolygon2Dオブジェクト。
     */
    const Polygon2D& getBase() const;

private:
    /** @brief プリズムの底面。 */
    const Polygon2D base;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_POLYGONALPRISM_H
