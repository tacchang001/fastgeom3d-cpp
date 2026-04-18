#include "PrismSupport.h"
#include <stdexcept>

namespace fastgeom3d::detail {

/**
 * @brief 平面形状のAABBを高さ方向へ押し出した角柱AABBへ変換する。
 */
AABB makePrismAABB(const AABB& baseAABB, double height) {
    if (height <= 0.0) {
        throw std::invalid_argument("height must be positive");
    }

    if (baseAABB.minZ != baseAABB.maxZ) {
        throw std::invalid_argument("base shape must be flat in the Z axis");
    }

    // 底面のXY範囲は維持し、Z方向だけ高さ分を加えて角柱に拡張する。
    return AABB(
        baseAABB.minX,
        baseAABB.minY,
        baseAABB.minZ,
        baseAABB.maxX,
        baseAABB.maxY,
        baseAABB.minZ + height
    );
}

} // namespace fastgeom3d::detail