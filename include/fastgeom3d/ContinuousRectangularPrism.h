#ifndef FASTGEOM3D_CONTINUOUSRECTANGULARPRISM_H
#define FASTGEOM3D_CONTINUOUSRECTANGULARPRISM_H

#include "fastgeom3d/AABB.h"
#include <vector>

namespace fastgeom3d {

/**
 * @brief 連続した直方体プリズムを表すクラス。
 *
 * 連続した複数のAABBからなる3D形状を表現します。
 */
class ContinuousRectangularPrism final {
public:
    /**
     * @brief ContinuousRectangularPrismのコンストラクタ。
     *
     * @param prisms_ 連続したAABBのベクトル。少なくとも2つのプリズムが必要です。
     * @throw std::invalid_argument プリズムが2つ未満、または連続していない場合。
     */
    explicit ContinuousRectangularPrism(const std::vector<AABB>& prisms_);

    /**
     * @brief プリズムのリストを取得します。
     *
     * @return AABBのベクトル。
     */
    const std::vector<AABB>& getPrisms() const;

    /**
     * @brief 連続プリズム全体のAABBを取得します。
     *
     * @return 全体を囲む軸平行境界ボックス。
     */
    AABB getAABB() const;

private:
    /** @brief 連続したAABBのベクトル。 */
    const std::vector<AABB> prisms;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_CONTINUOUSRECTANGULARPRISM_H
